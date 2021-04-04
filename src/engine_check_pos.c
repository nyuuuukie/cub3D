/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_check_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:54:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 04:51:59 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_pos(t_all *all, char t)
{
	int i;
	int j;

	i = 0;
	while (all->map->rows - 1)
	{
		j = 0;
		while (all->map->arr[i][j] != '\0')
		{
			if (all->map->arr[i][j] == t)
			{
				all->pos.x = i + 0.5 + 1 * roundf(all->dir.y);
				all->pos.y = j + 0.5 + 1 * roundf(all->dir.x);
				all->sky_exist = !all->sky_exist;
				all->ceil_exist = !all->ceil_exist;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	check_map_position(t_all *all, int x, int y)
{
	if (all->map->arr[x][y] == '2')
	{
		init_music(all, init_sound_fork);
	}
	else if (all->map->arr[x][y] == '3')
	{
		init_music(all, init_csound_fork);
		all->map->keys--;
		remove_sprite(all, x, y);
	}
	else if (all->map->arr[x][y] == 'O')
	{
		next_level(all);
	}
	else if (all->map->keys == 0)
	{
		if (all->map->arr[x][y] == 'T')
			change_pos(all, 'H');
		else if (all->map->arr[x][y] == 'H')
			change_pos(all, 'T');
	}
}

void	move_bonus_check(t_all *all, t_v_dbl new)
{
	calculate_weapon_offset(all);
	check_map_position(all, new.x, all->pos.y);
	check_map_position(all, all->pos.x, new.y);
}
