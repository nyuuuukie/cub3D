/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/15 19:26:43 by mhufflep         ###   ########.fr       */
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
	// int h;
	// int w;
	// all->img.img = mlx_xpm_file_to_image(all->mlx, "./textures/bluecloud_bk.xpm", &w, &h);
	key_action(all);
	raycasting(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
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

void	vector_int_init(t_v_int *vect, int x, int y)
{
	vect->x = x;
	vect->y = y;
}

int		random_number(int min, int max)
{
	return (rand() % (max - min) + min);
}

void	draw_rain(t_all *all, int x)
{
	int rain_drops;
	int rain_drop_len;
	int	start_y;
	int y;

	y = 0;
	start_y = 0;
	rain_drops = 1;
	while (rain_drops--)
	{
		rain_drop_len = random_number(5, 50);
		start_y = random_number(y, all->map->h);
		y = start_y;
		while (y < start_y + rain_drop_len && y < all->map->h)
		{
			write_pixel_to_img(&all->img, x, y, 0x3F3F3F);
			y++;
		}
	}
}

void  raycasting(t_all *all)
{
	// int r;
	// srand(time(0));
	for (int x = 0; x < all->map->w; x++)
	{	
		// if (x % 10 == 0)
		// 	r = rand() % 10;

		all->hit_wall = 0;
		vector_init(&all->cam, 2 * x / (double)all->map->w - 1, 0.0f);
		vector_init(&all->ray, all->dir.x + all->plane.x * all->cam.x, all->dir.y + all->plane.y * all->cam.x);
		vector_init(&all->delta, fabs(1 / all->ray.x), fabs(1 / all->ray.y));
		vector_int_init(&all->grid, all->pos.x, all->pos.y);
		
		init_next_dist(all);
		throw_ray(all);
		
		recognize_texture(all);
		
		calculate_distance_to_wall(all);
		calculate_wall_height(all);
		calculate_wall_borders(all);
		calculate_texture_column(all);
		
		double step = 1.0 * all->cur->w / all->wall_h;
		// Starting texture coordinate
		double texPos = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;
		
		double skystep = 1.0 * all->sky.w / all->map->h;
		double skytexPos = (0 - all->map->h / 2 + all->map->h / 2) * step;
		
		//ADD brightness
		all->brightness = get_angle(vector_angle(&all->norm, &all->ray)) / 540.0;
		if (all->brightness > 0.95)
			all->brightness = 0.95;
		
		for (int y = 0; y < all->map->h; y++)
		{
			if (y < all->wall_beg)
			{
				#ifdef BONUS
					int texY = (int)skytexPos;
			 		skytexPos += skystep;
					int TextX = x / all->sky.h;
					all->color = *(int *)(all->sky.img.addr + texY * all->sky.img.len + TextX);
				#else
					all->color = get_color_from_params(&all->map->c);
				#endif
			}
			else if (y > all->wall_end)
			{
				all->color = get_color_from_params(&all->map->f);
				
				#ifdef BONUS
				if (y < all->a * x * x + all->b * x + all->c)
				{
					//all->color = color_make_darker(0.9, all->color);
					all->color = color_make_darker(1 - ((double)(y - all->wall_end) / (2 * (all->map->h - all->wall_end))), all->color);
				}
				else
				{
					//all->color = color_make_darker(0.4, all->color);
					all->color = color_make_darker(1 - ((double)(y - all->wall_end) / (1.9 * (all->map->h - all->wall_end))), all->color);
				}
				#endif
			}
			else
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (all->cur->h - 1);
			 	texPos += step;
			 	
				all->color = *(int *)(all->cur->img.addr + texY * all->cur->img.len + all->tex.x * (all->cur->img.bpp / 8));				
				
				#ifdef BONUS
					all->color = color_make_darker(all->dist_to_wall / 5, all->color);				
				#endif
			}
			all->color = color_make_darker(all->brightness, all->color);
			write_pixel_to_img(&all->img, x, y, all->color);
		}
		draw_rain(all, x);
		// printf("%d\n", x);
	}
}
