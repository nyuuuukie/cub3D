/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:46:58 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/23 01:14:22 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		parse_map(t_map *map)
{
	map->tr.i = 0;
	map_to_list(map);
	
	map->rows = ft_lstsize(map->lst) + 2;
	map->cols = ft_lstmax_cont_len(map->lst);
	arr_create(&map->arr, map->rows, map->cols);
	arr_fill(map->arr, map->lst);
	validate_map(map);
	arr_replace(map->arr, '#', '0');
	print_status("Map's validation ", 0, "OK");
	return (0);
}

int		parse_prm(t_map *map)
{
	while (!is_prm_complete(map))
	{
		map->tr.i = 0;
		map->tr.line++;
		if (!parse_getline(map))
			throw_error(ERR_ID_NOT_FOUND, 0);
		if (ft_strcmp(map->line, "") != 0)
			parse_identify_line(map);
		free(map->line);
	}
	return (0);
}

void	parse_scene_file(t_map *map, char *path)
{
	map->fd = open(path, O_RDWR);
	map->tr.line = 0;
	parse_prm(map);
	parse_map(map);
	close(map->fd);
}

