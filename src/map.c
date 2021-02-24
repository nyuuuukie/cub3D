/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:47:11 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/24 11:50:02 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_map *map)
{
	map->sprite ? free(map->sprite) : NULL;
	map->NO_path ? free(map->NO_path) : NULL;
	map->SO_path ? free(map->SO_path) : NULL;
	map->WE_path ? free(map->WE_path) : NULL;
	map->EA_path ? free(map->EA_path) : NULL;
	map->arr ? arr_delete(map->arr) : NULL;
	map->lst ? ft_lstclear(&map->lst, free) : NULL;
	set_defaults(map);
}

t_map	*get_map(t_map *map)
{
	static t_map	*ptr;

	if (ptr == NULL)
		ptr = map;
	return (ptr);
}