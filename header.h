/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:27:37 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 13:50:06 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESCAPE 53

/*
** The first elements below, including the structure s_file, \
** are just for the get_next_line part of the program.
*/

# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 4

typedef struct				s_file
{
	char					*content;
	int						fd;
	struct s_file			*next;
}							t_file;

int							get_next_line(const int fd, char **line);

typedef struct s_player		t_player;

struct						s_player
{
	double					x;
	double					y;
	double					ang;
	double					fov;
};

typedef struct s_move		t_move;

struct						s_move
{
	double					rotation_speed;
	double					forward_speed;
};

typedef struct s_game		t_game;

struct						s_game
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*img_ptr;
	unsigned char			*image;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
	int						size_x;
	int						size_y;
	char					*title;
	double					wall_pix_size_pp_dist;
	double					wall_size_time_pp_dist;
};

typedef struct s_keys		t_keys;

struct						s_keys
{
	int						up;
	int						down;
	int						left;
	int						right;
};

typedef struct s_colors		t_colors;

struct						s_colors
{
	unsigned char			sky[4];
	unsigned char			floor[4];
	unsigned char			wall_north[4];
	unsigned char			wall_south[4];
	unsigned char			wall_west[4];
	unsigned char			wall_east[4];
};

typedef struct s_global		t_global;

struct						s_global
{
	t_player				player;
	t_move					move;
	t_game					game;
	t_keys					keys;
	t_colors				colors;
	int						map[100][100];
};

typedef struct s_column_pix	t_column_pix;

struct						s_column_pix
{
	int						col_pix_nb;
	double					distance;
	int						obs_type;
	int						obs_side;
};
/*
** value for the param obs_side --> 0 north, 1 south, 2 west, 3 east
*/

int							key_press(int keycode, t_global *gl);
int							key_release(int keycode, t_global *gl);
int							click_escape(int keycode, void *empty);
int							change_pos(t_global *gl);

void						empty_map(t_global *gl);
void						initialize_map(t_global *gl, char *file);
void						initialize_colors(t_global *gl);
void						initialize_map_and_player(t_global *gl, char *file);

int							apply_rotation(t_global *gl);
void						get_next_incremental_move\
								(t_global *gl, \
								double *inc_pos);
int							move_to_new_position(t_global *gl);
int							next_move(t_global *gl);

void						reinitialize_image\
								(t_global *gl);
void						update_pixel_color\
								(t_global *gl, \
								t_column_pix *column_pix, \
								int fst_pix_char);
void						update_column_of_pixel\
								(t_global *gl, \
								t_column_pix *column_pix);
void						update_image_with_obstacles\
								(t_global *gl);
void						display_new_view(t_global *gl);

void						reinitialize_image(t_global *gl);
void						update_pixel_color(t_global *gl, \
								t_column_pix *column_pix, \
								int fst_pix_char);
void						update_column_of_pixels(t_global *gl, \
								t_column_pix *column_pix, \
								double angle);
void						update_image_with_obstacles(t_global *gl);
void						display_new_view(t_global *gl);

int							check_if_obstacle_met_horizontal_line\
								(t_global *gl, double angle, \
								t_column_pix *horiz, \
								double *coor);
void						find_closest_obstacle_horizontal_line\
								(t_global *gl, double angle, \
								t_column_pix *horiz);
int							check_if_obstacle_met_vertical_line\
								(t_global *gl, double angle, \
								t_column_pix *horiz, double *coor);
void						find_closest_obstacle_vertical_line\
								(t_global *gl, double angle, \
								t_column_pix *verti);
void						find_obstacle_with_raycasting(t_global *gl, \
								t_column_pix *column_pix, double angle);

double						ft_abs(double n);
double						compute_distance(double x_a, double y_a, \
								double x_b, double y_b);
void						copy_t_column_pix_node_onto_another\
								(t_column_pix *a, t_column_pix *b);
double						d_to_r(double degree);
void						set_pixel(unsigned char *pixel, \
								unsigned char *color);

double						map_borders(int i, double n);

#endif
