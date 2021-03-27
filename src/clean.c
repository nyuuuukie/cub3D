/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:01:24 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/27 18:57:46 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    free_all_bonus(t_all *all)
{
    if (all->map->SK_path)
        mlx_destroy_image(all->mlx, all->sky.img.img);
    if (all->map->FT_path)
        mlx_destroy_image(all->mlx, all->flr.img.img);
    if (all->map->WP_path)
        mlx_destroy_image(all->mlx, all->wpn[all->wp_i].img.img);
    if (all->map->AS_path)
        mlx_destroy_image(all->mlx, all->s2.img.img);
}


void    free_all(t_all *all)
{
    // if (all && all->mlx)
    // {
        free_map(all->map);
        mlx_destroy_image(all->mlx, all->no.img.img);
        mlx_destroy_image(all->mlx, all->so.img.img);
        mlx_destroy_image(all->mlx, all->ea.img.img);
        mlx_destroy_image(all->mlx, all->we.img.img);
        mlx_destroy_image(all->mlx, all->s1.img.img);
        if (all->map->bonus)
            free_all_bonus(all);
        mlx_destroy_image(all->mlx, all->img.img);
        if (all->screen == 0)
            mlx_destroy_window(all->mlx, all->win);
        free(all->ZBuffer);
        free(all->mlx);
        if (all->music != 0)
            kill(all->music, SIGKILL);
        if (all->sound != 0)
            kill(all->sound, SIGKILL);
    // }
}