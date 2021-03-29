/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:01:24 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/30 00:15:28 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    free_all_bonus(t_all *all)
{
    int i;

    i = 0;
    if (all->map->SK_path)
        mlx_destroy_image(all->mlx, all->sky.img.img);
    if (all->map->FT_path)
        mlx_destroy_image(all->mlx, all->flr.img.img);
    if (all->map->AS_path)
        mlx_destroy_image(all->mlx, all->s2.img.img);
    if (all->map->WP_path)
    {
        while (i < ANIM_FRAMES)
            mlx_destroy_image(all->mlx, all->wpn[i++].img.img);
    }
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
    free(all->ZBuffer);
    free(all->mlx);
    // while (1);
}