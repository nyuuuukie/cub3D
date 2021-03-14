/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:15:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/14 18:17:12 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_all(t_all *all)
{
	all->m_speed = 0.066f;
	all->r_angle = 0.066f;

	init_window(all);	
	init_img(all, &all->img);
	init_keys(all);
	init_coord(all);
	init_textures(all);
	init_shadow_params(all);
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
	// printf("x = %.3f y= %.3f\n", i + 0.5, j + 0.5);
	// printf("dir[%.3f %.3f]\n", all->dir.x, all->dir.y);
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
	
	vector_init(&x, 0.0f, 9 * (double)all->map->h / 10);
	vector_init(&y, (double)all->map->w / 2, (double)6.75f * all->map->h / 8);
	vector_init(&z, all->map->w, 9 * (double)all->map->h / 10);

	all->a = (z.y - (((y.y - x.y) * z.x + (y.x * x.y) - (x.x * y.y)) / (y.x - x.x))) / ((z.x - x.x - y.x) * z.x + (x.x * y.x));
	all->b = (y.y - x.y) / (y.x - x.x) - all->a * (x.x + y.x);
	all->c = ((y.x * x.y - x.x * y.y) / (y.x - x.x)) + all->a * x.x * y.x;
}