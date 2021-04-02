/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:35:08 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 06:15:16 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rain(t_all *all)
{
	int y;
	int x;
	int big;
	int small;
	int drop_len;

	x = 0;
	while (x < all->map->w)
	{
		if (all->zbuf[x] > 0.5)
		{
			small = random_number(1, 15);
			big = random_number(5, 30);
			y = random_number(0, all->map->h / 6 + 1);
			while (y < all->map->h)
			{
				if (y < all->wall_beg)
					drop_len = small;
				else
					drop_len = big;
				while (drop_len-- && y < all->map->h)
				{
					if (y < all->a * x * x + all->b * x || x % 5 == 0)
						put_pixel(&all->img, x, y, 0x006F6F6F);
					y++;
				}
				y += random_number(50, 70);
			}
		}
		x++;
	}
}

void	draw_weapon(t_all *all)
{
	t_v_int tex;
	int y;
	int x;

	x = 0;
	while (x < all->map->w)
	{
		y = 0;
		while (y < all->map->h)
		{
			tex.x = 1.0 * x / all->map->w * all->wpn[all->wp_i].w;
			tex.y = 1.0 * y / all->map->h * all->wpn[all->wp_i].h + all->r;
			all->color = color_from_txt(&all->wpn[all->wp_i], tex.x, tex.y);
			if ((all->color & 0x00FFFFFF) != 0)
				put_pixel(&all->img, x, y, all->color);
			y++;
		}
		x++;
	}
}

void	draw_number(t_all *all, int x, int y, int num)
{
	int i;
	int j;
	int scale;
	int color;
	
	i = 0;
	scale = all->map->h / 20 + 1;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			color = color_from_txt(&all->digits[num], 
				1.0 * all->digits[num].w * j / scale, 
					1.0 * all->digits[num].w * i / scale);
			if ((color & 0xFFFFFFFF) == 0)
				put_pixel(&all->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_hud(t_all *all)
{
	int x;
	int count;
	
	x = all->map->w - 10; 
	count = all->map->keys;
	while (count != 0)
	{
		x -= all->map->h / 20 + 1;
		draw_number(all, x, 10, count % 10);
		count /= 10;
	}
}
