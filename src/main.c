/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/15 22:46:44 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int link_start()
{
	return (0);
}

int make_screenshot()
{
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
	map->f[0] = 0;
	map->f[1] = 0;
	map->f[2] = 0;
	map->c[0] = 0;
	map->c[1] = 0;
	map->c[2] = 0;
	map->f_set = 0;
	map->c_set = 0;
}

int main(int argc, char **argv)
{
	t_map	map;

	set_defaults(&map);
	if (argc == 2 || argc == 3)
	{
		if (check_file_path(argv[1], ".cub"))
			return (-1);
		if (argc == 3 && check_save_arg(argv[2]))
			return (-1);
		if (parse_scene_file(argv[1], &map))
			return (-1);
		(argc == 2) ? link_start() : make_screenshot();
	}
	else
		print_error(get_error_title(0), get_error_msg(0), 0);
	return (0);
}