/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:15:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/30 02:41:30 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_mouse(t_all *all)
{
	int h;
	int w;
	
	if (all->map->bonus && all->screen == 0)
	{
		h = all->screen_h / 2;
		w = all->screen_w / 2;
		#ifdef LINUX
			mlx_mouse_move(all->mlx, all->win, w, h);
		#else
			mlx_mouse_move(all->win, w, h);
		#endif
	}
}

void 	init_params(t_all *all)
{
	all->m_speed = 0.066f;
	all->r_angle = 0.066f;
	all->frame_count = 0;
	all->r = -60;
	all->inc = 3;
	all->offset = 0;
	all->pmx = all->screen_w / 2;
	all->ZBuffer = malloc(sizeof(double) * all->map->w);

	all->floor_exist = 0;
	all->sky_exist = 0;
	all->ceil_exist = 0;
	all->wp_i = 0;
	if (!all->ZBuffer)
		throw_engine_error(all, ERR_CANNOT_ALLOC, 0);
	all->coin_counter = 0;
	all->sound_started = 0;
	all->wsound_started = 0;
	all->music_started = 0;
	vector_int_init(&all->scale, 1, 1);
	all->vmove = 0.0;
}

void	init_all(t_all *all)
{
	init_images(all);
	init_params(all);
	init_bonus_flags(all);
	init_window(all);
	init_mouse(all);
	init_img(all, &all->img);
	init_keys(all);
	init_coord(all);
	init_textures(all);
	init_shadow_params(all);
	init_sprites(all);
}

void	init_vectors(t_all *all, int i, int j)
{
	if (all->map->arr[i][j] == 'N')
	{
		vector_init(&all->dir, -1.0, 0.0);
		vector_init(&all->plane, 0.0, 0.66);
	}
	if (all->map->arr[i][j] == 'E')
	{
		vector_init(&all->dir, 0.0, 1.0);
		vector_init(&all->plane, 0.66, 0);
	}
	if (all->map->arr[i][j] == 'W')
	{
		vector_init(&all->dir, 0.0, -1.0);
		vector_init(&all->plane, -0.66, 0);
	}
	if (all->map->arr[i][j] == 'S')
	{
		vector_init(&all->dir, 1.0, 0.0);
		vector_init(&all->plane, 0.0, -0.66);
	}
}

void	init_coord(t_all *all)
{
 	int i;
 	int j;

 	i = 1;
 	while (i < all->map->rows)
 	{
 		j = 1;
 		while (j < all->map->cols + 1)
 		{	
			if (ft_strchr("NSWE", all->map->arr[i][j]))
 			{
				init_vectors(all, i, j);
				vector_init(&all->pos, i + 0.5, j + 0.5);
			}
 			j++;
 		}
 		i++;
	}
	vector_init(&all->norm, 0.0, 1.0);	
}

void	init_shadow_params(t_all *all)
{
	t_vector x;
	t_vector y;
	t_vector z;
	
	vector_init(&x, 0.0f, 8.0 * all->map->h / 10);
	vector_init(&y, all->map->w / 2.0, 7.5 * all->map->h / 10);
	vector_init(&z, all->map->w, 8.0 * all->map->h / 10);
	all->a = ((y.y - x.y) * z.x + (y.x * x.y) - (x.x * y.y)) / (y.x - x.x);
	all->a = z.y - all->a;
	all->a /= (z.x - x.x - y.x) * z.x + (x.x * y.x);
	all->b = (y.y - x.y) / (y.x - x.x) - all->a * (x.x + y.x);
	all->c = ((y.x * x.y - x.x * y.y) / (y.x - x.x)) + all->a * x.x * y.x;
}