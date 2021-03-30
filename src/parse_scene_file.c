/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:46:58 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/30 23:19:07 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_scene_file(t_map *map, char *path)
{
	map->fd = open(path, O_RDWR);
	map->tr.line = 0;
	parse_prm(map);
	parse_map(map);
	close(map->fd);
}

int		parse_map(t_map *map)
{
	map->tr.i = 0;
	map_to_list(map);	
	arr_create(&map->arr, map->rows, map->cols);
	arr_fill(map->arr, map->lst);
	map_validate(map);
	
	arr_replace(map->arr, '#', '0');
	map->sprites = arr_replace(map->arr, 'x', '2');
	map->sprites += arr_replace(map->arr, 'T', 'T');
	map->keys = arr_replace(map->arr, '.', '3');
	map->sprites += map->keys;
	print_status("Map's validation ", 0, "OK");
	return (0);
}

int		parse_prm(t_map *map)
{
	while (!is_prm_complete(map))
	{
		map->tr.i = 0;
		map->tr.line++;
		if (!map_getline(map))
			throw_parse_error(ERR_ID_NOT_FOUND, 0);
		if (ft_strcmp(map->line, "") != 0)
			parse_identify_line(map);
		free(map->line);
	}
	return (0);
}
