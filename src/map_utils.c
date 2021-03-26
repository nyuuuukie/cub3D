/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:47:11 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/26 16:36:28 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_map *map)
{
	if (map->sprite) 
		free(map->sprite);
	if (map->NO_path)
		free(map->NO_path);
	if (map->SO_path)
		free(map->SO_path);
	if (map->WE_path)
		free(map->WE_path);
	if (map->EA_path)
		free(map->EA_path);
	if (map->SK_path)
		free(map->SK_path);
	if (map->WP_path)
		free(map->WP_path);
	if (map->FT_path)
		free(map->FT_path);
	if (map->sound)
		free(map->sound);
	if (map->music)
		free(map->music);
	if (map->arr)
		arr_delete(map->arr);
	if (map->lst)
		ft_lstclear(&map->lst, free);
	set_defaults(map);
}

t_map	*get_map(t_map *map)
{
	static t_map	*ptr;

	if (ptr == NULL)
		ptr = map;
	return (ptr);
}

void	set_defaults(t_map *map)
{
	map->bonus = 0;
	map->w = 0;
	map->h = 0;
	map->NO_path = 0;  
	map->SO_path = 0;
	map->WE_path = 0;
	map->EA_path = 0;
	map->SK_path = 0;
	map->WP_path = 0;
	map->FT_path = 0;
	map->AS_path = 0;
	map->WF_path = 0;
	map->music = 0;
	map->sound = 0;
	map->wsound = 0;
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
	map->sprites = 0;


	#ifdef BONUS
		map->bonus = 1;
	#endif
	get_map(map);
}