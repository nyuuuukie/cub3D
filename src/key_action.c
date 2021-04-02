/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:39:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_all *all)
{
	all->keys.w = 0;
	all->keys.a = 0;
	all->keys.s = 0;
	all->keys.d = 0;
	all->keys.l = 0;
	all->keys.r = 0;
	all->keys.p = 0;
	all->keys.k0 = 0;
	all->keys.k1 = 0;
	all->keys.sh = 0;
	all->keys.f = 0;
}

int		key_action(t_all *all)
{
	if (all->keys.w && !all->keys.s)
		move(all, &all->dir, 1);
	if (all->keys.s && !all->keys.w)
		move(all, &all->dir, -1);
	if (all->keys.a && !all->keys.d)
		move(all, &all->plane, -1);
	if (all->keys.d && !all->keys.a)
		move(all, &all->plane, 1);
	if (all->keys.l && !all->keys.r)
		rotate(all, 1, all->r_angle);
	if (all->keys.r && !all->keys.l)
		rotate(all, -1, all->r_angle);
	if (all->map->bonus && all->keys.f)
		fire(all);
	all->k_speed = all->keys.sh + 1.0;
	return (0);
}

int		key_release(int keycode, t_all *all)
{
	if (keycode == KEY_W)
		all->keys.w = 0;
	else if (keycode == KEY_S)
		all->keys.s = 0;
	else if (keycode == KEY_A)
		all->keys.a = 0;
	else if (keycode == KEY_D)
		all->keys.d = 0;
	else if (keycode == KEY_LEFT)
		all->keys.l = 0;
	else if (keycode == KEY_RIGHT)
		all->keys.r = 0;
	else if (keycode == KEY_SHIFT)
		all->keys.sh = 0;
	return (0);
}

int		key_press(int keycode, t_all *all)
{
	if (keycode == KEY_W)
		all->keys.w = 1;
	else if (keycode == KEY_S)
		all->keys.s = 1;
	else if (keycode == KEY_A)
		all->keys.a = 1;
	else if (keycode == KEY_D)
		all->keys.d = 1;
	else if (keycode == KEY_LEFT)
		all->keys.l = 1;
	else if (keycode == KEY_RIGHT)
		all->keys.r = 1;
	else if (keycode == KEY_P)
		all->keys.p = !all->keys.p;
	else if (keycode == KEY_SHIFT)
		all->keys.sh = 1;
	else if (keycode == KEY_ESC)
		stop_engine(all);
	else if (keycode == KEY_K0)
		all->keys.k0 = !all->keys.k0;
	else if (keycode == KEY_K1)
		all->keys.k1 = !all->keys.k1;
	else if (keycode == KEY_F)
		all->keys.f = 1;
	return (0);
}
