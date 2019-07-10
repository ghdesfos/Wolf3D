/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 20:54:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2018/11/19 03:20:08 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	ft_abs(double n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

double	compute_distance(double x_a, double y_a, double x_b, double y_b)
{
	double n;

	n = ((x_a - x_b) * (x_a - x_b)) + ((y_a - y_b) * (y_a - y_b));
	n = sqrt(n);
	return (n);
}

void	copy_t_column_pix_node_onto_another(t_column_pix *a, t_column_pix *b)
{
	a->distance = b->distance;
	a->obs_type = b->obs_type;
	a->obs_side = b->obs_side;
}

double	d_to_r(double degree)
{
	double radiant;

	radiant = degree * M_PI / 180;
	return (radiant);
}

void	set_pixel(unsigned char *pixel, unsigned char *color)
{
	pixel[0] = color[0];
	pixel[1] = color[1];
	pixel[2] = color[2];
	pixel[3] = color[3];
}
