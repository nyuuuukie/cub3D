/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 04:50:14 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 07:05:24 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_level(t_all *all)
{
	char	*path;
	int		w;
	int		h;

	all->exit = 0;
	w = all->map->w;
	h = all->map->h;
	path = ft_strdup(all->map->nl_path);
	mlx_loop_hook(all->mlx, 0, all);
	all->mlx = 0;
	free_all(all);
	parse_scene_file(all->map, path);
	all->map->w = w;
	all->map->h = h;
	free(path);
	start_engine(all->map, 2);
}
