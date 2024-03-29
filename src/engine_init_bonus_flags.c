/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init_bonus_flags.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 00:30:08 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 16:11:43 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_bonus_flags(t_all *all)
{
	if (all->map->bonus)
	{
		all->sky_exist = 1;
		all->ceil_exist = 0;
		all->floor_exist = 1;
	}
}
