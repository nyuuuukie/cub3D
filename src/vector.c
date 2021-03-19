/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:07:18 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/19 20:43:51 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	vector_rotate(t_vector *v, double angle)
{
	double temp;

	temp = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = v->y * cos(angle) + temp * sin(angle);
}

void	vector_init(t_vector *vect, double x, double y)
{
	vect->x = x;
	vect->y = y;
}

double	vector_mlp(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y);
}

double vector_len(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y));
}

double vector_angle(t_vector *v1, t_vector *v2)
{
	return (acos(vector_mlp(v1, v2) / (vector_len(v1) * vector_len(v2))));
}