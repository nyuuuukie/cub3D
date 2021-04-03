/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:19:31 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 19:27:59 by mhufflep         ###   ########.fr       */
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

void	init_mouse(t_all *all)
{
	int h;
	int w;

	if (all->map->bonus && all->screen == 0)
	{
		h = all->screen_h / 2;
		w = all->screen_w / 2;
		move_mouse(all, w, h);
	}
}
