/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 23:09:59 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char*	get_error_msg(int code)
{
	const int n = 10; //Cannot use const due to norm error
	static char* errors[10];

	errors[0] = "Unknown error";
	errors[1] = "Invalid file extension";
	errors[2] = "No such file or directory";
	errors[3] = "";
	errors[4] = "";
	errors[5] = "";
	errors[6] = "";
	errors[7] = "";
	errors[7] = "";
	errors[8] = "";
	errors[9] = "";
	
	code = (code < 1 && code > n - 1) ? 0 : code;
	return (errors[code]);
}

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
	map->NO_texture = 0;  
	map->SO_texture = 0;
	map->WE_texture = 0;
	map->EA_texture = 0;
	map->sprite = 0;
	map->f[0] = 0;
	map->f[1] = 0;
	map->f[2] = 0;
	map->c[0] = 0;
	map->c[1] = 0;
	map->c[2] = 0;
	map->f_color_set = 0;
	map->c_color_set = 0;
}

int main(int argc, char **argv)
{
	t_map	map;

	set_defaults(&map);
	if (argc == 2 || argc == 3)
	{
		if (check_file(argv[1], ".cub"))
			return (-1);
		if (argc == 3 && check_save_arg(argv[2]))
			return (-1);
		if (check_map(argv[1], &map))
			return (-1);
		(argc == 2) ? link_start() : make_screenshot();
	}
	else
		print_error("Argument error", "Invalid number of arguments", 0);
	return (0);
}