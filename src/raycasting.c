/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 20:43:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	recognize_texture(t_all *all)
{
	double ang;
	
	ang = v_dbl_angle(&all->norm, &all->ray);
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

#ifdef BONUS

void	draw_bonus_part(t_all *all)
{
	if (all->map->bonus)
	{
		if (all->wsound_started && all->wp_i < ANIM_FRAMES - 1)
			all->wp_i++;
		if (!all->wsound_started)
			all->wp_i = 0;
		all->tpf++;
		if (all->tpf >= ANIM_FRAMES)
			all->tpf = 0;
		if (!all->ceil_exist && all->keys.p)
			draw_rain(all);
		if (all->keys.k1)
			draw_weapon(all);
		draw_hud(all);
	}
}	

#else

void	draw_bonus_part(t_all *all)
{
	return ;
}

#endif

#ifdef BONUS

void	fire(t_all *all)
{
	all->keys.f = 0;
	#ifdef BONUS
		if (all->map->bonus && all->keys.k1)
			init_music(all, init_wsound_fork);
	#endif
}

#else

void	fire(t_all *all)
{
	return ;
}

#endif

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

void	check_if_sprite_hit(t_all *all, int x, int y)
{
	if (all->map->bonus && all->map->arr[x][y] == '2')
	{
		if (all->remove == 1)
			remove_sprite(all, x, y);
		all->remove = 0;
	}
}

void	check_shooted_sprite(t_all *all)
{
	int w;

	if (all->map->arr[all->grid.x][all->grid.y] == '2')
	{
		w = all->map->w / 2;
		if (all->remove == 1 && all->it.x >= w - 5 && all->it.x <= w + 5)
		{
			remove_sprite(all, all->grid.x, all->grid.y);
			all->remove = 0;
		}
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

int		is_lightning(t_all *all)
{
	return ((all->frame_count % 100 < 5 ) || \
			(all->frame_count % 100 > 20 && all->frame_count % 100 < 25));
}
