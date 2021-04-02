/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:19:31 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mouse_press(int button, int x, int y, void *param)
{
	t_all	*all;

	(void)x;
	(void)y;
	all = (t_all *)param;
	if (button == 1)
		fire(all);
	return (0);
}

#ifdef LINUX

void	get_mouse_pos(t_all *all)
{
	mlx_mouse_hide(all->mlx, all->win);
	mlx_mouse_get_pos(all->mlx, all->win, &all->cmx, &all->cmy);
}

#else

void	get_mouse_pos(t_all *all)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(all->win, &all->cmx, &all->cmy);
}

#endif

int		mouse_action(t_all *all)
{
	double	angle;
	int		sign;

	sign = 1;
	get_mouse_pos(all);
	angle = 10.0 * abs(all->pmx - all->cmx) / all->map->w;
	if (all->pmx - all->cmx < 0)
		sign = -1;
	all->pmx = all->cmx;
	rotate(all, sign, angle);
	return (0);
}
