/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:01:24 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/22 14:22:46 by mhufflep         ###   ########.fr       */
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
        mlx_destroy_image(all->mlx, all->wpn.img.img);
    if (all->map->SK_path || all->map->FT_path)
        mlx_destroy_image(all->mlx, all->wpn.img.img);
}


void    free_all(t_all *all)
{
    free_map(all->map);
    
    //check if all freed properly through parse error
    mlx_destroy_image(all->mlx, all->no.img.img);
    mlx_destroy_image(all->mlx, all->so.img.img);
    mlx_destroy_image(all->mlx, all->ea.img.img);
    mlx_destroy_image(all->mlx, all->we.img.img);
    mlx_destroy_image(all->mlx, all->s.img.img);
    free_all_bonus(all);
    mlx_destroy_image(all->mlx, all->img.img);
    if (all->screen == 0)
        mlx_destroy_window(all->mlx, all->win);

    free(all->ZBuffer);
    free(all->mlx);
    if (all->music != 0)
        kill(all->music);
    if (all->sound != 0)
        kill(all->sound, );
}