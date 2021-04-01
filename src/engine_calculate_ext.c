/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_calculate_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:33:20 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 20:34:36 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		calculate_floor_ceil_text_coord(t_all *all)
{
	v_int_init(&all->tex_f, (int)(all->floor.x * all->flr.w) % all->flr.w,
						  (int)(all->floor.y * all->flr.h) % all->flr.h);
	v_int_init(&all->tex_c, (int)(all->floor.x * all->sky.w) % all->sky.w, 
						  (int)(all->floor.y * all->sky.h) % all->sky.h);
	return (0);
}

int		calculate_floor_color(t_all *all, int y)
{
	double w;
	t_v_dbl k;
	t_v_dbl f_w;
	
	v_dbl_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	if (all->side_wall == 0)
		v_dbl_init(&f_w, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		v_dbl_init(&f_w, all->grid.x + all->ratio, all->grid.y + k.y);
	w = all->map->h / (2.0 * y - all->map->h) / (all->dist_to_wall);
	v_dbl_init(&all->floor, w * f_w.x + (1.0 - w) * all->pos.x,
							 w * f_w.y + (1.0 - w) * all->pos.y);
	calculate_floor_ceil_text_coord(all);
	return (0);
}

int		calculate_skybox_color(t_all *all, int y)
{
	return (color_from_txt(&all->sky, (all->n / 360.0 * all->sky.w), \
								(1.0 * y / all->map->h * all->sky.h)));
}