/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:32:06 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:07:00 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	(void)all;
	return ;
}

#endif
