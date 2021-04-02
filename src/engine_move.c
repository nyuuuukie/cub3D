/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_all *all, int sign, double angle)
{
	v_dbl_rotate(&all->dir, sign * angle);
	v_dbl_rotate(&all->plane, sign * angle);
}

void	calculate_weapon_offset(t_all *all)
{
	if ((int)all->r > -1 || (int)all->r < -60)
		all->inc *= -1;
	all->r += all->inc;
}

void	print_map(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
		ft_putendl_fd(arr[i++], 1);
}

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
				all->pos.x = i + 0.5 + 1 * all->dir.y;
				all->pos.y = j + 0.5 + 1 * all->dir.x;
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

void	move(t_all *all, t_v_dbl *base, int sign)
{
	t_v_dbl	new;

	new.x = all->pos.x + (sign * base->x * all->m_speed * all->k_speed);
	new.y = all->pos.y + (sign * base->y * all->m_speed * all->k_speed);
	if (!ft_strchr("321", all->map->arr[(int)new.x][(int)all->pos.y]))
		all->pos.x = new.x;
	if (!ft_strchr("321", all->map->arr[(int)all->pos.x][(int)new.y]))
		all->pos.y = new.y;
	if (all->map->bonus)
		move_bonus_check(all, new);
}
