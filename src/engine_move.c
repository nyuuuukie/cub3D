/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/21 09:24:56 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate(t_all *all, int sign)
{
	vector_rotate(&all->dir, sign * all->r_angle);
	vector_rotate(&all->plane, sign * all->r_angle);                                                                            
}


void	rotate_m(t_all *all, double angle)
{
	vector_rotate(&all->dir, angle);
	vector_rotate(&all->plane, angle);                                                                            
}

void	move(t_all *all, t_vector *base, int sign)
{
	t_vector	new;
	all->offset += sign * 0.05; //HERE!!!
 
	new.x = all->pos.x + (sign * base->x * all->m_speed * all->k_speed);
	new.y = all->pos.y + (sign * base->y * all->m_speed * all->k_speed);
	if (!ft_strchr("21", all->map->arr[(int)new.x][(int)all->pos.y]))
		all->pos.x = new.x;
	if (!ft_strchr("21", all->map->arr[(int)all->pos.x][(int)new.y]))
		all->pos.y = new.y;
}
