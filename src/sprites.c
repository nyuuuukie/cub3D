/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 04:44:36 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 20:43:24 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	remove_sprite(t_all *all, int x, int y)
{
	int i;

	i = 0;
	while (i < all->map->sprites)
	{
		if ((int)all->sprites[i].p.x == x && (int)all->sprites[i].p.y == y)
		{
			all->map->arr[x][y] = '0';
			all->sprites[i].id = 'X';
			all->sprites[i].p.x = -1;
			all->sprites[i].p.y = -1;
			all->sprites[i].p.dist = -1;
			break ;
		}
		i++;
	}
}

void	sort_sprites(t_all *all)
{
	int i;

	i = 0;
	while (i < all->map->sprites - 1)
	{
		if (all->sprites[i].p.dist < all->sprites[i + 1].p.dist)
		{
			swap_d_values(&all->sprites[i].p.x, &all->sprites[i + 1].p.x);
			swap_d_values(&all->sprites[i].p.y, &all->sprites[i + 1].p.y);
			swap_c_values(&all->sprites[i].id, &all->sprites[i + 1].id);
			swap_d_values(&all->sprites[i].p.dist, &all->sprites[i + 1].p.dist);
			i = -1;
		}
		i++;
	}
}

void	calculate_dist_to_sprites(t_all *all)
{
	t_v_dbl a;
	int i;

	i = 0;
	while (i < all->map->sprites)
	{
		a.x = all->pos.x - all->sprites[i].p.x;
		a.y = all->pos.y - all->sprites[i].p.y;
		// v_dbl_init(&a, all->pos.x - all->sprites[i].p.x, all->pos.y - all->sprites[i].p.y);
		all->sprites[i].p.dist = a.x * a.x + a.y * a.y;
		i++;
	}
}