/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:32:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 03:52:05 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	draw_extra_data(t_all *all) {

	time_t now = time(0);
	if (now - all->last_frame >= 1) {
		all->last_frame = now;
		all->fps = all->frame_count;
		all->frame_count = 0;
	}

	char fps_msg[20] = { 0 };
	sprintf(fps_msg, "FPS: %d", all->fps);
	mlx_string_put(all->mlx, all->win, 30, 30, 0x00ffffff, fps_msg);

	char kill_counter_msg[20] = { 0 };
	sprintf(kill_counter_msg, "Kills: %d", all->kill_counter);
	mlx_string_put(all->mlx, all->win, 30, 50, 0x00ffffff, kill_counter_msg);

	char keys_counter_msg[30] = { 0 };
	sprintf(keys_counter_msg, "Keys to unlock portal: %d", all->map->keys);
	mlx_string_put(all->mlx, all->win, 30, 70, 0x00ffffff, keys_counter_msg);
}

void	draw_bonus_part(t_all *all)
{
	if (all->map->bonus)
	{
		if (all->weapon_action == 1) {
			if (all->wp_i < ANIM_FRAMES - 1) {
				all->wp_i++;
			} else {
				all->wp_i = 0;
				all->weapon_action = 0;
				all->remove = 0;
			}
		}


		if (all->tpf < ANIM_FRAMES - 1)
			all->tpf++;
		else
			all->tpf = 0;

		if (!all->ceil_exist && all->keys.p)
			draw_rain(all);
		if (all->keys.k1)
			draw_weapon(all);
	}
}

#else

void	draw_bonus_part(t_all *all)
{
	(void)all;
	return ;
}

#endif
