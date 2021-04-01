/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:19:31 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 17:20:45 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int 	mouse_press(int button, int x, int y, void *param)
// {
// 	t_all *all;
// 	(void)x;
// 	(void)y;
// 	all = (t_all *)param;
// 	if (button == 1)
// 		fire(all);
// 	return (0);
// }

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