/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:32:24 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 19:47:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite_parameteres(t_all *all, int i)
{
	all->d.x = all->sprites[i].p.x - all->pos.x;
	all->d.y = all->sprites[i].p.y - all->pos.y;

	all->det = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y);

	all->t.x = all->det * (all->dir.y * all->d.x - all->dir.x * all->d.y);
	all->t.y = all->det * (-all->plane.y * all->d.x + all->plane.x * all->d.y);
	all->sp_scr_x = (int)((all->map->w / 2) * (1 + all->t.x / all->t.y));
	all->vm_scr = (int)(all->vmove / all->t.y);
	v_int_init(&all->s_size, abs((int)(all->map->w / all->t.y)) / all->scale.x,
							abs((int)(all->map->h / all->t.y)) / all->scale.y);
	v_int_init(&all->s_beg, -all->s_size.x / 2 + all->sp_scr_x, 
					-all->s_size.y / 2 + all->map->h / 2 + all->vm_scr);
	v_int_init(&all->s_end, all->s_size.x / 2 + all->sp_scr_x, 
					all->s_size.y / 2 + all->map->h / 2 + all->vm_scr);
}

void	check_sprite_parameters(t_all *all, int i)
{
	if (all->s_beg.y < 0)
		all->s_beg.y = 0;
	if (all->s_end.y >= all->map->h)
		all->s_end.y = all->map->h;
	if (all->s_beg.x < 0) 
		all->s_beg.x = 0;
	if (all->s_end.x >= all->map->w) 
		all->s_end.x = all->map->w;
	
	if (all->sprites[i].id == '2')
		all->s = &(all->s1);
	else
		all->s = &(all->s2);
	if (all->sprites[i].id == 'T' || all->sprites[i].id == 'H')
		all->s = &(all->tp[all->tpf]);
}

void	draw_sprite_line(t_all *all, int i, int sx)
{
	int sy;
	int d;

	sy = all->s_beg.y;
	while (sy < all->s_end.y)
	{
		d = (sy - all->vm_scr) * 256 - all->map->h * 128 + all->s_size.y * 128;
		all->tex.y = ((d * all->s->h) / all->s_size.y) / 256;
		if (all->tex.x >= 0 && all->tex.x <= all->s->w &&
			all->tex.y >= 0 && all->tex.y <= all->s->h)
			all->color = color_from_txt(all->s, all->tex.x, all->tex.y);
		else
			all->color = 0x00000000;
		if (all->map->bonus && all->keys.k0)
			all->color = color_make_darker(all->sprites[i].p.dist / 40, all->color);
		if ((all->color & 0x00FFFFFF) != 0)
			put_pixel(&all->img, sx, sy, all->color);
		sy++;
	}
}

void	draw_sprite(t_all *all, int i)
{
	int sx;

	sx = all->s_beg.x;
	while (sx < all->s_end.x)
	{
		all->tex.x = (int)(256 * (sx - (-all->s_size.x / 2 + all->sp_scr_x)) * all->s->w / all->s_size.x) / 256 + 1;
		if (all->t.y > 0 && all->t.y < all->zbuf[sx])
		{
			if (sx > 0 && sx < all->map->w)
				draw_sprite_line(all, i, sx);
		}
		sx++;
	}
}

void	draw_sprites(t_all *all)
{
	int i;

	calculate_dist_to_sprites(all);
	if (all->map->sprites > 1)
		sort_sprites(all);
	i = 0;
	while (i < all->map->sprites)
	{
		init_sprite_parameteres(all, i);
		check_sprite_parameters(all, i);
		draw_sprite(all, i);
		i++;
	}
}