/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:15:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 07:03:07 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_params(t_all *all)
{
	all->m_speed = 0.066f;
	all->r_angle = 0.066f;
	all->frame_count = 0;
	all->r = -60;
	all->inc = 3;
	all->pmx = all->screen_w / 2;
	all->zbuf = malloc(sizeof(double) * all->map->w);
	if (!all->zbuf)
		throw_engine_error(all, ERR_CANNOT_ALLOC, 0);
	all->floor_exist = 0;
	all->sky_exist = 0;
	all->ceil_exist = 0;
	all->wp_i = 0;
	all->tpf = 0;
	v_int_init(&all->it, 0, 0);
	v_int_init(&all->scale, 1, 1);
	all->vmove = 0.0;
	all->remove = 0;
	all->kill_counter = 0;
	all->exit = 1;
	all->debug = 0;
	all->weapon_action = 0;
	all->last_frame = time(0);
	all->fps = 0;
}

void	init_all(t_all *all)
{
	init_images(all);
	init_params(all);
	init_bonus_flags(all);
	if (all->exit)
		init_window(all);
	init_mouse(all);
	if (all->exit)
		init_img(all, &all->img);
	init_keys(all);
	init_coord(all);
	init_textures(all);
	init_shadow_params(all);
	init_sprites(all);
	init_sound(all);
}

void init_sound(t_all *all) {
	soundlib_init(all);

	all->music = load_sound(all, all->map->music);
	all->sound = load_sound(all, all->map->sound);
	all->wsound = load_sound(all, all->map->wsound);
	all->csound = load_sound(all, all->map->csound);
}

void	init_vectors(t_all *all, int i, int j)
{
	if (all->map->arr[i][j] == 'N')
	{
		v_dbl_init(&all->dir, -1.0, 0.0);
		v_dbl_init(&all->plane, 0.0, 0.66);
	}
	if (all->map->arr[i][j] == 'E')
	{
		v_dbl_init(&all->dir, 0.0, 1.0);
		v_dbl_init(&all->plane, 0.66, 0);
	}
	if (all->map->arr[i][j] == 'W')
	{
		v_dbl_init(&all->dir, 0.0, -1.0);
		v_dbl_init(&all->plane, -0.66, 0);
	}
	if (all->map->arr[i][j] == 'S')
	{
		v_dbl_init(&all->dir, 1.0, 0.0);
		v_dbl_init(&all->plane, 0.0, -0.66);
	}
}

void	init_coord(t_all *all)
{
	int	i;
	int	j;

	i = 1;
	while (i < all->map->rows)
	{
		j = 1;
		while (j < all->map->cols + 1)
		{
			if (ft_strchr("NSWE", all->map->arr[i][j]))
			{
				init_vectors(all, i, j);
				v_dbl_init(&all->pos, i + 0.5, j + 0.5);
			}
			j++;
		}
		i++;
	}
	v_dbl_init(&all->norm, 0.0, 1.0);
}

void	init_shadow_params(t_all *all)
{
	t_v_dbl x;
	t_v_dbl y;
	t_v_dbl z;

	v_dbl_init(&x, 0.0f, 8.0 * all->map->h / 10);
	v_dbl_init(&y, all->map->w / 2.0, 7.5 * all->map->h / 10);
	v_dbl_init(&z, all->map->w, 8.0 * all->map->h / 10);
	all->a = ((y.y - x.y) * z.x + (y.x * x.y) - (x.x * y.y)) / (y.x - x.x);
	all->a = z.y - all->a;
	all->a /= (z.x - x.x - y.x) * z.x + (x.x * y.x);
	all->b = (y.y - x.y) / (y.x - x.x) - all->a * (x.x + y.x);
	all->c = ((y.x * x.y - x.x * y.y) / (y.x - x.x)) + all->a * x.x * y.x;
}
