/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 03:19:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2018/11/19 06:18:07 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	map_borders(int i, double n)
{
	if (i == 0)
	{
		if (n < 0)
			return (0);
		else if (n >= 100)
			return (100 - 1);
		else
			return (n);
	}
	else if (i == 1)
	{
		if (n < 0)
			return (0);
		else if (n >= 100)
			return (100 - 1);
		else
			return (n);
	}
	return (0);
}
