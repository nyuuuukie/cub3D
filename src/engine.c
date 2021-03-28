/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:35:59 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/27 18:31:07 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int 	start_engine(t_map *map, int mode)
{
	t_all all;

	all.map = map;
	if (mode == 2)
	{
		all.screen = 0;
		// init_threads(&all);
		start_main_loop(&all);
	}
	else if (mode == 3)
	{
		all.screen = 1;
		make_screenshot(&all);
	}
	return (0);
}

int	stop_engine(void *ptr)
{
	t_all *all;

	all = (t_all *)ptr;
	music_stop(all, all->music);
	music_stop(all, all->sound);
	music_stop(all, all->wsound);
	free_all(all);
	ft_putstr_fd("cub3D stopped", 1);
	exit(0);
}