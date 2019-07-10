/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:00:07 by ghdesfos          #+#    #+#             */
/*   Updated: 2018/11/19 04:13:05 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		apply_rotation(t_global *gl)
{
	int backward;

	backward = 1;
	if (gl->keys.down == 1)
		backward = -1;
	if (gl->keys.left == 0 && gl->keys.right == 0)
		return (0);
	if (gl->keys.left == 1)
		gl->player.ang -= gl->move.rotation_speed * backward;
	if (gl->keys.right == 1)
		gl->player.ang += gl->move.rotation_speed * backward;
	while (gl->player.ang >= 360)
		gl->player.ang = gl->player.ang - 360;
	while (gl->player.ang < 0)
		gl->player.ang = gl->player.ang + 360;
	return (1);
}

void	get_next_incremental_move(t_global *gl, double *inc_pos)
{
	double	sp;

	sp = gl->move.forward_speed;
	if (gl->player.ang >= 0 && gl->player.ang < 90)
	{
		inc_pos[0] = sin(d_to_r(gl->player.ang)) * sp;
		inc_pos[1] = cos(d_to_r(gl->player.ang)) * sp * -1;
	}
	else if (gl->player.ang >= 90 && gl->player.ang < 180)
	{
		inc_pos[0] = sin(d_to_r(180.0 - gl->player.ang)) * sp;
		inc_pos[1] = cos(d_to_r(180.0 - gl->player.ang)) * sp;
	}
	else if (gl->player.ang >= 180 && gl->player.ang < 270)
	{
		inc_pos[0] = sin(d_to_r(gl->player.ang - 180)) * sp * -1;
		inc_pos[1] = cos(d_to_r(gl->player.ang - 180)) * sp;
	}
	else if (gl->player.ang >= 270 && gl->player.ang < 360)
	{
		inc_pos[0] = sin(d_to_r(360 - gl->player.ang)) * sp * -1;
		inc_pos[1] = cos(d_to_r(360 - gl->player.ang)) * sp * -1;
	}
}

int		move_to_new_position(t_global *gl)
{
	double inc_pos[2];
	double tmp;

	if (gl->keys.up == 0 && gl->keys.down == 0)
		return (0);
	get_next_incremental_move(gl, inc_pos);
	tmp = gl->player.x;
	if (gl->keys.down == 1)
	{
		inc_pos[0] = -inc_pos[0];
		inc_pos[1] = -inc_pos[1];
	}
	if (gl->map[(int)floor(gl->player.x + inc_pos[0])]\
			[(int)floor(gl->player.y)] == 0)
		gl->player.x += inc_pos[0];
	if (gl->map[(int)floor(tmp)]\
			[(int)floor(gl->player.y + inc_pos[1])] == 0)
		gl->player.y += inc_pos[1];
	return (1);
}

int		next_move(t_global *gl)
{
	int rotation;
	int movement;

	rotation = apply_rotation(gl);
	movement = move_to_new_position(gl);
	if (rotation == 0 && movement == 0)
		return (0);
	else
		return (1);
}
