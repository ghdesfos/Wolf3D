/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_obstacle_with_raycasting.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:35:05 by ghdesfos          #+#    #+#             */
/*   Updated: 2018/11/19 03:18:04 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_if_obstacle_met_horizontal_line(t_global *gl, double angle, \
		t_column_pix *horiz, double *coor)
{
	int obs_type;

	if ((angle > 270 || angle < 90) \
			&& (obs_type = gl->map[(int)floor(coor[0])][(int)coor[1] - 1]) != 0)
	{
		horiz->distance = \
			compute_distance(gl->player.x, gl->player.y, coor[0], coor[1]);
		horiz->obs_type = obs_type;
		horiz->obs_side = 1;
		return (1);
	}
	if ((angle >= 90 && angle <= 270) \
			&& (obs_type = gl->map[(int)floor(coor[0])][(int)coor[1]]) != 0)
	{
		horiz->distance = \
			compute_distance(gl->player.x, gl->player.y, coor[0], coor[1]);
		horiz->obs_type = obs_type;
		horiz->obs_side = 0;
		return (1);
	}
	return (0);
}

void	find_closest_obstacle_horizontal_line(t_global *gl, double angle, \
		t_column_pix *horiz)
{
	int		i;
	int		swap;
	double	coor[2];

	i = floor(gl->player.y) + ((angle > 270 || angle < 90) ? 0 : 1);
	swap = 0;
	while (swap == 0)
	{
		coor[1] = i;
		if (angle >= 0 && angle < 90)
			coor[0] = map_borders(0, gl->player.x \
					+ ft_abs(gl->player.y - i) * tan(d_to_r(angle)));
		else if (angle >= 90 && angle < 180)
			coor[0] = map_borders(0, gl->player.x \
					+ ft_abs(gl->player.y - i) * tan(d_to_r(180 - angle)));
		else if (angle >= 180 && angle < 270)
			coor[0] = map_borders(0, gl->player.x \
					- ft_abs(gl->player.y - i) * tan(d_to_r(angle - 180)));
		else if (angle >= 270 && angle < 360)
			coor[0] = map_borders(0, gl->player.x \
					- ft_abs(gl->player.y - i) * tan(d_to_r(360 - angle)));
		swap = check_if_obstacle_met_horizontal_line(gl, angle, horiz, coor);
		(angle > 270 || angle < 90) ? i-- : i++;
	}
}

int		check_if_obstacle_met_vertical_line(t_global *gl, double angle, \
		t_column_pix *horiz, double *coor)
{
	int obs_type;

	if ((angle > 180) \
			&& (obs_type = gl->map[(int)coor[0] - 1][(int)floor(coor[1])]) != 0)
	{
		horiz->distance = \
			compute_distance(gl->player.x, gl->player.y, coor[0], coor[1]);
		horiz->obs_type = obs_type;
		horiz->obs_side = 3;
		return (1);
	}
	if ((angle <= 180) \
			&& (obs_type = gl->map[(int)coor[0]][(int)floor(coor[1])]) != 0)
	{
		horiz->distance = \
			compute_distance(gl->player.x, gl->player.y, coor[0], coor[1]);
		horiz->obs_type = obs_type;
		horiz->obs_side = 2;
		return (1);
	}
	return (0);
}

void	find_closest_obstacle_vertical_line(t_global *gl, double angle, \
		t_column_pix *verti)
{
	int		i;
	int		swap;
	double	coor[2];

	i = floor(gl->player.x) + ((angle > 180) ? 0 : 1);
	swap = 0;
	while (swap == 0)
	{
		coor[0] = i;
		if (angle >= 0 && angle < 90)
			coor[1] = map_borders(1, gl->player.y \
					- ft_abs(gl->player.x - i) / tan(d_to_r(angle)));
		else if (angle >= 90 && angle < 180)
			coor[1] = map_borders(1, gl->player.y \
					+ ft_abs(gl->player.x - i) / tan(d_to_r(180 - angle)));
		else if (angle >= 180 && angle < 270)
			coor[1] = map_borders(1, gl->player.y \
					+ ft_abs(gl->player.x - i) / tan(d_to_r(angle - 180)));
		else if (angle >= 270 && angle < 360)
			coor[1] = map_borders(1, gl->player.y \
					- ft_abs(gl->player.x - i) / tan(d_to_r(360 - angle)));
		swap = check_if_obstacle_met_vertical_line(gl, angle, verti, coor);
		(angle > 180) ? i-- : i++;
	}
}

void	find_obstacle_with_raycasting(t_global *gl, t_column_pix *column_pix, \
		double angle)
{
	t_column_pix horiz;
	t_column_pix verti;

	if (angle != 90 && angle != 270)
		find_closest_obstacle_horizontal_line(gl, angle, &horiz);
	if (angle != 0 && angle != 180)
		find_closest_obstacle_vertical_line(gl, angle, &verti);
	if (angle == 90 || angle == 270)
		copy_t_column_pix_node_onto_another(column_pix, &verti);
	else if (angle == 0 || angle == 180)
		copy_t_column_pix_node_onto_another(column_pix, &horiz);
	else
	{
		if (verti.distance < horiz.distance)
			copy_t_column_pix_node_onto_another(column_pix, &verti);
		else
			copy_t_column_pix_node_onto_another(column_pix, &horiz);
	}
}
