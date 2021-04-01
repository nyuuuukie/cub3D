/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_put_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:37:44 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 20:38:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    put_pixel(t_img *img, int x, int y, int color)
{
	*(int*)(img->addr + y * img->len + x * (img->bpp / 8)) = color;
}

void	put_column(t_all *all, int x)
{
	double step = 1.0 * all->cur->w / all->wall_h;
	double texPos = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;

	t_v_dbl k;
	t_v_dbl floor_wall;
	v_dbl_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	
	if (all->side_wall == 0)
		v_dbl_init(&floor_wall, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		v_dbl_init(&floor_wall, all->grid.x + all->ratio, all->grid.y + k.y);

	for (int y = 0; y < all->map->h; y++)
	{
		if (y > all->wall_beg && y <= all->wall_end) 
		{
			all->tex.y = (int)texPos; 
			texPos += step;
		 	
			all->color = color_from_txt(all->cur, all->tex.x, all->tex.y);
			#ifdef BONUS
			 	if (all->keys.k0)
			 		all->color = color_make_darker(all->dist_to_wall / 20, all->color);				
				if (all->keys.p && is_lightning(all)) //(all->frame_count % 100 < 5 || (all->frame_count % 100 > 20 && all->frame_count % 100 < 25)))
					all->color = color_negative(all->color);
			#endif
			if ((all->color & 0x00FFFFFF) != 0)
				put_pixel(&all->img, x, y, all->color);
		}
	}	
}