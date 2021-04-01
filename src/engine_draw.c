/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:28:33 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 02:12:52 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		draw_all(t_all *all)
{
	draw_walls(all);
	if (all->map->sprites > 0)
		draw_sprites(all);
	draw_bonus_part(all);
	return (0);
}

void	draw_background(t_all *all)
{
	t_v_dbl k;
	t_v_dbl floor_wall;

	calculate_wall_prm(all, &floor_wall, &k);
	all->it.y = all->map->h / 2;
	while (all->it.y < all->map->h)
	{
		draw_floor_ceil(all, all->it.x, all->it.y);
		all->it.y++;
	}
}

void	draw_walls(t_all *all)
{
	all->it.x = 0;
	while (all->it.x < all->map->w)
	{
		v_dbl_init(&all->cam, 2.0 * all->it.x / all->map->w - 1, 0.0);
		v_dbl_init(&all->ray,  all->dir.x + all->plane.x * all->cam.x, \
								all->dir.y + all->plane.y * all->cam.x);
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

void	draw_floor_ceil(t_all *all, int x, int y)
{
	int		f;
	int		c;
	double	k;

	if (all->floor_exist || all->ceil_exist)
		calculate_floor_color(all, y);

	if (all->floor_exist)
		f = color_from_txt(&all->flr, all->tex_f.x, all->tex_f.y);
	else
		f = color_from_prm(&all->map->f);

	if (all->ceil_exist)
		c = color_from_txt(&all->sky, all->tex_c.x, all->tex_c.y);
	else if (all->sky_exist)
		c = calculate_skybox_color(all, all->map->h - y);
	else
		c = color_from_prm(&all->map->c);

	if (all->keys.k0)
	{
		if (y < all->a * x * x + all->b * x + all->c)
			k = 1.65;
		else
			k = 1.5;
		f = color_make_darker(1 - (double)y / (k * all->map->h), f);
		c = color_make_darker(1 - (double)y / (k * all->map->h), c);
	}
	if (all->map->bonus && all->keys.p && is_lightning(all))
		f = color_negative(f);
	if (all->map->bonus && all->keys.p && is_lightning(all))
		c = color_negative(c);
	put_pixel(&all->img, x, y, f);
	put_pixel(&all->img, x, all->map->h - y - 1, c);
}
