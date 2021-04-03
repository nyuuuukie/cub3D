/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_defined_functions_ext.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:22:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 19:26:04 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef LINUX

void	get_screen_size(t_all *all)
{
	mlx_get_screen_size(all->mlx, &all->screen_w, &all->screen_h);
}

#else

void	get_screen_size(t_all *all)
{
	mlx_get_screen_size(&all->screen_w, &all->screen_h);
}

#endif
