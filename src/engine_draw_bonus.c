/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:35:08 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 03:59:36 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rain(t_all *all)
{
	int x;
	int drop_len;

	x = -1;
	while (++x < all->map->w)
	{
		if (all->zbuf[x] > 0.5)
		{
			all->it.y = random_number(0, all->map->h / 6 + 1);
			while (all->it.y < all->map->h)
			{
				if (rand() % 2 == 0)
					drop_len = random_number(1, 5);
				else
					drop_len = random_number(5, 30);
				while (drop_len-- && all->it.y < all->map->h)
				{
					if (all->it.y < all->a * x * x + all->b * x || x % 5 == 0)
						put_pixel(&all->img, x, all->it.y, 0x006F6F6F);
					all->it.y++;
				}
				all->it.y += random_number(50, 70);
			}
		}
	}
}

void	draw_weapon(t_all *all)
{
	t_v_int tex;
	int		y;
	int		x;

	x = 0;
	while (x < all->map->w)
	{
		y = all->map->h / 2 - 60;
		tex.x = 1.0 * x / all->map->w * all->wpn[all->wp_i].w;
		while (y < all->map->h)
		{
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
	int xt;
	int yt;
	int color;

	i = 0;
	while (i < all->num_scale)
	{
		j = 0;
		yt = 1.0 * all->digits[num].w * i / all->num_scale;
		while (j < all->num_scale)
		{
			xt = 1.0 * all->digits[num].w * j / all->num_scale;
			color = color_from_txt(&all->digits[num], xt, yt);
			if ((color & 0xFFFFFFFF) == 0)
				put_pixel(&all->img, x + j, y + i, color_negative(color));
			j++;
		}
		i++;
	}
}

void	draw_hud(t_all *all)
{
	int xr;
	int count;

	all->num_scale = all->map->h / 20 + 1;
	xr = all->map->w - 10;
	count = all->map->keys;
	while (count != 0)
	{
		xr -= all->num_scale;
		draw_number(all, xr, 10, count % 10);
		count /= 10;
	}
	count = all->kill_counter;
	xr = all->num_scale * 4 + 10;
	while (count != 0)
	{
		xr -= all->num_scale;
		draw_number(all, xr, 10, count % 10);
		count /= 10;
	}
}
