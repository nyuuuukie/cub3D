/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 07:00:49 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	fire(t_all *all)
{
	all->keys.f = 0;
	if (all->map->bonus && all->keys.k1 && !all->weapon_action) {
		play_sound(all->wsound, false);
		all->weapon_action = 1;
		all->remove = 1;
	}
}

#else

void	fire(t_all *all)
{
	(void)all;
	return ;
}

#endif

int		render(t_all *all)
{
	// mlx_do_sync(all->mlx);
	all->frame_count++;

	key_action(all);
	mouse_action(all);

	// if ((all->frame_count & 1) == 0) {
	draw_all(all);
	// }

	return (0);
}

void	start_main_loop(t_all *all)
{
	init_all(all);
	all->exit = 1;

	if (all->map->bonus) {
		play_sound(all->music, true);
	}

	mlx_hook(all->win, KEY_PRESS_EVENT, KEY_PRESS_MASK, key_press, all);
	mlx_hook(all->win, KEY_RELEASE_EVENT, KEY_RELEASE_MASK, key_release, all);
	mlx_hook(all->win, 17, 1L << 17, stop_engine, all);
	mlx_mouse_hook(all->win, mouse_press, all);
	mlx_loop_hook(all->mlx, render, all);
	mlx_loop(all->mlx);
}
