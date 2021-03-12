/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:39:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/12 18:06:31 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_keys(t_all* all)
{
	all->keys.w = 0;
	all->keys.a = 0;
	all->keys.s = 0;
	all->keys.d = 0;
	all->keys.l = 0;
	all->keys.r = 0;
}

int key_action(t_all *all)
{
	mlx_do_sync(all->mlx);
	if (all->keys.w && !all->keys.s)
		move(all, 1);
	if (all->keys.s && !all->keys.w)
		move(all, -1);
	if (all->keys.a && !all->keys.d)
		move_side(all, 1);
	if (all->keys.d && !all->keys.a)
		move_side(all, -1);
	if (all->keys.l && !all->keys.r)
		rotate(all, 1);
	if (all->keys.r && !all->keys.l)
		rotate(all, -1);
	//render(all);
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
	return (0);
}

int		key_press(int keycode, t_all *all)
{
	//mlx_do_key_autorepeaton(all->mlx);
	if (!all->keys.w && keycode == KEY_W)
		all->keys.w = 1;
	else if (!all->keys.s && keycode == KEY_S)
		all->keys.s = 1;
	else if (!all->keys.a && keycode == KEY_A)
		all->keys.a = 1;
	else if (!all->keys.d && keycode == KEY_D)
		all->keys.d = 1;
	else if (!all->keys.l && keycode == KEY_LEFT)
		all->keys.l = 1;
	else if (!all->keys.r && keycode == KEY_RIGHT)
		all->keys.r = 1;
	else if (keycode == KEY_ESC)
		stop_engine(all);
	key_action(all);
	return (0);
}
