/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/21 09:26:11 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    write_pixel_to_img(t_img *img, int x, int y, int color)
{
    if ((color & 0x00FFFFFF) != 0)
		*(int*)(img->addr + y * img->len + x * (img->bpp / 8)) = color;
}

void	show_sprites_dist(t_all *all)
{
	int i;
	i = 0;
	while (i < all->map->sprites)
	{
		printf("%d %.3f %.3f %.3f\n", i, all->sprites[i].x, all->sprites[i].y, all->sprites[i].dist);		
		i++;
	}
}

void	calculate_dist_to_sprite(t_all *all)
{
	t_vector a;
	int i;

	i = 0;
	while (i < all->map->sprites)
	{
		vector_init(&a, all->pos.x - all->sprites[i].x, all->pos.y - all->sprites[i].y);
		all->sprites[i].dist = a.x * a.x + a.y * a.y;
		i++;
	}
}

void	swap_values(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprites(t_all *all)
{
	int i;

	i = 0;
	while (i < all->map->sprites - 1)
	{
		if (all->sprites[i].dist < all->sprites[i + 1].dist)
		{
			swap_values(&all->sprites[i].x, &all->sprites[i + 1].x);
			swap_values(&all->sprites[i].y, &all->sprites[i + 1].y);
			swap_values(&all->sprites[i].dist, &all->sprites[i + 1].dist);
			i = -1;
		}	
		i++;
	}
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

void	draw_rain(t_all *all)
{
	int y;
	int drop_len;
	int start;
	int x;
	
	x = 0;
	while (x < all->map->w)
	{
		y = 0;
		while (y < all->map->h)
		{
			drop_len = random_number(5, 40);
			start = y + random_number(0, drop_len + 1);
			while (y < start + drop_len && y < all->map->h)
			{
				if (rand() % 100 < 20)
					write_pixel_to_img(&all->img, x, y, 0x005F5F5F);
				else if (x % 5 == 0)
					write_pixel_to_img(&all->img, x, y, 0x005F5F5F);
				y++;
			}
			y += random_number(30, 70);
		}
		x++;
	}
}

void	draw_weapon(t_all *all)
{
	t_v_int tex;
	int y;
	int x;
	//int r;

	x = 0;
	//r = 5 * sin(all->offset);
	while (x < all->map->w)
	{
		y = 0;
		while (y < all->map->h)
		{
			tex.x = 1.0 * x / all->map->w * all->wpn.w;
			tex.y = 1.0 * y / all->map->h * all->wpn.h / 2 + all->wpn.h / 2;// - r;
			all->color = color_from_img(&all->wpn.img, tex.x, tex.y);
			write_pixel_to_img(&all->img, x, y, all->color);
			y++;
		}
		x++;
	}
}

void	draw_sprites(t_all *all)
{
	
	calculate_dist_to_sprite(all);
	if (all->map->sprites > 1)
		sort_sprites(all);
	else
		all->s_order[0] = 0;

    //after sorting the sprites, do the projection and draw them
	for (int i = 0; i < all->map->sprites; i++)
    {
	    t_vector s;
		//int num = all->s_order[i];
		vector_init(&s, all->sprites[i].x - all->pos.x, all->sprites[i].y - all->pos.y);
		//translate sprite position to relative to camera


		double invDet = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y); //required for correct matrix multiplication

		double transformX = invDet * (all->dir.y * s.x - all->dir.x * s.y);
		double transformY = invDet * (-all->plane.y * s.x + all->plane.x * s.y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((all->map->w / 2) * (1 + transformX / transformY));	

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(all->map->h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + all->map->h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + all->map->h / 2 + vMoveScreen;
		if (drawEndY >= all->map->h)
			drawEndY = all->map->h - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (all->map->w / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= all->map->w) drawEndX = all->map->w - 1;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * all->s.w / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < all->map->w && transformY < all->ZBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y - vMoveScreen) * 256 - all->map->h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * all->s.h) / spriteHeight) / 256;
				all->color = *(int *)(all->s.img.addr + texY * all->s.img.len + texX * (all->s.img.bpp / 8));
				//all->color = all->s.img texture[sprite[spriteOrder[i]].texture][all->s.w * texY + texX]; //get current color from the texture
				
				if ((all->color & 0x00FFFFFF) != 0)
				{
					if (all->keys.p)
						all->color = color_make_darker(all->sprites[i].dist / 32, all->color);
					write_pixel_to_img(&all->img, stripe, y, all->color); //buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
}

void	init_sprites(t_all *all)
{
	int i;
	int j;
	int n;

	i = 0;
	n = 0;
	all->sprites = malloc(sizeof(t_vector) * all->map->sprites);
	if (!all->sprites)
		throw_error(ERR_CANNOT_ALLOC, "Sprites");
	while (i < all->map->rows && n < all->map->sprites)
	{
		j = 0;
		while (j < all->map->cols && n < all->map->sprites)
		{
			if (all->map->arr[i][j] == '2')
				vector_init(&(all->sprites[n++]), i + 0.5, j + 0.5);
			j++;
		}
		i++;
	}
}

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
	all->n = ang;
}

int		render(t_all *all)
{
	all->frame_count++;
	mlx_do_sync(all->mlx);
	key_action(all);
	mlx_mouse_get_pos(all->mlx, all->win, &all->cmx, &all->cmy);
	double pos = 1.0 * (all->pmx - all->cmx) / all->map->w;
	all->pmx = all->cmx;
	rotate_m(all, pos);
	draw_walls(all);
	if (all->map->sprites > 0)
		draw_sprites(all);

	#ifdef BONUS
		if (all->keys.p)
		{
			draw_rain(all);
			draw_weapon(all);
		}
	#endif
	
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

int		mouse_action(int button, int x, int y, t_all *all)
{
	printf("%d button\n", button);
	printf("%d x\n", x);
	printf("%d y\n", y);
	printf("%d w\n", all->map->w);
	return (0);
}

void	start_main_loop(t_all *all)
{
	all->frame_count = 0;
	all->offset = 0.0;
	all->pmx = all->map->w / 2;
	init_all(all);
	all->ZBuffer = malloc(sizeof(double) * all->map->w);
	all->s_order = malloc(sizeof(int) * all->map->sprites);
	init_sprites(all);
	
	#ifdef BONUS
		music_start(&all->music, "cyber.mp3");
	#endif

	//mlx_mouse_hook(all->win, mouse_action, &all);
	mlx_hook(all->win, KEY_PRESS_EVENT, KEY_PRESS_MASK, key_press, all);
	mlx_hook(all->win, KEY_CLOSE_EVENT, KEY_CLOSE_MASK, stop_engine, all);
	mlx_hook(all->win, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, key_release, all);
	mlx_loop_hook(all->mlx, render, all);
	mlx_loop(all->mlx);
}


void	calculate_collision_coordinates(t_all *all)
{
	all->hit_wall = 0;
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

void	calculate_initial_dist(t_all *all)
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
	// if (all->keys.p)
	// {
	// 	all->keys.p = 0;

	// 	printf("%d\n", all->wall_h);
	// 	printf("%.5f\n", all->dist_to_wall);
	// }
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

void	calculate_texture_coordinates(t_all *all)
{
	if (all->side_wall == 0)
		all->ratio = all->pos.y + all->dist_to_wall * all->ray.y;
	else
		all->ratio = all->pos.x + all->dist_to_wall * all->ray.x;
	all->ratio -= floor(all->ratio);

	all->tex.x = (int)(all->ratio * all->cur->w);
	if (all->side_wall == 0 && all->ray.x > 0) 
		all->tex.x = all->cur->w - all->tex.x - 1;
	if (all->side_wall == 1 && all->ray.y < 0)
		all->tex.x = all->cur->w - all->tex.x - 1;
}





void	map_iterator(t_all *all, void (*f)(t_all *))
{
	int y;
	int x;

	x = 0;
	while (x < all->map->w)
	{
		y = 0;
		while (y < all->map->h)
		{
			f(all);	
			y++;
		}
		x++;
	}
}



int		calculate_floor_ceil_text_coord(t_all *all)
{
	vector_int_init(&all->tex_f, (int)(all->floor.x * all->flr.w) % all->flr.w, 
						  (int)(all->floor.y * all->flr.h) % all->flr.h);
	

	vector_int_init(&all->tex_c, (int)(all->floor.x * all->sky.w) % all->sky.w, 
						  (int)(all->floor.y * all->sky.h) % all->sky.h);
	return (0);
}

int		calculate_floor_color(t_all *all, int y)
{
	double w;
	t_vector k;
	t_vector f_w;
	
	vector_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	
	if (all->side_wall == 0)
		vector_init(&f_w, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		vector_init(&f_w, all->grid.x + all->ratio, all->grid.y + k.y);

	w = all->map->h / (2.0 * y - all->map->h) / (all->dist_to_wall);

	vector_init(&all->floor, w * f_w.x + (1.0 - w) * all->pos.x,
						w * f_w.y + (1.0 - w) * all->pos.y);

	calculate_floor_ceil_text_coord(all);
	//t_v_int tex;
	//vector_int_init(&tex, (int)(all->floor.x * t->w) % t->w, 
	//					  (int)(all->floor.y * t->h) % t->h);
	
	return (0);
}

int		calculate_skybox_color(t_all *all, int y)
{
	return (color_from_img(&all->sky.img, (all->n / 360.0 * all->sky.w), \
								(1.0 * y / all->map->h * all->sky.h)));
}

void	draw_floor(t_all *all)
{
	int y;
	int x;

	x = 0;
	while (x < all->map->w)
	{
		y = 0;
		while (y < all->map->h)
		{
			if (y < all->wall_beg)
			{
				all->color = color_from_prm(&all->map->c);
				if (all->keys.p)
					all->color = color_make_lighter((1.0 * y / (all->map->h / 1.5)), all->color);
			}
			else if (y > all->wall_end)
			{		
				double d_k;

				if (y < all->a * x * x + all->b * x + all->c)
					d_k = 5.0;
				else
					d_k = 4.3;

				#ifdef BONUS
					all->color = calculate_floor_color(all, y);
				#else
					all->color = color_from_prm(&all->map->f);				
				#endif
				
				if (all->keys.p)
					all->color = color_make_darker(1.0 - (double)y / (d_k * all->map->h), all->color);
			}
			write_pixel_to_img(&all->img, x, y, all->color);
			y++;
		}
		x++;
	}
}

void	write_column_to_img(t_all *all, int x)
{
	double step = 1.0 * all->cur->w / all->wall_h;
	double texPos = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;

	//#ifdef BONUS
	//	all->brightness = (all->n / 360.0);
	//	if (all->brightness < 0.2)
	//		all->brightness = 0.2;
	//#endif

	t_vector k;
	t_vector floor_wall;
	vector_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	
	if (all->side_wall == 0)
		vector_init(&floor_wall, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		vector_init(&floor_wall, all->grid.x + all->ratio, all->grid.y + k.y);

	for (int y = 0; y < all->map->h; y++)
	{
		//if (y < all->wall_beg)
		//{
		//	//all->color = color_from_prm(&all->map->c);
		//	#ifdef BONUS
		//		all->color = calculate_skybox_color(all, y);
		//	#else
		//		all->color = color_from_prm(&all->map->c);
		//	#endif
			
		//	//#ifdef CEIL
		//	//	all->color = calculate_floor_color(all, &all->sky, y);
		//	//#endif

		//	if (all->keys.p)
		//		all->color = color_make_lighter(((double)y / (all->map->h / 1.5)), all->color);
		//}
		if (y > all->wall_end)
		{		
			double d_k;
				
			#ifdef BONUS
				calculate_floor_color(all, y);
				all->color = color_from_img(&all->flr.img, all->tex_f.x, all->tex_f.y);
				write_pixel_to_img(&all->img, x, y, all->color);
				#ifdef CEIL
					all->color = color_from_img(&all->sky.img, all->tex_c.x, all->tex_c.y);
				#else
					all->color = calculate_skybox_color(all, all->map->h - y);
				#endif
				write_pixel_to_img(&all->img, x, all->map->h - y - 1, all->color);
			#else
				all->color = color_from_prm(&all->map->f);
				write_pixel_to_img(&all->img, x, y, all->color);
				all->color = color_from_prm(&all->map->c);
				write_pixel_to_img(&all->img, x, all->map->h - y - 1, all->color);
			#endif

			if (all->keys.p)
			{
				if (y < all->a * x * x + all->b * x + all->c)
					d_k = 1.15;
				else
					d_k = 1.1;

				all->color = color_make_darker(1 - (double)y / (d_k * all->map->h), all->color);
			}
		}
		else if (y >= all->wall_beg)
		{
			all->tex.y = (int)texPos & (all->cur->h - 1); 
			texPos += step;
		 	
			all->color = color_from_img(&all->cur->img, all->tex.x, all->tex.y);
			#ifdef BONUS
				if (all->keys.p)
					all->color = color_make_darker(all->dist_to_wall / 10, all->color);				
			#endif
			write_pixel_to_img(&all->img, x, y, all->color);
		}
		all->color = color_make_darker(all->brightness, all->color);
		
		if (all->keys.p && all->frame_count % 100 < 5)
			all->color = color_negative(all->color);
		
		//if ((all->color & 0x00FFFFFF) != 0)
			//write_pixel_to_img(&all->img, x, y, all->color);
	}	
}

void	draw_walls(t_all *all)
{
	int x;

	x = 0;
	while (x < all->map->w)
	{
		vector_init(&all->cam, 2.0 * x / all->map->w - 1, 0.0);
		vector_init(&all->ray,  all->dir.x + all->plane.x * all->cam.x, \
								all->dir.y + all->plane.y * all->cam.x);
		vector_init(&all->delta, fabs(1 / all->ray.x), fabs(1 / all->ray.y));
		vector_int_init(&all->grid, all->pos.x, all->pos.y);
		recognize_texture(all);
		calculate_initial_dist(all);
		calculate_collision_coordinates(all);
		calculate_distance_to_wall(all);
		calculate_wall_height(all);
		calculate_wall_borders(all);
		calculate_texture_coordinates(all);
		if (all->screen == 0)
			all->ZBuffer[x] = all->dist_to_wall;
		write_column_to_img(all, x);
		x++;
	}
}
