/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:30:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 19:31:08 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_images(t_all *all)
{
	int i;

	i = 0;
	all->img.img = NULL;
	all->no.img.img = NULL;
	all->so.img.img = NULL;
	all->ea.img.img = NULL;
	all->we.img.img = NULL;
	all->s1.img.img = NULL;
	all->s2.img.img = NULL;
	all->flr.img.img = NULL;
	all->sky.img.img = NULL;
	while (i < ANIM_FRAMES)
		all->wpn[i++].img.img = NULL;
}

void	init_screen_size(t_all *all)
{
	get_screen_size(all);
	if (all->screen == 0)
	{
		if (all->map->h > all->screen_h)
			all->map->h = all->screen_h;
		if (all->map->w > all->screen_w)
			all->map->w = all->screen_w;
	}
	else
	{
		if (all->map->h > 20000)
			all->map->h = 20000;
		if (all->map->w > 20000)
			all->map->w = 20000;
	}
}

void	init_sprites(t_all *all)
{
	int i;
	int j;
	int n;

	i = 0;
	n = 0;
	all->sprites = malloc(sizeof(t_sprite) * all->map->sprites);
	if (!all->sprites)
		throw_engine_error(all, ERR_CANNOT_ALLOC, "Sprites");
	while (i < all->map->rows && n < all->map->sprites)
	{
		j = 0;
		while (j < all->map->cols && n < all->map->sprites)
		{
			if (ft_strchr(SPRITES, all->map->arr[i][j]))
			{
				all->sprites[n].id = all->map->arr[i][j];
				v_dbl_init(&(all->sprites[n++].p), i + 0.5, j + 0.5);
			}
			j++;
		}
		i++;
	}
}
