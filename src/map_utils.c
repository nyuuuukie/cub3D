/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:47:11 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 03:09:33 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void 	free_map_add(t_map *map)
{
	if (map->wp_path) 
		free(map->wp_path);
	if (map->tp_path) 
		free(map->tp_path);
	if (map->dg_path) 
		free(map->dg_path);
	if (map->as_path)
		free(map->as_path);
	if (map->sound)
		free(map->sound);
	if (map->music)
		free(map->music);
	if (map->sk_path)
		free(map->sk_path);
	if (map->ft_path)
		free(map->ft_path);
	if (map->wsound)
		free(map->wsound);
	if (map->csound)
		free(map->csound);
}

void	free_map(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	if (map->sprite) 
		free(map->sprite);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->arr)
		arr_delete(map->arr);
	if (map->lst)
		ft_lstclear(&map->lst, free);
	if (map->bonus)
		free_map_add(map);
	set_defaults(map);
}

t_map	*get_map(t_map *map)
{
	static t_map	*ptr;

	if (ptr == NULL)
		ptr = map;
	return (ptr);
}

void 	set_default_bonus(t_map *map)
{
	map->sk_path = 0;
	map->wp_path = 0;
	map->ft_path = 0;
	map->as_path = 0;
	map->tp_path = 0;
	map->dg_path = 0;
	map->music = 0;
	map->sound = 0;
	map->wsound = 0;
	map->csound = 0;
}

void	set_default_colors(t_map *map)
{
	map->f.val[0] = 0;
	map->f.val[1] = 0;
	map->f.val[2] = 0;
	map->c.val[0] = 0;
	map->c.val[1] = 0;
	map->c.val[2] = 0;
	map->f.set = 0;
	map->c.set = 0;
}

void	set_defaults(t_map *map)
{
	get_map(map);
	map->w = 0;
	map->h = 0;
	map->lst = 0;
	map->arr = 0;
	map->tr.i = 0;
	map->bonus = 0;
	map->sprite = 0;
	map->no_path = 0;
	map->so_path = 0;
	map->we_path = 0;
	map->ea_path = 0;
	map->tr.line = 0;
	map->sprites = 0;
	set_default_colors(map);
	set_default_bonus(map);
	#ifdef BONUS
		map->bonus = 1;	
	#endif
}