/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/21 09:53:37 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int 	start_engine(t_map *map, int mode)
{
	(void)map;
	if (mode == START_CUB3D)
	{
		return (1);
	}
	else if (mode == MAKE_SCREENSHOT)
	{
		return (2);
	}
	return (0);
}

void	set_defaults(t_map *map)
{
	map->r_height = 0;
	map->r_width = 0;
	map->NO_path = 0;  
	map->SO_path = 0;
	map->WE_path = 0;
	map->EA_path = 0;
	map->sprite = 0;
	map->f.val[0] = 0;
	map->f.val[1] = 0;
	map->f.val[2] = 0;
	map->c.val[0] = 0;
	map->c.val[1] = 0;
	map->c.val[2] = 0;
	map->f.set = 0;
	map->c.set = 0;
	map->lst = 0;
	map->arr = 0;
	get_map(map);
}

int main(int argc, char **argv)
{
	int		mode;
	t_map	map;

	set_defaults(&map);
	if (argc == 2 || argc == 3)
	{
		mode = argc == 2 ? START_CUB3D : MAKE_SCREENSHOT;
		map.line = argv[1];
		check_file_path(&map, ".cub");
		if (mode == MAKE_SCREENSHOT)
			check_save_arg(argv[2]);
		parse_scene_file(&map, argv[1]);
		start_engine(&map, mode);
	}
	else
		throw_error(ERR_ARG_NUM, 0, 0);
	return (0);
}