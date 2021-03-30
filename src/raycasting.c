/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/30 17:00:57 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    put_pixel(t_img *img, int x, int y, int color)
{
		*(int*)(img->addr + y * img->len + x * (img->bpp / 8)) = color;
}

void	calculate_dist_to_sprite(t_all *all)
{
	t_vector a;
	int i;

	i = 0;
	while (i < all->map->sprites)
	{
		vector_init(&a, all->pos.x - all->sprites[i].p.x, all->pos.y - all->sprites[i].p.y);
		all->sprites[i].p.dist = a.x * a.x + a.y * a.y;
		i++;
	}
}

void	swap_d_values(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	swap_c_values(char *a, char *b)
{
	char temp;

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
		if (all->sprites[i].p.dist < all->sprites[i + 1].p.dist)
		{
			swap_d_values(&all->sprites[i].p.x, &all->sprites[i + 1].p.x);
			swap_d_values(&all->sprites[i].p.y, &all->sprites[i + 1].p.y);
			swap_c_values(&all->sprites[i].id, &all->sprites[i + 1].id);
			swap_d_values(&all->sprites[i].p.dist, &all->sprites[i + 1].p.dist);
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
	int x;
	int big;
	int small;
	int drop_len;
	
	x = 0;
	while (x < all->map->w)
	{
		small = random_number(1, 15);
		big = random_number(5, 30);
		if (all->ZBuffer[x] > 0.5)
		{
			y = random_number(0, all->map->h / 6 + 1);
			while (y < all->map->h)
			{
				if (y < all->wall_beg)
					drop_len = small;
				else
					drop_len = big;
				while (drop_len-- && y < all->map->h)
				{
					if (y < all->a * x * x + all->b * x || x % 5 == 0)
						put_pixel(&all->img, x, y, 0x006F6F6F);
					y++;
				}
				y += random_number(50, 70);
			}
		}
		x++;
	}
}

void	draw_weapon(t_all *all)
{
	t_v_int tex;
	int y;
	int x;

	x = 0;
	while (x < all->map->w)
	{
		y = 0;
		while (y < all->map->h)
		{
			tex.x = 1.0 * x / all->map->w * all->wpn[all->wp_i].w;
			tex.y = 1.0 * y / all->map->h * all->wpn[all->wp_i].h + all->r;
			all->color = color_from_txt(&all->wpn[all->wp_i], tex.x, tex.y);
			if ((all->color & 0x00FFFFFF) != 0)
				put_pixel(&all->img, x, y, all->color);
			y++;
		}
		x++;
	}
}

void	draw_number(t_all *all, int x, int y, int num)
{
	int i;
	int j;
	int scale;
	
	i = 0;
	scale = all->map->h / 20 + 1;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			int color = color_from_txt(&all->digits[num], 1.0 * all->digits[num].w * j / scale, 1.0 * all->digits[num].w * i / scale);
			if ((color & 0xFFFFFFFF) == 0)
				put_pixel(&all->img, x + j, y + i, color_negative(color));
			j++;
		}
		i++;
	}
}

void	draw_hud(t_all *all)
{
	int x;
	//int y;
	int count;
	
	//y = 10;
	x = all->map->w - 10; 
	count = all->coin_counter;
	 while (count != 0)
	{
		x -= all->map->h / 20 + 1;
		draw_number(all, x, 10, count % 10);
		count /= 10;
	}
}

// void	calculate_sprites()
// {

// }


// void	calculate_sprite_size(t_all *all)
// {
	
// }

// void 	check_sprite_coords(t_all *all)
// {

// }

// void	draw_sprite(t_all *all)
// {
	
// }

void	draw_sprites(t_all *all)
{
	double det;
	
	calculate_dist_to_sprite(all);

	if (all->map->sprites > 1)
		sort_sprites(all);

	for (int i = 0; i < all->map->sprites; i++)
    {
		vector_init(&all->d, all->sprites[i].p.x - all->pos.x, 
						all->sprites[i].p.y - all->pos.y);

		det = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y);

		vector_init(&all->t, det * (all->dir.y * all->d.x - all->dir.x * all->d.y),
							det * (-all->plane.y * all->d.x + all->plane.x * all->d.y));

		all->sp_scr_x = (int)((all->map->w / 2) * (1 + all->t.x / all->t.y));

		all->vm_scr = (int)(all->vmove / all->t.y);

		vector_int_init(&all->s_size, abs((int)(all->map->w / all->t.y)) / all->scale.x,
								  	  abs((int)(all->map->h / all->t.y)) / all->scale.y);
		vector_int_init(&all->s_beg, -all->s_size.x / 2 + all->sp_scr_x, 
						-all->s_size.y / 2 + all->map->h / 2 + all->vm_scr);
		vector_int_init(&all->s_end, all->s_size.x / 2 + all->sp_scr_x, 
						all->s_size.y / 2 + all->map->h / 2 + all->vm_scr);

		if (all->s_beg.y < 0)
			all->s_beg.y = 0;
		if (all->s_end.y >= all->map->h)
			all->s_end.y = all->map->h;// - 1;
		if (all->s_beg.x < 0) 
			all->s_beg.x = 0;
		if (all->s_end.x >= all->map->w) 
			all->s_end.x = all->map->w;// - 1;
		
		t_texture *s;

		if (all->sprites[i].id == '2')
			s = &(all->s1);
		else
			s = &(all->s2);

		for (int sx = all->s_beg.x; sx < all->s_end.x; sx++)
		{
			all->tex.x = (int)(256 * (sx - (-all->s_size.x / 2 + all->sp_scr_x)) * s->w / all->s_size.x) / 256 + 1;
			
			if (all->t.y > 0 && sx > 0 && sx < all->map->w && all->t.y < all->ZBuffer[sx])
			{
				for (int sy = all->s_beg.y; sy < all->s_end.y; sy++) 
				{
					int d = (sy - all->vm_scr) * 256 - all->map->h * 128 + all->s_size.y * 128;
					all->tex.y = ((d * s->h) / all->s_size.y) / 256;
					
					if (all->tex.x >= 0 && all->tex.x <= s->w && all->tex.y >= 0 && all->tex.y <= s->h)
						all->color = color_from_txt(s, all->tex.x, all->tex.y);
					else
						all->color = 0x00000000;
					
					if ((all->color & 0x00FFFFFF) != 0)
					{
						if (all->map->bonus && all->keys.k0)
							all->color = color_make_darker(all->sprites[i].p.dist / 40, all->color);
						put_pixel(&all->img, sx, sy, all->color);
					}
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
	all->sprites = malloc(sizeof(t_sprite) * all->map->sprites);
	if (!all->sprites)
		throw_engine_error(all, ERR_CANNOT_ALLOC, "Sprites");
	while (i < all->map->rows && n < all->map->sprites)
	{
		j = 0;
		while (j < all->map->cols && n < all->map->sprites)
		{
			if (ft_strchr(SPRITES, all->map->arr[i][j]))
			{
				all->sprites[n].id = all->map->arr[i][j];
				vector_init(&(all->sprites[n++].p), i + 0.5, j + 0.5);
			}
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

int		mouse_action(t_all *all)
{
	int sign;
	double angle;

	sign = 1;
	#ifdef LINUX
		mlx_mouse_hide(all->mlx, all->win);
		mlx_mouse_get_pos(all->mlx, all->win, &all->cmx, &all->cmy);
	#else
		mlx_mouse_hide();
		mlx_mouse_get_pos(all->win, &all->cmx, &all->cmy);
	#endif
	angle = 10.0 * abs(all->pmx - all->cmx) / all->map->w;
	if (all->pmx - all->cmx < 0)
		sign = -1;
	all->pmx = all->cmx;
	rotate(all, sign, angle);
	return (0);
}

// int		draw_fire(t_all *all)
// {
// 	t_v_int tex;
// 	int y;
// 	int x;
// 	x = 0;
// 	while (x < all->map->w)
// 	{
// 		y = 0;
// 		while (y < all->map->h)
// 		{
// 			tex.x = 1.0 * x / all->map->w * all->fire.w;
// 			tex.y = 1.0 * y / all->map->h * all->fire.h + 0.5 * all->r;
// 			all->color = color_from_txt(&all->fire, tex.x, tex.y);
// 			if ((all->color & 0x00FFFFFF) != 0)
// 				put_pixel(&all->img, x, y, all->color);
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (0);
// }

int		draw_all(t_all *all)
{
	draw_walls(all);
	
	if (all->map->sprites > 0)
		draw_sprites(all);
	if (all->wsound_started && all->wp_i < ANIM_FRAMES - 1) //&& all->frame_count % 2 == 0)
		all->wp_i++;
	if (!all->wsound_started)
		all->wp_i = 0;
	#ifdef BONUS
		if (!all->ceil_exist && all->keys.p)
			draw_rain(all);
		if (all->keys.k1)
			draw_weapon(all);
		draw_hud(all);
	#endif
	return (0);
}

void fire(t_all *all)
{
	(void)all;
	#ifdef BONUS
		if (all->map->bonus && all->keys.k1)
			init_music(all, init_wsound_fork);
	#endif
}

int 	mouse_press(int button, int x, int y, void *param)
{
	t_all *all;

	(void)x;
	(void)y;
	all = (t_all *)param;
	if (button == 1)
		fire(all);

	return (0);
}

int		render(t_all *all)
{
	mlx_do_sync(all->mlx);
	all->frame_count++;
	key_action(all);
	if (all->map->bonus)
		mouse_action(all);
	draw_all(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (0);
}

void	start_main_loop(t_all *all)
{
	init_all(all);

	#ifdef MUSIC
		init_music(all, init_music_fork);	
	#endif
	
	// mlx_mouse_hook(all->win, mouse_press, all);
	mlx_hook(all->win, KEY_PRESS_EVENT, KEY_PRESS_MASK, key_press, all);
	mlx_hook(all->win, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, key_release, all);
	mlx_hook(all->win, 17, 1L << 17, stop_engine, all);
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
	all->wall_beg = all->map->h / 2 - all->wall_h / 2;
	if (all->wall_beg < 0)
		all->wall_beg = 0;
		
	all->wall_end = all->map->h / 2 + all->wall_h / 2;
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

void	init_bonus_flags(t_all *all)
{
	if (all->map->bonus)
	{
		#ifdef FLOOR
			all->floor_exist = 1;
		#endif
		#ifdef SKY
			all->sky_exist = 1;
		#elif defined CEIL
			all->ceil_exist = 1;
		#endif
	}
}

int is_lightning(t_all *all)
{
	return ((all->frame_count % 100 < 5 ) || \
			(all->frame_count % 100 > 20 && all->frame_count % 100 < 25));
}


void	draw_floor_ceil(t_all *all, int x, int y)
{
	int f;
	int c;
	double d_k;

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
			d_k = 1.65;
		else
			d_k = 1.5;
		f = color_make_darker(1 - (double)y / (d_k * all->map->h), f);
		c = color_make_darker(1 - (double)y / (d_k * all->map->h), c);
	}
	if (all->map->bonus && all->keys.p && is_lightning(all))
		f = color_negative(f);
	put_pixel(&all->img, x, y, f);
	put_pixel(&all->img, x, all->map->h - y - 1, c);
}

void	draw_background(t_all *all, int x)
{
	t_vector k;
	t_vector floor_wall;
	
	int y;
	vector_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	
	if (all->side_wall == 0)
		vector_init(&floor_wall, all->grid.x + k.x, all->grid.y + all->ratio);
	else
		vector_init(&floor_wall, all->grid.x + all->ratio, all->grid.y + k.y);
	
	y = all->map->h / 2;
	while (y < all->map->h)
	{
		draw_floor_ceil(all, x, y);
		y++;
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
	return (0);
}

int		calculate_skybox_color(t_all *all, int y)
{
	return (color_from_txt(&all->sky, (all->n / 360.0 * all->sky.w), \
								(1.0 * y / all->map->h * all->sky.h)));
}

void	put_column(t_all *all, int x)
{
	double step = 1.0 * all->cur->w / all->wall_h;
	double texPos = (all->wall_beg - all->map->h / 2 + all->wall_h / 2) * step;

	t_vector k;
	t_vector floor_wall;
	vector_init(&k, (all->ray.x < 0), (all->ray.y < 0));
	
	if (all->side_wall == 0)
		vector_init(&floor_wall, all->grid.x + k.x, all->grid.y + all->ratio);
    else
		vector_init(&floor_wall, all->grid.x + all->ratio, all->grid.y + k.y);

	for (int y = 0; y < all->map->h; y++)
	{
		if (y > all->wall_beg && y <= all->wall_end) 
		{
			all->tex.y = (int)texPos; 
			texPos += step;
		 	
			all->color = color_from_txt(all->cur, all->tex.x, all->tex.y);
			#ifdef BONUS
			 	if (all->keys.k0)
			 		all->color = color_make_darker(all->dist_to_wall / 20, all->color);				
				if (all->keys.p && (all->frame_count % 100 < 5 || (all->frame_count % 100 > 20 && all->frame_count % 100 < 25)))
					all->color = color_negative(all->color);
			#endif
			if ((all->color & 0x00FFFFFF) != 0)
				put_pixel(&all->img, x, y + all->offset, all->color);
		}
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
		draw_background(all, x);
		if (all->screen == 0)
			all->ZBuffer[x] = all->dist_to_wall;
		put_column(all, x);
		x++;
	}
}
