/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:53:14 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/27 12:19:47 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		key_press(int keycode, t_global *gl)
{
	int move;

	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_image(gl->game.mlx_ptr, gl->game.img_ptr);
		mlx_destroy_window(gl->game.mlx_ptr, gl->game.win_ptr);
		exit(0);
	}
	if (keycode == KEY_UP && (gl->keys.up = 1))
		gl->keys.down = 0;
	if (keycode == KEY_DOWN && (gl->keys.down = 1))
		gl->keys.up = 0;
	if (keycode == KEY_LEFT && (gl->keys.left = 1))
		gl->keys.right = 0;
	if (keycode == KEY_RIGHT && (gl->keys.right = 1))
		gl->keys.left = 0;
	move = next_move(gl);
	if (move == 1)
		display_new_view(gl);
	return (0);
}

int		key_release(int keycode, t_global *gl)
{
	if (keycode == KEY_UP)
		gl->keys.up = 0;
	if (keycode == KEY_DOWN)
		gl->keys.down = 0;
	if (keycode == KEY_LEFT)
		gl->keys.left = 0;
	if (keycode == KEY_RIGHT)
		gl->keys.right = 0;
	return (0);
}

int		click_escape(int keycode, void *empty)
{
	(void)keycode;
	(void)empty;
	exit(0);
	return (0);
}

int		change_pos(t_global *gl)
{
	int move;

	move = next_move(gl);
	if (move == 1)
		display_new_view(gl);
	return (0);
}

int		main(int argc, char **argv)
{
	t_global gl;

	gl.game.size_x = 1000;
	gl.game.size_y = 1000;
	gl.game.title = "wolf3d";
	if (argc == 2)
		initialize_map_and_player(&gl, argv[1]);
	else
		return (0);
	gl.game.mlx_ptr = mlx_init();
	gl.game.win_ptr = mlx_new_window(gl.game.mlx_ptr, \
			gl.game.size_x, gl.game.size_y, gl.game.title);
	gl.game.img_ptr = mlx_new_image(gl.game.mlx_ptr, \
			gl.game.size_x, gl.game.size_y);
	gl.game.image = (unsigned char*)mlx_get_data_addr(gl.game.img_ptr, \
			&(gl.game.bits_per_pixel), &(gl.game.size_line), &(gl.game.endian));
	display_new_view(&gl);
	mlx_hook(gl.game.win_ptr, 2, 0, &key_press, &gl);
	mlx_hook(gl.game.win_ptr, 3, 0, &key_release, &gl);
	mlx_hook(gl.game.win_ptr, 2, 0, &key_press, &gl);
	mlx_hook(gl.game.win_ptr, 17, 0, &click_escape, NULL);
	mlx_loop_hook(gl.game.mlx_ptr, &change_pos, &gl);
	mlx_loop(gl.game.mlx_ptr);
	return (0);
}
