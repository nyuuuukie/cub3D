/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:48:07 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/21 19:02:46 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_window(t_all *all)
{
	all->mlx = mlx_init();
	if (!all->mlx)
		throw_error(ERR_MLX_WIN_FAIL, 0);
	init_screen_size(all);
	if (all->screen == 0)
	{
		all->win = mlx_new_window(all->mlx, all->map->w, all->map->h, "cub3D");
		if (!all->win)
			throw_error(ERR_MLX_WIN_FAIL, 0);
	}
}

void	init_img(t_all *all, t_img *img)
{
	img->img = mlx_new_image(all->mlx, all->map->w, all->map->h);
	if (!img->img)
		throw_error(ERR_MLX_IMG_FAIL, 0);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		throw_error(ERR_MLX_IMG_FAIL, 0);
}

void	init_texture(void *mlx, char *path, t_texture *t)
{
	t_img *img;

	img = &t->img; 
	img->img = mlx_xpm_file_to_image(mlx, path, &t->w, &t->h);
	if (!img->img)
		throw_error(ERR_MLX_TXT_FAIL, path);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		throw_error(ERR_MLX_TXT_FAIL, path);
}

void	init_textures(t_all *all)
{
	init_texture(all->mlx, all->map->NO_path, &all->no);
	init_texture(all->mlx, all->map->SO_path, &all->so);
	init_texture(all->mlx, all->map->WE_path, &all->we);
	init_texture(all->mlx, all->map->EA_path, &all->ea);
	init_texture(all->mlx, all->map->sprite, &all->s);
	#ifdef WEAPON
		// init_texture(all->mlx, all->map->WP_path, &all->wpn);
		init_texture(all->mlx, "./textures/weapon.xpm", &all->wpn);
	#endif
	#ifdef FLOOR
		// init_texture(all->mlx, all->map->F_path, &all->flr);
		init_texture(all->mlx, "./textures/floor.xpm", &all->flr);
	#endif
	#ifdef CEIL
		// init_texture(all->mlx, all->map->C_path, &all->flr);
		init_texture(all->mlx, "./textures/cement1.xpm", &all->sky);
	#endif
	#ifdef SKY
		// init_texture(all->mlx, all->map->SK_path, &all->sky);
		init_texture(all->mlx, "./textures/cyber.xpm", &all->sky);
	#endif
}

void	init_screen_size(t_all *all)
{
	#ifdef LINUX
		mlx_get_screen_size(all->mlx, &all->screen_w, &all->screen_h);
	#else
		mlx_get_screen_size(&all->screen_w, &all->screen_h);
	#endif

	if (all->map->h > all->screen_h)
		all->map->h = all->screen_h;
	if (all->map->w > all->screen_w)
		all->map->w = all->screen_w;
}