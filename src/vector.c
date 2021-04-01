/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:07:18 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 05:55:16 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	v_dbl_rotate(t_v_dbl *v, double angle)
{
	double temp;

	temp = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = v->y * cos(angle) + temp * sin(angle);
}

void	v_dbl_init(t_v_dbl *vect, double x, double y)
{
	vect->x = x;
	vect->y = y;
}

double	v_dbl_mlp(t_v_dbl *v1, t_v_dbl *v2)
{
	return (v1->x * v2->x + v1->y * v2->y);
}

double	v_dbl_len(t_v_dbl *v)
{
	return (sqrt(v->x * v->x + v->y * v->y));
}

double	v_dbl_angle(t_v_dbl *v1, t_v_dbl *v2)
{
	return (acos(v_dbl_mlp(v1, v2) / (v_dbl_len(v1) * v_dbl_len(v2))));
}
