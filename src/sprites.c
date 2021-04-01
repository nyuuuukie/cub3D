/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 04:44:36 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 06:33:24 by mhufflep         ###   ########.fr       */
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
