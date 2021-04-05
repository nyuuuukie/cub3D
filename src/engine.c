/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:35:59 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 07:05:59 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		start_engine(t_map *map, int mode)
{
	t_all *all;

	all = (t_all *)malloc(sizeof(t_all));
	if (all == NULL)
		throw_parse_error(ERR_CANNOT_ALLOC, "Cannot allocate t_all");
	all->map = map;
	if (mode == 2)
	{
		all->screen = 0;
		start_main_loop(all);
	}
	else if (mode == 3)
	{
		all->screen = 1;
		make_screenshot(all);
	}
	return (0);
}

#ifdef BONUS

void	kill_music(t_all *all)
{
	if (all->map->bonus && all->music != 0)
		kill(all->music, SIGKILL);
	if (all->map->bonus && all->sound != 0)
		kill(all->sound, SIGKILL);
	if (all->map->bonus && all->wsound != 0)
		kill(all->wsound, SIGKILL);
	if (all->map->bonus && all->csound != 0)
		kill(all->csound, SIGKILL);
}

int		stop_engine(void *ptr)
{
	t_all *all;

	all = (t_all *)ptr;
	all->exit = 1;
	kill_music(all);
	free_all(all);
	ft_putstr_fd("cub3D stopped", 1);
	exit(0);
}

#else

void	kill_music(t_all *all)
{
	(void)all;
}

int		stop_engine(void *ptr)
{
	t_all *all;

	all = (t_all *)ptr;
	all->exit = 1;
	free_all(all);
	kill(all->music, SIGKILL);
	ft_putstr_fd("cub3D stopped", 1);
	exit(0);
}

#endif
