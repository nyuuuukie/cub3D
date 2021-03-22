/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:45:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/22 11:57:54 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_extension(t_map *map, const char *ext)
{
	int i;
	int end;
	
	i = 0;
	end = ft_strlen(map->line) - 1;
	while (i < EXTENSION_LEN && end != 0 && map->line[end] != '.')
	{
		i++;
		end--;
	}
	if (!(end != 0 && !ft_strcmp(&map->line[end], ext)))
	{
		map->tr.i = end;
		throw_parse_error(ERR_WRONG_EXT, &map->line[end]);	
	}
	return (0);
}

int		check_music_path(t_map *map, char *ext)
{
	if (!ft_strcmp(&map->line[map->tr.i], "\0"))
		throw_parse_error(ERR_NO_FILENAME, 0);
	check_extension(map, ext);
	return (0);
}

int		check_file_path(t_map *map, char *ext)
{
	int fd;

	if (!ft_strcmp(&map->line[map->tr.i], "\0"))
		throw_parse_error(ERR_NO_FILENAME, 0);
	check_extension(map, ext);
	if ((fd = open(&map->line[map->tr.i], O_RDONLY)) < 0)
		throw_parse_error(ERR_NO_FILE, &map->line[map->tr.i]);
	else
		close(fd);
	return (0);
}

int check_save_arg(int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save"))
			throw_parse_error(ERR_INVALID_ARG, argv[2]);
	}
	return (0);
}