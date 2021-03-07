/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:07:18 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/07 17:58:46 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
    // double dot = v1->x * v2->x + v1->y * v2->y;
    // double det = v1->x * v2->y - v1->y * v2->y;
    // return atan2(det, dot);

	return (acos(vector_mlp(v1, v2) / (vector_len(v1) * vector_len(v2))));
}