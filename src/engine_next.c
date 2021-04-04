/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 04:50:14 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 04:52:19 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_level(t_all *all)
{
	char *path;

	path = ft_strdup(all->map->nl_path);
	free_all(all);
	kill_music(all);
	parse_scene_file(all->map, path);
	free(path);
	start_engine(all->map, 2);
}
