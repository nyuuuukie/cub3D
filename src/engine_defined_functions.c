/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_defined_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:22:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 19:25:15 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef LINUX

void	get_mouse_pos(t_all *all)
{
	mlx_mouse_hide(all->mlx, all->win);
	mlx_mouse_get_pos(all->mlx, all->win, &all->cmx, &all->cmy);
}

void	move_mouse(t_all *all, int w, int h)
{
	mlx_mouse_move(all->mlx, all->win, w, h);
}

#else

void	get_mouse_pos(t_all *all)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(all->win, &all->cmx, &all->cmy);
}

void	move_mouse(t_all *all, int w, int h)
{
	mlx_mouse_move(all->win, w, h);
}

#endif
