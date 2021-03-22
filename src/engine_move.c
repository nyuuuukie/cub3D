/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/22 18:57:36 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate(t_all *all, int sign, double angle)
{
	vector_rotate(&all->dir, sign * angle);
	vector_rotate(&all->plane, sign * angle);                                                                            
}

void *init_fork(void * prm)
{
	t_all *all = (t_all*)prm;
	if (!all->started)
	{
		all->started = 1;
		sound_start(all, &all->sound, all->map->sound);
		waitpid(all->sound, 0, 0);
		all->started = 0;
	}
	return (NULL);
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
	
	if (all->map->arr[(int)new.x][(int)all->pos.y] == '2' || 
		all->map->arr[(int)all->pos.x][(int)new.y] == '2')
	{
		if (!all->started)
		{
			pthread_create(&all->pmusic, NULL, init_fork, all);
			pthread_detach(all->pmusic);
		}
	}
}
