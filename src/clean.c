/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:01:24 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 03:27:15 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    free_mlp_texture(t_all *all, t_texture txt[], int len)
{
    int i;

    i = 0;
    while (i < len && txt[i].img.img)
        mlx_destroy_image(all->mlx, txt[i++].img.img);
}

void    free_all_bonus(t_all *all)
{
    if (all->map->sk_path && all->mlx && all->sky.img.img)
        mlx_destroy_image(all->mlx, all->sky.img.img);
    if (all->map->ft_path && all->mlx && all->flr.img.img)
        mlx_destroy_image(all->mlx, all->flr.img.img);
    if (all->map->as_path && all->mlx && all->s2.img.img)
        mlx_destroy_image(all->mlx, all->s2.img.img);
    if (all->mlx && all->map->wp_path)
        free_mlp_texture(all, all->wpn, ANIM_FRAMES);
    if (all->mlx && all->map->tp_path)
        free_mlp_texture(all, all->tp, ANIM_FRAMES);
    if (all->mlx && all->map->dg_path)
        free_mlp_texture(all, all->digits, 10);
}


void    free_all(t_all *all)
{
    if (all->mlx && all->no.img.img)
        mlx_destroy_image(all->mlx, all->no.img.img);
    if (all->mlx && all->so.img.img)
        mlx_destroy_image(all->mlx, all->so.img.img);
    if (all->mlx && all->ea.img.img)
        mlx_destroy_image(all->mlx, all->ea.img.img);
    if (all->mlx && all->we.img.img)
        mlx_destroy_image(all->mlx, all->we.img.img);
    if (all->mlx && all->s1.img.img)
        mlx_destroy_image(all->mlx, all->s1.img.img);
    if (all->map->bonus)
        free_all_bonus(all);
    if (all->mlx && all->img.img)
        mlx_destroy_image(all->mlx, all->img.img);
    if (all->screen == 0)
        mlx_destroy_window(all->mlx, all->win);
    free_map(all->map);
    free(all->zbuf);
    free(all->mlx);
    // while (1);
}