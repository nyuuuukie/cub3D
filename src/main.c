/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/19 18:01:35 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int start_engine(t_map *map)
{
	if (map->run_mode == START_CUB3D)
	{
		map->run_mode--;
	}
	else if (map->run_mode == MAKE_SCREENSHOT)
	{
		map->run_mode--;
	}
	return (map->run_mode);
}

void	set_defaults(t_map *map)
{
	map->run_mode = 0;
	map->r_height = 0;
	map->r_width = 0;
	map->NO_path = 0;  
	map->SO_path = 0;
	map->WE_path = 0;
	map->EA_path = 0;
	map->sprite = 0;
	map->f[0] = 0;
	map->f[1] = 0;
	map->f[2] = 0;
	map->c[0] = 0;
	map->c[1] = 0;
	map->c[2] = 0;
	map->f_set = 0;
	map->c_set = 0;
	map->lst = 0;
	map->arr = 0;
	get_map(map);
}

int main(int argc, char **argv)
{
	t_map	map;

	set_defaults(&map);
	if (argc == 2 || argc == 3)
	{
		check_file_path(argv[1], ".cub");
		map.run_mode = argc == 2 ? START_CUB3D : MAKE_SCREENSHOT;
		map.run_mode == MAKE_SCREENSHOT ? check_save_arg(argv[2]) : NULL;
		parse_scene_file(argv[1], &map);
		start_engine(&map);
	}
	else
		throw_error(ERR_ARG_NUM, 0, 0);
	return (0);
}