/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:48:07 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 19:30:39 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_all *all)
{
	all->mlx = mlx_init();
	if (!all->mlx)
		throw_engine_error(all, ERR_MLX_WIN_FAIL, 0);
	init_screen_size(all);
	if (all->screen == 0)
	{
		all->win = mlx_new_window(all->mlx, all->map->w, all->map->h, "cub3D");
		if (!all->win)
			throw_engine_error(all, ERR_MLX_WIN_FAIL, 0);
	}
}

void	init_img(t_all *all, t_img *img)
{
	img->img = mlx_new_image(all->mlx, all->map->w, all->map->h);
	if (!img->img)
		throw_engine_error(all, ERR_MLX_IMG_FAIL, 0);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		throw_engine_error(all, ERR_MLX_IMG_FAIL, 0);
}

void	init_texture(t_all *all, char *path, t_texture *t)
{
	t_img *img;

	img = &(t->img);
	img->img = mlx_xpm_file_to_image(all->mlx, path, &t->w, &t->h);
	if (img->img == NULL)
		throw_engine_error(all, ERR_MLX_TXT_FAIL, path);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->end);
	if (!img->addr)
		throw_engine_error(all, ERR_MLX_TXT_FAIL, path);
}

void	init_mult_textures(t_all *all, t_texture txt[], char *dir, int num)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	path = ft_strjoin(dir, "/0.xpm");
	len = ft_strlen(path);
	while (i < num)
	{
		init_texture(all, path, &(txt[i]));
		path[len - 5] += 1;
		i++;
	}
	free(path);
}

void	init_textures(t_all *all)
{
	init_texture(all, all->map->no_path, &all->no);
	init_texture(all, all->map->so_path, &all->so);
	init_texture(all, all->map->we_path, &all->we);
	init_texture(all, all->map->ea_path, &all->ea);
	init_texture(all, all->map->sprite, &all->s1);
	if (all->map->bonus)
	{
		init_texture(all, all->map->as_path, &all->s2);
		init_texture(all, all->map->ft_path, &all->flr);
		init_texture(all, all->map->sk_path, &all->sky);
		init_mult_textures(all, all->wpn, all->map->wp_path, ANIM_FRAMES);
		init_mult_textures(all, all->tp, all->map->tp_path, ANIM_FRAMES);
		init_mult_textures(all, all->digits, all->map->dg_path, 10);
	}
}
