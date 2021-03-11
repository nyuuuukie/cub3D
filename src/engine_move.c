/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/11 21:45:00 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate(t_all *all, int sign)
{
	double oldDirX = all->dir.x;
	all->dir.x = all->dir.x * cos(sign * all->r_angle) - all->dir.y * sin(sign * all->r_angle);
	all->dir.y = oldDirX * sin(sign * all->r_angle) + all->dir.y * cos(sign * all->r_angle);

	double oldPlaneX = all->plane.x;
	all->plane.x = all->plane.x * cos(sign * all->r_angle) - all->plane.y * sin(sign * all->r_angle);
	all->plane.y = oldPlaneX * sin(sign * all->r_angle) + all->plane.y * cos(sign * all->r_angle);
		
	all->angle += all->r_angle * 180 / M_PI * -sign;
}

void	move_side(t_all *all, int sign)
{
	t_vector	new;
 
	new.x = all->pos.x + (sign * all->dir.y * all->m_speed);
	new.y = all->pos.y + (sign * all->dir.x * all->m_speed);
	if (all->map->arr[(int)new.x][(int)all->pos.y] != '1')
		all->pos.x = new.x;
	if (all->map->arr[(int)all->pos.x][(int)new.y] != '1')
		all->pos.y = new.y;
}

void	move(t_all *all, int sign)
{
	t_vector	new;

	new.x = all->pos.x + (sign * all->dir.x * all->m_speed);
	new.y = all->pos.y + (sign * all->dir.y * all->m_speed);
	if (all->map->arr[(int)new.x][(int)all->pos.y] != '1')
		all->pos.x = new.x;
	if (all->map->arr[(int)all->pos.x][(int)new.y] != '1')
		all->pos.y = new.y;
}