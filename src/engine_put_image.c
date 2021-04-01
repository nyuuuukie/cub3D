/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_put_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:37:44 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 02:13:59 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	*(int*)(img->addr + y * img->len + x * (img->bpp / 8)) = color;
}


void	calculate_wall_prm(t_all *all, t_v_dbl *floor_wall, t_v_dbl *k)
{
	v_dbl_init(k, (all->ray.x < 0), (all->ray.y < 0));
	if (all->side_wall == 0)
		v_dbl_init(floor_wall, all->grid.x + k->x, all->grid.y + all->ratio);
    else
		v_dbl_init(floor_wall, all->grid.x + all->ratio, all->grid.y + k->y);
}

void	draw_wall_line(t_all *all)
{
	t_v_dbl	floor_wall;
	t_v_dbl	k;
	double	step;
	double	tex_p;

	calculate_wall_prm(all, &floor_wall, &k);
	step = 1.0 * all->cur->w / all->wall_h;
	tex_p = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;
	all->it.y = 0;
	while (all->it.y < all->map->h)
	{
		if (all->it.y > all->wall_beg && all->it.y <= all->wall_end) 
		{
			all->tex.y = (int)tex_p; 
			tex_p += step;
			all->color = color_from_txt(all->cur, all->tex.x, all->tex.y);
			if (all->map->bonus && all->keys.k0)
				all->color = color_make_darker(all->dist_to_wall / 20, all->color);
			if (all->map->bonus && all->keys.p && is_lightning(all))
				all->color = color_negative(all->color);
			if ((all->color & 0x00FFFFFF) != 0)
				put_pixel(&all->img, all->it.x, all->it.y, all->color);
		}
		all->it.y++;
	}	
}
