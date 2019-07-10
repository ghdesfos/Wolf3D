/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_map_and_player.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:51:53 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/27 12:21:45 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	empty_map(t_global *gl)
{
	int i;
	int j;

	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			gl->map[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	initialize_map(t_global *gl, char *file)
{
	int		fd;
	int		i;
	int		j;
	char	*str;

	if ((fd = open(file, O_RDONLY)) == -1)
		return ;
	i = 0;
	while (get_next_line(fd, &str) == 1)
	{
		j = 0;
		while (str[j])
		{
			gl->map[i][j] = str[j] - 48;
			j++;
		}
		free(str);
		str = NULL;
		i++;
	}
	if (close(fd) == -1)
		return ;
}

void	initialize_colors(t_global *gl)
{
	gl->colors.sky[3] = 0;
	gl->colors.sky[2] = 135;
	gl->colors.sky[1] = 206;
	gl->colors.sky[0] = 250;
	gl->colors.floor[3] = 0;
	gl->colors.floor[2] = 192;
	gl->colors.floor[1] = 192;
	gl->colors.floor[0] = 192;
	gl->colors.wall_north[3] = 0;
	gl->colors.wall_north[2] = 240;
	gl->colors.wall_north[1] = 128;
	gl->colors.wall_north[0] = 128;
	gl->colors.wall_south[3] = 0;
	gl->colors.wall_south[2] = 205;
	gl->colors.wall_south[1] = 92;
	gl->colors.wall_south[0] = 92;
	gl->colors.wall_west[3] = 0;
	gl->colors.wall_west[2] = 178;
	gl->colors.wall_west[1] = 34;
	gl->colors.wall_west[0] = 34;
	gl->colors.wall_east[3] = 0;
	gl->colors.wall_east[2] = 139;
	gl->colors.wall_east[1] = 0;
	gl->colors.wall_east[0] = 0;
}

void	initialize_map_and_player(t_global *gl, char *file)
{
	double pp_dist;

	empty_map(gl);
	initialize_map(gl, file);
	initialize_colors(gl);
	gl->player.x = 1.5;
	gl->player.y = 1.5;
	gl->player.ang = 90;
	gl->player.fov = 60;
	gl->move.rotation_speed = 1;
	gl->move.forward_speed = 0.03;
	pp_dist = gl->game.size_x / 2;
	pp_dist /= tan(d_to_r(gl->player.fov / 2));
	gl->game.wall_pix_size_pp_dist = 1;
	gl->game.wall_size_time_pp_dist = gl->game.wall_pix_size_pp_dist * pp_dist;
}
