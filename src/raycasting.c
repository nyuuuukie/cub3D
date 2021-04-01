/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 00:35:25 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#ifdef BONUS

void	fire(t_all *all)
{
	all->keys.f = 0;
	if (all->map->bonus && all->keys.k1)
		init_music(all, init_wsound_fork);
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
	if (!all->music_started && all->map->bonus)
		init_music(all, init_music_fork);
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
	mlx_hook(all->win, KEY_PRESS_EVENT, KEY_PRESS_MASK, key_press, all);
	mlx_hook(all->win, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, key_release, all);
	mlx_hook(all->win, 17, 1L << 17, stop_engine, all);
	mlx_loop_hook(all->mlx, render, all);
	mlx_loop(all->mlx);
}
