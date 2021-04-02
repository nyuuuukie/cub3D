/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_get_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 02:24:22 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 04:58:13 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_fc_color(t_all *all, int *f, int *c)
{
	if (all->floor_exist || all->ceil_exist)
		calculate_floor_color(all);
	if (all->ceil_exist)
		*c = color_from_txt(&all->sky, all->tex_c.x, all->tex_c.y);
	else if (all->sky_exist)
		*c = calculate_skybox_color(all);
	else
		*c = color_from_prm(&all->map->c);
	if (all->floor_exist)
		*f = color_from_txt(&all->flr, all->tex_f.x, all->tex_f.y);
	else
		*f = color_from_prm(&all->map->f);
}

void	get_shadow_color(t_all *all, int *f, int *c)
{
	double	k;
	int		x;

	x = all->it.x;
	if (all->map->bonus && all->keys.k0)
	{
		if (all->it.y < all->a * x * x + all->b * x + all->c)
			k = 1.65;
		else
			k = 1.5;
		*f = color_make_darker(1 - (double)all->it.y / (k * all->map->h), *f);
		*c = color_make_darker(1 - (double)all->it.y / (k * all->map->h), *c);
	}
}

void	get_lightning_color(t_all *all, int *f, int *c)
{
	if (all->map->bonus && all->keys.p && is_lightning(all))
	{
		if (f != NULL)
			*f = color_negative(*f);
		if (c != NULL)
			*c = color_negative(*c);
	}
}
