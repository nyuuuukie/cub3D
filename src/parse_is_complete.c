/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_is_complete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:55:11 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 02:57:07 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_prm_complete_bonus(t_map *map)
{
	if (map->wp_path == 0 || map->sk_path == 0 || map->tp_path == 0)
		return (0);
	if (map->ft_path == 0 || map->as_path == 0)
		return (0);
	if (map->sound == 0 || map->music == 0 || map->ct_path == 0)
		return (0);
	if (map->wsound == 0 || map->csound == 0 || map->nl_path == 0)
		return (0);
	return (1);
}

int		is_prm_complete(t_map *map)
{
	int res;

	res = 1;
	if (map->w == 0 || map->h == 0)
		res = 0;
	if (map->so_path == 0 || map->no_path == 0)
		res = 0;
	if (map->we_path == 0 || map->ea_path == 0)
		res = 0;
	if (map->c.set == 0 || map->f.set == 0)
		res = 0;
	if (map->sprite == 0)
		res = 0;
	if (map->bonus)
		res *= is_prm_complete_bonus(map);
	return (res);
}
