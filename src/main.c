/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/24 11:06:20 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;


typedef struct	s_plr
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				  t_plr;

typedef struct	s_all
{
	void    *mlx;
	void    *mlx_win;
	t_data	*img;
	t_map	*map;
	t_plr	*plr;
	int		scale;
	int		padding;

}				t_all;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
	int     offset;
	
	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
    dst = data->addr + offset;
    *(unsigned int*)dst = color;
}
 
void	put_triangle(t_data *timg, int x, int y0, int y)
{
	int x0 = 1;
	while (y0 < y)
	{
		int temp = x0;
		while (temp--)
			my_mlx_pixel_put(timg, x - (x0 / 2) + temp, y0, rand());
		y0++;
		x0++;
	}
}

void	put_circle(t_data *timg, int x, int y, int r)
{
	int x0 = x - r;
	int y0 = y - r;
	while (y0 < y + r)
	{
		x0 = x - r;
		while (x0 < x + r)
		{
			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r)
				my_mlx_pixel_put(timg, x0, y0, rand());
			x0++;
		}
		y0++;
	}
}

void	put_background(t_data *timg, t_map *map, int color)
{
	int i;
	int j;

	i = 0;
	while (i < map->r_height)
	{
		j = 0;
		while (j < map->r_width)
		{
			my_mlx_pixel_put(timg, j, i, color);
			j++;
		}
		i++;
	}
}

//////////////////////////////////////////////////////////////////////

void	set_scale(t_all *all)
{
	int scale_w;
	int scale_h;

	#ifdef SCALE
		scale_w = 1;
		scale_h = 1;
		all->scale = SCALE * scale_w * scale_h;
	#else
		scale_w = (all->map->r_width - 2 * all->padding) / all->map->cols;
		scale_h = (all->map->r_height - 2 * all->padding) / all->map->rows;
		all->scale = scale_h < scale_w ? scale_h : scale_w; 
	#endif
}

void	put_cell(t_all *all, int x0, int y0, int color)
{
	int i;
	int j;

	i = 0;
	while (i < all->scale)
	{
		j = 0;
		while (j < all->scale)
		{
			my_mlx_pixel_put(all->img, x0 + j, y0 + i, color);
			j++;
		}
		i++;
	}
}

void	put_minimap(t_all *all, int x0, int y0, int color)
{
	int i;
	int j;

	i = 0;
	while (i < all->map->rows)
	{
		j = 0;
		while (j < all->map->cols + 1)
		{
			if (all->map->arr[i][j] == '1')
				put_cell(all, x0 + j * all->scale, y0 + i * all->scale, color);
			if (all->map->arr[i][j] == '2')
				put_cell(all, x0 + j * all->scale, y0 + i * all->scale, 0xFFFFFFFF);
			if (ft_strchr("NSWE", all->map->arr[i][j]))
				my_mlx_pixel_put(all->img, all->plr->x + j, all->plr->y + i, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}



int 	render(t_all *all)
{
	put_minimap(all, all->padding, all->padding, rand());
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 10, 10);
	return (0);
}

int change_pos(t_all *all, float delx, float dely)
{
	float x;
	float y;

	x = all->plr->x + delx;
	y = all->plr->y + dely;

	if (all->map->arr[(int)(y / all->scale)][(int)(x / all->scale)] != '1')
	{
		all->plr->x = x;
		all->plr->y = y;
	}
	return (0);
}

int key_hook(int keycode, t_all *all)
{
	if (keycode == 119)
		change_pos(all, 0, -1);
	if (keycode == 97)
		change_pos(all, -1, 0);
	if (keycode == 115)
		change_pos(all, 0, 1);
	if (keycode == 100)
		change_pos(all, 1, 0);
	render(all);
	return (0);
}

void init_coord_plr(t_all *all)
{
	int i;
	int j;

	i = 1;
	while (i < all->map->rows)
	{
		j = 1;
		while (j < all->map->cols + 1)
		{
			if (ft_strchr("NSWE", all->map->arr[i][j]))
			{
				all->plr->x = j * all->scale;
				all->plr->y = i * all->scale;
			}
			j++;
		}
		i++;
	}
}


int check_screen_size(t_all *all)
{
	int current_width;
	int current_height;

	mlx_get_screen_size(all->mlx, &current_width, &current_height);
	if (all->map->r_height > current_height)
		all->map->r_height = current_height;
	if (all->map->r_width > current_width)
		all->map->r_width = current_width;
	return (0);	
}


int		mlx_try(t_map *map)
{
	t_all all;
	t_plr plr;
	t_data img;
	all.plr = &plr;
	all.map = map;
	all.padding = 0;
	
	//Init
	all.mlx = mlx_init();
	all.mlx_win = mlx_new_window(all.mlx, map->r_width, map->r_height, "cub3D");
	check_screen_size(&all);

	//Get image
	img.img = mlx_new_image(all.mlx, map->r_width, map->r_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	all.img = &img;

	//Set default values
	set_scale(&all);
	init_coord_plr(&all);
	
	mlx_hook(all.mlx_win, 2, 1L, key_hook, &all);
	mlx_loop(all.mlx);
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

int		main(int argc, char **argv)
{
	t_map	map;

	set_defaults(&map);
	if (argc == 2 || argc == 3)
	{
		map.line = argv[1];
		check_file_path(&map, ".cub");
		check_save_arg(argc, argv);
		parse_scene_file(&map, argv[1]);
		start_engine(&map, argc);
	}
	else
		throw_error(ERR_ARG_NUM, 0);
	return (0);
}