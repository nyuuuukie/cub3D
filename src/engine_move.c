/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/30 06:45:00 by mhufflep         ###   ########.fr       */
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


void	remove_sprite(t_all *all, int x, int y)
{
	int i;

	i = 0;
	while (i < all->map->sprites)
	{
		if ((int)all->sprites[i].p.x == x && (int)all->sprites[i].p.y == y)
		{
			all->sprites[i].id = 'T';
			all->sprites[i].p.x = -1;
			all->sprites[i].p.y = -1;
			all->sprites[i].p.dist = -1;
		}
		i++;
	}
	
}

void	print_map(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
		ft_putendl_fd(arr[i++], 1);
}

void	move_bonus_check(t_all *all, t_vector new)
{
	calculate_weapon_offset(all);
	if (all->map->arr[(int)new.x][(int)all->pos.y] == '2' || 
		all->map->arr[(int)all->pos.x][(int)new.y] == '2')
	{
		#ifdef BONUS
			init_music(all, init_sound_fork);
		#endif
	}
	else if (all->map->arr[(int)new.x][(int)all->pos.y] == '3')
	{
		// #ifdef BONUS
		// 	init_music(all, init_sound_fork);
		// #endif
		all->coin_counter++;
		// remove_sprite(all, new.x, all->pos.y);
		all->map->arr[(int)new.x][(int)all->pos.y] = '0';
		all->sprites[all->map->sprites - 1].id = 'T';
		all->sprites[all->map->sprites - 1].p.x = -1;
		all->sprites[all->map->sprites - 1].p.y = -1;
		all->sprites[all->map->sprites - 1].p.dist = -1;
		// print_map(all->map->arr);
	}
	else if (all->map->arr[(int)all->pos.x][(int)new.y] == '3')
	{
		// #ifdef BONUS
		// 	init_music(all, init_sound_fork);
		// #endif
		all->coin_counter++;
		// remove_sprite(all, new.x, all->pos.y);
		all->map->arr[(int)all->pos.x][(int)new.y] = '0';
		all->sprites[all->map->sprites - 1].id = 'T';
		all->sprites[all->map->sprites - 1].p.x = -1;
		all->sprites[all->map->sprites - 1].p.y = -1;
		all->sprites[all->map->sprites - 1].p.dist = -1;
		// print_map(all->map->arr);
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
