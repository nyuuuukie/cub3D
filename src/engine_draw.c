/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:28:33 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_all(t_all *all)
{
	draw_walls(all);
	if (all->map->sprites > 0)
		draw_sprites(all);
	draw_bonus_part(all);
}

void	draw_background(t_all *all)
{
	t_v_dbl k;
	t_v_dbl floor_wall;

	calculate_wall_prm(all, &floor_wall, &k);
	all->it.y = all->map->h / 2;
	while (all->it.y < all->map->h)
	{
		draw_floor_ceil(all);
		all->it.y++;
	}
}

void	draw_walls(t_all *all)
{
	all->it.x = 0;
	while (all->it.x < all->map->w)
	{
		v_dbl_init(&all->cam, 2.0 * all->it.x / all->map->w - 1, 0.0);
		all->ray.x = all->dir.x + all->plane.x * all->cam.x;
		all->ray.y = all->dir.y + all->plane.y * all->cam.x;
		v_dbl_init(&all->delta, fabs(1 / all->ray.x), fabs(1 / all->ray.y));
		v_int_init(&all->grid, all->pos.x, all->pos.y);
		recognize_texture(all);
		calculate_initial_dist(all);
		calculate_collision_coordinates(all);
		calculate_distance_to_wall(all);
		calculate_wall_borders(all);
		calculate_texture_coordinates(all);
		draw_background(all);
		draw_wall_line(all);
		all->it.x++;
	}
}

void	draw_floor_ceil(t_all *all)
{
	int	f;
	int	c;

	get_fc_color(all, &f, &c);
	get_shadow_color(all, &f, &c);
	get_lightning_color(all, &f, &c);
	put_pixel(&all->img, all->it.x, all->it.y, f);
	put_pixel(&all->img, all->it.x, all->map->h - all->it.y - 1, c);
}
