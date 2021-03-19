/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/19 02:11:10 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    write_pixel_to_img(t_img *img, int x, int y, int color)
{
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
	//show_sprites_dist(all);
}

void	sort_sprites(t_all *all)
{
	t_vector t;
	int i;

	i = 0;
	while (i < all->map->sprites - 1)
	{
		if (all->sprites[i].dist < all->sprites[i + 1].dist)
		{
			vector_init(&t, all->sprites[i].x, all->sprites[i].y);
			t.dist = all->sprites[i].dist;
			vector_init(&(all->sprites[i]), all->sprites[i + 1].x, all->sprites[i + 1].y);
			all->sprites[i].dist = all->sprites[i + 1].dist;
			vector_init(&(all->sprites[i + 1]), t.x, t.y);
			all->sprites[i + 1].dist = t.dist;
			i = -1;
		}	
		i++;
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
		//double spriteX = sprite[spriteOrder[i]].x - posX;
		//double spriteY = sprite[spriteOrder[i]].y - posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

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
		int spriteWidth = abs( (int) (all->map->h / (transformY))) / uDiv;
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
						all->color = color_make_darker(all->ZBuffer[stripe] / 8, all->color);
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


////DO NOT NEED ANYMORE
//void	draw_floor(t_all *all)
//{
////FLOOR CASTING
//    for(int y = 0; y < all->map->h; y++)
//    {
//		t_vector r0;
//		t_vector r1;
//		t_vector floor;
//		t_vector f_step;
//		double rowDistance = all->map->h / (2.0 * y - all->map->h);
//		vector_init(&r0, all->dir.x - all->plane.x, all->dir.y - all->plane.y);
//		vector_init(&r1, all->dir.x + all->plane.x, all->dir.y + all->plane.y);
//		vector_init(&floor, all->pos.x + rowDistance * r0.x, all->pos.y + rowDistance * r0.y);
//		vector_init(&f_step, rowDistance * (2 * all->plane.x) / all->map->w, rowDistance * (2 * all->plane.y) / all->map->w);
//	for (int x = 0; x < all->map->w; ++x)
//    {
//		int cellX = (int)(floor.x);
//    	int cellY = (int)(floor.y);
//		// get the texture coordinate from the fractional part
//		int tx = (int)(all->so.w * (floor.x - cellX)) & (all->so.w - 1);
//	    int ty = (int)(all->so.h * (floor.y - cellY)) & (all->so.h - 1);
//	    floor.x += f_step.x;
//	    floor.y += f_step.y;
//	    // floor
//		all->color = *(int *)(all->so.img.addr + ty * all->so.img.len + tx * (all->so.img.bpp / 8));
//		write_pixel_to_img(&all->img, x, y, all->color);
//      	}
//    }
//}

int		render(t_all *all)
{
	all->frame_count++;
	mlx_do_sync(all->mlx);
	key_action(all);
	//draw_floor(all);
	draw_walls(all);
	if (all->map->sprites > 0)
		draw_sprites(all);
	//draw_sprites if exist
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

void	start_main_loop(t_all *all)
{
	all->frame_count = 0;
	init_all(all);
	all->ZBuffer = malloc(sizeof(double) * all->map->w);
	all->s_order = malloc(sizeof(int) * all->map->sprites);
	init_sprites(all);
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
	int y;
	int drop_len;
	int start;

	y = 0;
	while (y < all->map->h)
	{
		drop_len = random_number(5, 40);
		start = y + random_number(0, drop_len + 1);
		while (y < start + drop_len && y < all->map->h)
		{
			if (rand() % 100 < 20 && y < all->a * x * x + all->b * x + all->c + all->wall_h)
				write_pixel_to_img(&all->img, x, y, 0x005F5F5F);
			else if (x % 5 == 0 && y > all->a * x * x + all->b * x + all->c - all->wall_h)
				write_pixel_to_img(&all->img, x, y, 0x005F5F5F);
			y++;
		}
		y += random_number(30, 70);
	}
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

int		calculate_floor_color(t_all *all, int y)
{
	t_vector k;
	t_v_int tex;
	t_vector floor_wall;
	
	vector_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	if (all->side_wall == 0)
		vector_init(&floor_wall, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		vector_init(&floor_wall, all->grid.x + all->ratio, all->grid.y + k.y);

	double currentDist = all->map->h / (2.0 * y - all->map->h);
	double weight = (currentDist) / (all->dist_to_wall);

	double currentFloorX = weight * floor_wall.x + (1.0 - weight) * all->pos.x;
	double currentFloorY = weight * floor_wall.y + (1.0 - weight) * all->pos.y;

	vector_int_init(&tex, (int)(currentFloorX * all->so.w) % all->so.w, (int)(currentFloorY * all->so.h) % all->so.h);
	return (color_from_img(&all->so.img, tex.x, tex.y));
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
			//mlx_string_put()
			y++;
		}
		x++;
	}
}

void	write_column_to_img(t_all *all, int x)
{
	double step = 1.0 * all->cur->w / all->wall_h;
	// Starting texture coordinate
	double texPos = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;

	//ADD brightness
	#ifdef BONUS
		//all->brightness = (all->n / 360.0);
		//if (all->brightness < 0.2)
		//	all->brightness = 0.2;
	#endif

	t_vector k;
	t_vector floor_wall;
	vector_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	
	if (all->side_wall == 0)
		vector_init(&floor_wall, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		vector_init(&floor_wall, all->grid.x + all->ratio, all->grid.y + k.y);

	for (int y = 0; y < all->map->h; y++)
	{
		if (y < all->wall_beg)
		{
			#ifdef BONUS
				all->color = calculate_skybox_color(all, y);
			#else
				all->color = color_from_prm(&all->map->c);
			#endif
			if (all->keys.p)
				all->color = color_make_lighter(((double)y / (all->map->h / 1.5)), all->color);
		}
		else if (y > all->wall_end)
		{		
			double d_k;
			
			#ifdef BONUS
				all->color = calculate_floor_color(all, y);
			#else
				all->color = color_from_prm(&all->map->f);				
			#endif
			
			if (y < all->a * x * x + all->b * x + all->c)
				d_k = 5.0;
			else
				d_k = 4.3;

			//all->color = color_make_darker(1 - ((double)(y - all->wall_end) / (d_k * (all->map->h - all->wall_end))), all->color);
			if (all->keys.p)
				all->color = color_make_darker(1 - (double)y / (d_k * all->map->h), all->color);
		}
		else if (y >= all->wall_beg)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			all->tex.y = (int)texPos & (all->cur->h - 1); 
			texPos += step;
		 	
			all->color = color_from_img(&all->cur->img, all->tex.x, all->tex.y);
			#ifdef BONUS
				if (all->keys.p)
					all->color = color_make_darker(all->dist_to_wall / 4, all->color);				
			#endif
		}
		all->color = color_make_darker(all->brightness, all->color);
		
		if (all->keys.p && all->frame_count % 100 < 5)
			all->color = color_negative(all->color);
		
		if ((all->color & 0x00FFFFFF) != 0)
			write_pixel_to_img(&all->img, x, y, all->color);
	}
	#ifdef BONUS
		if (all->keys.p)
			draw_rain(all, x);
	#endif
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
