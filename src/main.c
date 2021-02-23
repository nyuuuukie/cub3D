/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/23 08:06:15 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		mlx_try(t_map *map)
{
	//void    *mlx;
	void    *mlx_win = NULL;
	(void)map;
    //mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, map->r_width, map->r_height, "Hello www!");
	//mlx_loop(mlx);
	printf("%p", mlx_win);
	return (0);
}

int 	start_engine(t_map *map, int mode)
{
	if (mode == 2)
	{
		mlx_try(map);
	}
	else if (mode == 3)
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
	map->tr.i = 0;
	map->tr.line = 0;
	get_map(map);
}

int main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2 || argc == 3)
	{
		set_defaults(&map);
		map.line = argv[1];
		check_file_path(&map, ".cub");
		if (argc == 3)
			check_save_arg(argv[2]);
		parse_scene_file(&map, argv[1]);
		start_engine(&map, argc);
	}
	else
		throw_error(ERR_ARG_NUM, 0);
	return (0);
}