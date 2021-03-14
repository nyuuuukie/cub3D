/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/14 19:14:38 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	recognize_texture(t_all *all)
{
	double ang;
	
	ang = vector_angle(&all->norm, &all->ray);
	ang = get_angle(ang);
	if (all->ray.x < 0.0f)
		ang = 360 - ang;
	if (all->side_wall == 0)
	{
		if (ang >= 180.0f && ang <= 360.0f)
			all->cur = &all->no;
		else
			all->cur = &all->so;
	}	
	else
	{
		if (ang >= 90.0f && ang <= 270.0f)
			all->cur = &all->we;
		else
			all->cur = &all->ea;
	}
}

void    write_pixel_to_img(t_img *img, int x, int y, int color)
{
    char    *dst;
	int     offset;
	
	offset = y * img->len + x * (img->bpp / 8);
    dst = img->addr + offset;
    *(unsigned int*)dst = color;
}

int		get_color_from_params(t_clr *clr)
{
	return (0L | clr->val[0] << 16 | clr->val[1] << 8 | clr->val[2]);	
}

void	set_background(t_all *all)
{
	int i;
 	int j;
	int color;

 	i = 0;
	color = get_color_from_params(&all->map->f);
	while (i < all->map->h)
 	{
 		j = 0;
 		if (i == all->map->h / 2)
		 	color = get_color_from_params(&all->map->c);
		while (j < all->map->w)
 		{
			//all->buf[i][j] = color;
 			write_pixel_to_img(&all->img, j, i, color);
			j++;
		}
 		i++;
 	}	
}

int		render(t_all *all)
{
	mlx_do_sync(all->mlx);
	raycasting(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	key_action(all);
 	return (0);
}

void	start_main_loop(t_all *all)
{
	init_all(all);
	mlx_hook(all->win, 2, 1L<<0, key_press, all);
	mlx_hook(all->win, 3, 1L<<1, key_release, all);
	mlx_hook(all->win, 17, 1L<<0, stop_engine, all);
	mlx_loop_hook(all->mlx, render, all);
	mlx_loop(all->mlx);
}

void	throw_ray(t_all *all)
{
	while (all->hit_wall == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (all->next.x < all->next.y)
		{
			all->next.x += all->delta.x;
			all->grid.x += all->step.x;
			all->side_wall = 0;
		}
		else
		{
			all->next.y += all->delta.y;
			all->grid.y += all->step.y;
			all->side_wall = 1;
		}
		//Check if ray has hit a wall
		if (all->map->arr[all->grid.x][all->grid.y] == '1') 
			all->hit_wall = 1;
	}
}

void init_next_dist(t_all *all)
{
	if (all->ray.x < 0)
	{
		all->step.x = -1;
		all->next.x = (all->pos.x - all->grid.x) * all->delta.x;
	}
	else
	{
		all->step.x = 1;
		all->next.x = (all->grid.x + 1.0 - all->pos.x) * all->delta.x;
	}
	
	if (all->ray.y < 0)
	{
		all->step.y = -1;
		all->next.y = (all->pos.y - all->grid.y) * all->delta.y;
	}
	else
	{
		all->step.y = 1;
		all->next.y = (all->grid.y + 1.0 - all->pos.y) * all->delta.y;
	}
}

void	calculate_distance_to_wall(t_all *all)
{
	if (all->side_wall == 0)
		all->dist_to_wall = (all->grid.x - all->pos.x + (1 - all->step.x) / 2) / all->ray.x;
	else
		all->dist_to_wall = (all->grid.y - all->pos.y + (1 - all->step.y) / 2) / all->ray.y;
}

void	calculate_wall_height(t_all *all)
{
	all->wall_h = (int)(all->map->h / all->dist_to_wall);
}

void	calculate_wall_borders(t_all *all)
{
	all->wall_beg = -all->wall_h / 2 + all->map->h / 2;
	if (all->wall_beg < 0)
		all->wall_beg = 0;
		
	all->wall_end = all->wall_h / 2 + all->map->h / 2;
	if (all->wall_end > all->map->h)
		all->wall_end = all->map->h;
}

void	calculate_texture_column(t_all *all)
{
	double wallX;
	if (all->side_wall == 0)
		wallX = all->pos.y + all->dist_to_wall * all->ray.y;
	else
		wallX = all->pos.x + all->dist_to_wall * all->ray.x;
	wallX -= floor((wallX));

	all->tex.x = (int)(wallX * (double)all->cur->w);
	if (all->side_wall == 0 && all->ray.x > 0) 
		all->tex.x = all->cur->w - all->tex.x - 1;
	if (all->side_wall == 1 && all->ray.y < 0)
		all->tex.x = all->cur->w - all->tex.x - 1;
}

void  raycasting(t_all *all)
{
	for (int x = 0; x < all->map->w; x++)
	{	
		//noise
		int r = rand() % 7;
	
		vector_init(&all->cam, 2 * x / (double)all->map->w - 1, 0.0f);
		vector_init(&all->ray, all->dir.x + all->plane.x * all->cam.x, all->dir.y + all->plane.y * all->cam.x);

		all->grid.x = (int)all->pos.x;
		all->grid.y = (int)all->pos.y;
		
		all->hit_wall = 0;
		
		vector_init(&all->delta, fabs(1 / all->ray.x), fabs(1 / all->ray.y));
		init_next_dist(all);

		throw_ray(all);
		
		calculate_distance_to_wall(all);
		calculate_wall_height(all);
		calculate_wall_borders(all);
		recognize_texture(all);
		calculate_texture_column(all);

		double step = 1.0 * all->cur->w / all->wall_h;
		// Starting texture coordinate
		double texPos = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;

		for (int y = 0; y < all->map->h; y++)
		{
			// int color;
			if (y < all->wall_beg)
			{
				int TextY = y / all->sky.h;
				int TextX = x / all->sky.w; 
				// all->color = get_color_from_params(&all->map->f);
				all->color = *(int *)(all->sky.img.addr + TextY * all->cur->img.len + TextX * (all->cur->img.bpp / 8));
				//or skybox
			}
			else if (y > all->wall_end)
			{
				all->color = get_color_from_params(&all->map->c);
				if (y - r < all->a * x * x + all->b * x + all->c)
				{
					//color = color_make_darker(0.9, color);
					all->color = color_make_darker(1 - ((double)(y - all->wall_end) / (2 * (all->map->h - all->wall_end))), all->color);
				}
				else
				{
					//color = color_make_darker(0.8, color);
					all->color = color_make_darker(1 - ((double)(y - all->wall_end) / (1.95 * (all->map->h - all->wall_end))), all->color);
				}
			}
			else
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (all->cur->h - 1);
			 	texPos += step;
			 	
				all->color = *(int *)(all->cur->img.addr + texY * all->cur->img.len + all->tex.x * (all->cur->img.bpp / 8));
				
				all->color = color_make_darker(all->dist_to_wall / 4, all->color);				
			}
			write_pixel_to_img(&all->img, x, y, all->color);
		}
	}
}
