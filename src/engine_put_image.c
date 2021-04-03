/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_put_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:37:44 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 12:55:33 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	*(int*)(img->addr + y * img->len + x * 4) = color;
}

void	draw_wall_pixel(t_all *all)
{
	int c;

	c = color_from_txt(all->cur, all->tex.x, all->tex.y);
	if (all->map->bonus && all->keys.k0)
		c = color_make_darker(all->dist_to_wall / 10, c);
	get_lightning_color(all, 0, &c);
	put_pixel(&all->img, all->it.x, all->it.y, c);
}

void	draw_wall_line(t_all *all)
{
	double	step;
	double	tex_p;

	step = 1.0 * all->cur->w / all->wall_h;
	tex_p = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;
	all->it.y = all->wall_beg;
	while (all->it.y < all->wall_end)
	{
		all->tex.y = (int)tex_p;
		tex_p += step;
		draw_wall_pixel(all);
		all->it.y++;
	}
}
