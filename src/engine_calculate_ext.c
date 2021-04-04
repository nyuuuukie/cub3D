/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_calculate_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:33:20 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 20:04:14 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calculate_floor_ceil_text_coord(t_all *all)
{
	v_int_init(&all->tex_f, (int)(all->floor.x * all->flr.w) % all->flr.w,
							(int)(all->floor.y * all->flr.h) % all->flr.h);
	v_int_init(&all->tex_c, (int)(all->floor.x * all->cl.w) % all->cl.w,
							(int)(all->floor.y * all->cl.h) % all->cl.h);
	return (0);
}

void	calculate_wall_prm(t_all *all, t_v_dbl *f_w, t_v_dbl *k)
{
	v_dbl_init(k, (all->ray.x < 0), (all->ray.y < 0));
	if (all->side_wall == 0)
		v_dbl_init(f_w, all->grid.x + k->x, all->grid.y + all->ratio);
	else
		v_dbl_init(f_w, all->grid.x + all->ratio, all->grid.y + k->y);
}

int		calculate_floor_color(t_all *all)
{
	double	w;

	w = all->map->h / (2.0 * all->it.y - all->map->h) / (all->dist_to_wall);
	all->floor.x = w * all->f_w.x + (1.0 - w) * all->pos.x;
	all->floor.y = w * all->f_w.y + (1.0 - w) * all->pos.y;
	calculate_floor_ceil_text_coord(all);
	return (0);
}

int		calculate_skybox_color(t_all *all)
{
	int x;
	int y;

	x = all->n / 360.0 * all->sky.w;
	y = 1.0 * (all->map->h - all->it.y) / all->map->h * all->sky.h;
	return (color_from_txt(&all->sky, x, y));
}

void	calculate_weapon_offset(t_all *all)
{
	if ((int)all->r > -1 || (int)all->r < -60)
		all->inc *= -1;
	all->r += all->inc;
}
