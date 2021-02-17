/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:46:58 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/17 07:36:34 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		parse_map(int fd, t_map *map)
{
	parse_map_to_list(fd, map);
	map->rows = ft_lstsize(map->lst);
	map->cols = ft_lstmax_cont_len(map->lst);
	map->arr = create_arr(map);
	parse_validate_map(map);
	print_status("Map's validation ", 0, "OK");
	return (0);
}

int		parse_prm(int fd, t_map *map)
{
	char	*line;
	int		line_num;

	while (!is_prm_complete(map))
	{
		line_num = inc_line_number(1);
		if (!parse_getline(fd, &line))
			throw_error(ERR_ID_NOT_FOUND, line_num, 0);
		if (ft_strcmp(line, "\0") != 0)
			parse_identify_line(line, map);
		free(line);
	}
	return (0);
}

int		parse_scene_file(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDWR);
	parse_prm(fd, map);
	parse_map(fd, map);

	close(fd);
	return (0);
}

