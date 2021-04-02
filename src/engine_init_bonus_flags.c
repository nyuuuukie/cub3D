/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init_bonus_flags.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 00:30:08 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 04:07:29 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#ifdef FLOOR

void	init_floor_exist(t_all *all)
{
	all->floor_exist = 1;
}

#else

void	init_floor_exist(t_all *all)
{
	all->floor_exist = 0;
}

#endif

#ifdef SKY

void	init_sky_exist(t_all *all)
{
	all->sky_exist = 1;
}

#else

void	init_sky_exist(t_all *all)
{
	all->sky_exist = 0;
}

#endif

#ifdef CEIL

void	init_ceil_exist(t_all *all)
{
	all->ceil_exist = 1;
}

#else

void	init_ceil_exist(t_all *all)
{
	all->ceil_exist = 0;
}

#endif

void	init_bonus_flags(t_all *all)
{
	if (all->map->bonus)
	{
		init_ceil_exist(all);
		init_sky_exist(all);
		init_floor_exist(all);
	}
}
