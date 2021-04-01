/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 16:07:08 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_add_node(t_list **head, char *line)
{
	size_t		i;
	size_t		line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (ft_strchr(ALLOWED_MAP_SPEC, line[i++]) == NULL)
		{
			ft_lstclear(head, free);
			throw_parse_error(ERR_MISSING_SYMBOL, line);
		}
	}
	ft_lstadd_back(head, ft_lstnew(ft_strdup(line)));
}

int		map_to_list(t_map *map)
{
	int	res;

	res = 1;
	skip_empty_lines(map);
	while (res)
	{
		map_add_node(&map->lst, map->line);
		free(map->line);
		res = map_getline(map);
		if (map->line[0] == '\0')
			throw_parse_error(ERR_MISSING_SYMBOL, "Empty line in map");
	}
	map_add_node(&map->lst, map->line);
	free(map->line);
	map->rows = ft_lstsize(map->lst) + 2;
	map->cols = ft_lstmax_cont_len(map->lst);
	return (0);
}

int		map_getline(t_map *map)
{
	int res;

	if ((res = get_next_line(map->fd, &map->line)) < 0)
		throw_parse_error(ERR_GET_NEXT_LINE, 0);
	return (res);
}
