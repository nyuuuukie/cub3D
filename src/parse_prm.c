/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:31:19 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(t_map *map)
{
	map->tr.i = 0;
	check_and_skip(map, 'R');
	check_and_skip(map, ' ');
	skip_symbol(map, ' ');
	get_number(map, " ", &map->w);
	check_and_skip(map, ' ');
	skip_symbol(map, ' ');
	get_number(map, " ", &map->h);
	skip_symbol(map, ' ');
	check_symbol(map, '\0');
	print_status("Resolution", 0, "OK");
}

void	parse_color(t_map *map, t_clr *clr, char *name)
{
	int j;

	j = 0;
	if (clr->set == 1)
		throw_parse_error(ERR_DUPLICATE_SPEC, "Color");
	check_and_skip(map, name[0]);
	check_and_skip(map, ' ');
	while (j < 3)
	{
		skip_symbol(map, ' ');
		get_number(map, " ,", &clr->val[j]);
		skip_symbol(map, ' ');
		if (j != 2)
			check_and_skip(map, ',');
		check_number(clr->val[j], COLOR_MIN_VALUE, COLOR_MAX_VALUE);
		j++;
	}
	check_symbol(map, '\0');
	clr->set = 1;
	print_status("Color", name, "OK");
}

void	parse_wpath(t_map *map, char **texture, char *name, char *ext)
{
	map->tr.i = 0;
	check_duplicate(*texture, map->line);
	while (map->tr.i < ft_strlen(name))
		check_and_skip(map, name[map->tr.i]);
	check_symbol(map, ' ');
	skip_symbol(map, ' ');
	check_file_path(map, ext);
	check_anim_dir(map);
	*texture = ft_strdup(&map->line[map->tr.i]);
	print_status("Texture", name, "OK");
}

void	parse_path(t_map *map, char **texture, char *name, char *ext)
{
	map->tr.i = 0;
	check_duplicate(*texture, map->line);
	while (map->tr.i < ft_strlen(name))
		check_and_skip(map, name[map->tr.i]);
	check_symbol(map, ' ');
	skip_symbol(map, ' ');
	check_file_path(map, ext);
	*texture = ft_strdup(&map->line[map->tr.i]);
	print_status("Texture", name, "OK");
}
