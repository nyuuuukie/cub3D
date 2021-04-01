/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:32:24 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 20:42:23 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_sprites(t_all *all)
{
	double det;
	
	calculate_dist_to_sprites(all);

	if (all->map->sprites > 1)
		sort_sprites(all);

	for (int i = 0; i < all->map->sprites; i++)
    {
		t_texture *s;

		if ((all->sprites[i].id == 'T' || all->sprites[i].id == 'H') && all->map->keys != 0)
			continue;
		
		v_dbl_init(&all->d, all->sprites[i].p.x - all->pos.x, 
						all->sprites[i].p.y - all->pos.y);

		det = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y);

		v_dbl_init(&all->t, det * (all->dir.y * all->d.x - all->dir.x * all->d.y),
							det * (-all->plane.y * all->d.x + all->plane.x * all->d.y));

		all->sp_scr_x = (int)((all->map->w / 2) * (1 + all->t.x / all->t.y));

		all->vm_scr = (int)(all->vmove / all->t.y);

		v_int_init(&all->s_size, abs((int)(all->map->w / all->t.y)) / all->scale.x,
								  	  abs((int)(all->map->h / all->t.y)) / all->scale.y);
		v_int_init(&all->s_beg, -all->s_size.x / 2 + all->sp_scr_x, 
						-all->s_size.y / 2 + all->map->h / 2 + all->vm_scr);
		v_int_init(&all->s_end, all->s_size.x / 2 + all->sp_scr_x, 
						all->s_size.y / 2 + all->map->h / 2 + all->vm_scr);

		if (all->s_beg.y < 0)
			all->s_beg.y = 0;
		if (all->s_end.y >= all->map->h)
			all->s_end.y = all->map->h;
		if (all->s_beg.x < 0) 
			all->s_beg.x = 0;
		if (all->s_end.x >= all->map->w) 
			all->s_end.x = all->map->w;
		
		if (all->sprites[i].id == '2')
			s = &(all->s1);
		else
			s = &(all->s2);
			
		if (all->sprites[i].id == 'T' || all->sprites[i].id == 'H')
			s = &(all->tp[all->tpf]);
		
		for (int sx = all->s_beg.x; sx < all->s_end.x; sx++)
		{
			all->tex.x = (int)(256 * (sx - (-all->s_size.x / 2 + all->sp_scr_x)) * s->w / all->s_size.x) / 256 + 1;
			
			if (all->t.y > 0 && sx > 0 && sx < all->map->w && all->t.y < all->zbuf[sx])
			{
				for (int sy = all->s_beg.y; sy < all->s_end.y; sy++) 
				{
					int d = (sy - all->vm_scr) * 256 - all->map->h * 128 + all->s_size.y * 128;
					all->tex.y = ((d * s->h) / all->s_size.y) / 256;
					
					if (all->tex.x >= 0 && all->tex.x <= s->w && all->tex.y >= 0 && all->tex.y <= s->h)
						all->color = color_from_txt(s, all->tex.x, all->tex.y);
					else
						all->color = 0x00000000;
					
					if ((all->color & 0x00FFFFFF) != 0)
					{
						if (all->map->bonus && all->keys.k0)
							all->color = color_make_darker(all->sprites[i].p.dist / 40, all->color);
						put_pixel(&all->img, sx, sy, all->color);
					}
				}	
			}
		}
	}
}