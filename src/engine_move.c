/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/25 14:51:37 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate(t_all *all, int sign, double angle)
{
	vector_rotate(&all->dir, sign * angle);
	vector_rotate(&all->plane, sign * angle);                                                                            
}


//MOVE
void	calculate_weapon_offset(t_all *all)
{
	if ((int)all->r > -1 || (int)all->r < -60) //make constant
		all->inc *= -1;
	all->r += all->inc;
}

void	move_bonus_check(t_all *all, t_vector new)
{
	calculate_weapon_offset(all);
	//collision with '3' sprite ?
	if (all->map->arr[(int)new.x][(int)all->pos.y] == '2' || 
		all->map->arr[(int)all->pos.x][(int)new.y] == '2')
	{
		#ifdef BONUS
			init_music(all);
		#endif
	}
}



void	move(t_all *all, t_vector *base, int sign)
{
	t_vector	new;
 
	new.x = all->pos.x + (sign * base->x * all->m_speed * all->k_speed);
	new.y = all->pos.y + (sign * base->y * all->m_speed * all->k_speed);
	if (!ft_strchr("321", all->map->arr[(int)new.x][(int)all->pos.y]))
		all->pos.x = new.x;
	if (!ft_strchr("321", all->map->arr[(int)all->pos.x][(int)new.y]))
		all->pos.y = new.y;
	
	if (all->map->bonus)
		move_bonus_check(all, new);	
}
