/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:27:07 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 00:29:34 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	swap_d_values(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	swap_c_values(char *a, char *b)
{
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		random_number(int min, int max)
{
	return (rand() % (max - min) + min);
}

int		is_lightning(t_all *all)
{
	return ((all->frame_count % 100 < 5 ) || \
			(all->frame_count % 100 > 20 && all->frame_count % 100 < 25));
}