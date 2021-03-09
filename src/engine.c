/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:35:59 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/09 22:17:40 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int 	start_engine(t_map *map, int mode)
{
	if (mode == 2)
	{
		start_main_loop(map);
	}
	else if (mode == 3)
	{
		return (2);
	}
	return (0);
}

int	stop_engine(void *ptr)
{
	t_all *all;

	all = (t_all *)ptr;
	printf("Stopped! %d\n", all->map->w);
	//CLEAN
	exit(0);
}