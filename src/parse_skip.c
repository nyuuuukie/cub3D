/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:53:27 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_symbol(t_map *map, char c)
{
	while (map->line[map->tr.i] == c)
		map->tr.i++;
}

void	skip_empty_lines(t_map *map)
{
	int	res;

	res = 1;
	while ((res = map_getline(map)) > 0 && map->line[0] == '\0')
	{
		map->tr.line++;
		free(map->line);
	}
	map->tr.line++;
	if (res == 0)
	{
		free(map->line);
		throw_parse_error(ERR_MAP_MISSING, 0);
	}
}
