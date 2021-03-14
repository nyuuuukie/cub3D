/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/14 17:28:49 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate(t_all *all, int sign)
{
	vector_rotate(&all->dir, sign * all->r_angle);
	vector_rotate(&all->plane, sign * all->r_angle);                                                                            
}

void	move(t_all *all, t_vector *base, int sign)
{
	t_vector	new;

	new.x = all->pos.x + (sign * base->x * all->m_speed);
	new.y = all->pos.y + (sign * base->y * all->m_speed);
	if (all->map->arr[(int)new.x][(int)all->pos.y] != '1')
		all->pos.x = new.x;
	if (all->map->arr[(int)all->pos.x][(int)new.y] != '1')
		all->pos.y = new.y;
}
