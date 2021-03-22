/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/22 11:57:54 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;
// 	int     offset;
	
// 	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
//     dst = data->addr + offset;
//     *(unsigned int*)dst = color;
// }

// void	set_scale(t_all *all)
// {
// 	int scale_w;
// 	int scale_h;

// 	#ifdef SCALE
// 		scale_w = 1;
// 		scale_h = 1;
// 		all->scale = SCALE * scale_w * scale_h;
// 	#else
// 		scale_w = (all->map->w - 2 * all->padding) / all->map->cols;
// 		scale_h = (all->map->h - 2 * all->padding) / all->map->rows;
// 		all->scale = scale_h < scale_w ? scale_h : scale_w; 
// 	#endif
// }

// float	get_radian(float angle)
// {
// 	return angle * M_PI / 180;
// }

// void	throw_ray(t_all *all, t_plr *ray, int color)
// {
// 	float radian = get_radian(ray->start);

// 	while (all->map->arr[(int)(ray->y / all->scale)][(int)(ray->x / all->scale)] != '1')
// 	{
// 		ray->x += cos(radian);
// 		ray->y += sin(radian);
// 		my_mlx_pixel_put(all->img, ray->x, ray->y, color);
// 	}
// }

// void	ft_cast_rays(t_all *all, int color)
// {
// 	t_plr	ray = *all->plr;
// 	ray.start = ray.dir - (FOV / 2);
// 	ray.end = ray.dir + (FOV / 2);
 
// 	while (ray.start <= ray.end)
// 	{
// 		ray.x = all->plr->x;
// 		ray.y = all->plr->y;

// 		throw_ray(all, &ray, color);
// 		ray.start += (float)FOV / (float)RPA;
// 	}
// }

// void	put_cell(t_all *all, t_data *img, int x0, int y0, int color)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < all->scale)
// 	{
// 		j = 0;
// 		while (j < all->scale)
// 		{
// 			my_mlx_pixel_put(img, x0 + j, y0 + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	get_minimap_img(t_all *all, int x0, int y0, int color)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < all->map->rows)
// 	{
// 		j = 0;
// 		while (j < all->map->cols + 1)
// 		{
// 			if (all->map->arr[i][j] == '1')
// 				put_cell(all, all->img, x0 + j * all->scale, y0 + i * all->scale, color);
// 			else
// 				put_cell(all, all->img, x0 + j * all->scale, y0 + i * all->scale, 0x00FFFFFF);
// 			j++;  
// 		}
// 		i++;
// 	}
// }

// void	put_minimap(t_all *all, int x0, int y0, int color)
// {
// 	static int raycolor = 0x00010101;
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < all->map->rows)
// 	{
// 		j = 0;
// 		while (j < all->map->cols + 1)
// 		{
// 			if (all->map->arr[i][j] == '1')
// 				put_cell(all, all->img, x0 + j * all->scale, y0 + i * all->scale, color);
// 			else if (all->map->arr[i][j] == '2')
// 				put_cell(all, all->img, x0 + j * all->scale, y0 + i * all->scale, 0x00FF0000);
// 			else
// 				put_cell(all, all->img, x0 + j * all->scale, y0 + i * all->scale, 0x00FFFFFF);
// 			j++;  
// 		}
// 		i++;
// 	}
// 	my_mlx_pixel_put(all->img,  x0 + all->plr->x, y0 + all->plr->y, 0x00FF00FF);
// 	//put_cell(all, x0 + all->plr->x, y0 + all->plr->y, 0x00FF0000);
// 	raycolor += 10000;
// 	ft_cast_rays(all, raycolor);
// }

// int 	render(t_all *all, t_data *img)
// {
//     put_minimap(all, all->padding, all->padding, 0x00242424);
// 	mlx_put_image_to_window(all->mlx, all->mlx_win, img->img, 0, 0);
// 	return (0);
// }

// int		change_pos(t_all *all, float delx, float dely)
// {
// 	float x;
// 	float y;

// 	x = all->plr->x + delx;
// 	y = all->plr->y + dely;

// 	if (all->map->arr[(int)(y / all->scale)][(int)(x / all->scale)] != '1') //TO FIX
// 	{
// 		all->plr->x = x;
// 		all->plr->y = y;
// 	}
// 	return (0);
// }

// int		key_hook(int keycode, t_all *all)
// {
// 	mlx_do_sync(all->mlx);
// 	if (keycode == KEY_W)
// 		change_pos(all, 0, -1);
// 	else if (keycode == KEY_S)
// 		change_pos(all, 0, 1);
// 	else if (keycode == KEY_A)
// 		change_pos(all, -1, 0);
// 	else if (keycode == KEY_D)
// 		change_pos(all, 1, 0);
// 	else if (keycode == KEY_LEFT)
// 		all->plr->dir -= M_PI;
// 	else if (keycode == KEY_RIGHT)
// 		all->plr->dir += M_PI;
// 	render(all, all->img);
// 	return (0);
// }

// void	init_coord_plr(t_all *all)
// {
// 	int i;
// 	int j;

// 	i = 1;
// 	while (i < all->map->rows)
// 	{
// 		j = 1;
// 		while (j < all->map->cols + 1)
// 		{
// 			if (ft_strchr("NSWE", all->map->arr[i][j]))
// 			{
// 				all->plr->dir = 0;

// 				all->plr->x = (j + 0.5) * all->scale;
// 				all->plr->y = (i + 0.5) * all->scale;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int		check_screen_size(t_all *all)
// {
// 	int current_width;
// 	int current_height;

// 	mlx_get_screen_size(all->mlx, &current_width, &current_height);
// 	if (all->map->h > current_height)
// 		all->map->h = current_height;
// 	if (all->map->w > current_width)
// 		all->map->w = current_width;
// 	return (0);	
// }

// int		mlx_try(t_map *map)
// {
// 	t_all all;
// 	t_plr plr;
// 	t_data img;
// 	all.plr = &plr;
// 	all.map = map;
// 	all.padding = 0;
	
// 	//Init
// 	all.mlx = mlx_init();
// 	all.mlx_win = mlx_new_window(all.mlx, map->w, map->h, "cub3D");
// 	check_screen_size(&all);

// 	//Get image
// 	img.img = mlx_new_image(all.mlx, map->w, map->h);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
// 	setup_textures(&all);
// 	all.img = &img;

// 	//Set default values
// 	set_scale(&all);
// 	init_coord_plr(&all);
	
// 	mlx_hook(all.mlx_win, 2, 1L, key_hook, &all);
// 	mlx_loop(all.mlx);

// 	return (0);
// }


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
		throw_parse_error(ERR_ARG_NUM, 0);
	return (0);
}