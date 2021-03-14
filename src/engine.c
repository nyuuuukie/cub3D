/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:35:59 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/14 18:20:24 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int 	start_engine(t_map *map, int mode)
{
	t_all all;

	all.map = map;
	if (mode == 2)
	{
		start_main_loop(&all);
	}
	else if (mode == 3)
	{
		make_screenshot(&all);
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