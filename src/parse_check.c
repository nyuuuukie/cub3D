/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:51:41 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_symbol(t_map *map, const char c)
{
	if (map->line[map->tr.i] != c)
		throw_parse_error(ERR_MISSING_SYMBOL, &map->line[map->tr.i]);
}

void	check_and_skip(t_map *map, const char c)
{
	check_symbol(map, c);
	map->tr.i++;
}

void	check_number(int num, int min, int max)
{
	if (num < min || num > max)
		throw_parse_error(ERR_OUT_OF_BOUND, 0);
}

void	check_duplicate(char *texture, char *ptr)
{
	if (texture != NULL)
		throw_parse_error(ERR_DUPLICATE_SPEC, ptr);
}

void	check_anim_dir(t_map *map)
{
	int		i;
	int		fd;
	int		len;
	char	*path;

	i = 0;
	path = ft_strjoin(&map->line[map->tr.i], "/0.xpm");
	len = ft_strlen(path);
	while (i < ANIM_FRAMES)
	{
		path[len - 5] = '0' + i;
		if ((fd = open(path, O_RDONLY)) < 0)
			throw_parse_error(ERR_NO_FILE, path);
		else
			close(fd);
		i++;
	}
	free(path);
}
