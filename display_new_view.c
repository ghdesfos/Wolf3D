/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_new_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:06:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 14:02:31 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	reinitialize_image(t_global *gl)
{
	unsigned char	*str;
	int				line;
	int				i;

	str = gl->game.image;
	line = -1;
	while (++line < gl->game.size_y)
	{
		i = 0;
		while (i < 4 * gl->game.size_x)
		{
			if (line < gl->game.size_y / 2)
				set_pixel(&str[i + line * 4 * gl->game.size_x], \
						gl->colors.sky);
			else if (line >= gl->game.size_y / 2)
				set_pixel(&str[i + line * 4 * gl->game.size_x], \
						gl->colors.floor);
			i += 4;
		}
	}
}

void	update_pixel_color(t_global *gl, t_column_pix *column_pix, \
		int fst_pix_char)
{
	if (column_pix->obs_side == 0 || column_pix->obs_side == 1)
	{
		gl->game.image[fst_pix_char + 0] = (column_pix->obs_side == 0) ? \
			gl->colors.wall_north[0] : gl->colors.wall_south[0];
		gl->game.image[fst_pix_char + 1] = (column_pix->obs_side == 0) ? \
			gl->colors.wall_north[1] : gl->colors.wall_south[1];
		gl->game.image[fst_pix_char + 2] = (column_pix->obs_side == 0) ? \
			gl->colors.wall_north[2] : gl->colors.wall_south[2];
		gl->game.image[fst_pix_char + 3] = (column_pix->obs_side == 0) ? \
			gl->colors.wall_north[3] : gl->colors.wall_south[3];
	}
	if (column_pix->obs_side == 2 || column_pix->obs_side == 3)
	{
		gl->game.image[fst_pix_char + 0] = (column_pix->obs_side == 2) ? \
			gl->colors.wall_west[0] : gl->colors.wall_east[0];
		gl->game.image[fst_pix_char + 1] = (column_pix->obs_side == 2) ? \
			gl->colors.wall_west[1] : gl->colors.wall_east[1];
		gl->game.image[fst_pix_char + 2] = (column_pix->obs_side == 2) ? \
			gl->colors.wall_west[2] : gl->colors.wall_east[2];
		gl->game.image[fst_pix_char + 3] = (column_pix->obs_side == 2) ? \
			gl->colors.wall_west[3] : gl->colors.wall_east[3];
	}
}

void	update_column_of_pixels(t_global *gl, t_column_pix *column_pix, \
		double angle)
{
	double	wall_pixel_height;
	double	min;
	double	max;
	int		pix_nb;
	int		fst_pix_char;

	wall_pixel_height = floor(gl->game.wall_size_time_pp_dist \
			/ column_pix->distance \
			/ cos(d_to_r(ft_abs(gl->player.ang - angle))));
	min = floor((gl->game.size_y / 2) - (wall_pixel_height / 2));
	if (min < 0)
		min = 0;
	max = min + wall_pixel_height;
	if (max > gl->game.size_y)
		max = gl->game.size_y;
	pix_nb = min;
	while (pix_nb < max)
	{
		fst_pix_char = (4 * column_pix->col_pix_nb) \
			+ (pix_nb * 4 * gl->game.size_x);
		update_pixel_color(gl, column_pix, fst_pix_char);
		pix_nb++;
	}
}

void	update_image_with_obstacles(t_global *gl)
{
	t_column_pix	column_pix;
	int				img_col;
	double			angle;
	double			ang_inc;

	ang_inc = gl->player.fov / gl->game.size_x;
	img_col = 0;
	while (img_col < gl->game.size_x)
	{
		column_pix.col_pix_nb = img_col;
		angle = gl->player.ang - (gl->player.fov / 2);
		angle += ang_inc * img_col;
		while (angle >= 360)
			angle = angle - 360;
		while (angle < 0)
			angle = angle + 360;
		find_obstacle_with_raycasting(gl, &column_pix, angle);
		update_column_of_pixels(gl, &column_pix, angle);
		img_col++;
	}
}

void	display_new_view(t_global *gl)
{
	reinitialize_image(gl);
	update_image_with_obstacles(gl);
	mlx_put_image_to_window(gl->game.mlx_ptr, gl->game.win_ptr, \
			gl->game.img_ptr, 0, 0);
}
