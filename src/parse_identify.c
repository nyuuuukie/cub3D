/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:50:37 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_identify_line_bonus(t_map *map)
{
	if (!ft_strncmp(map->line, "SK", 2))
		parse_path(map, &map->sk_path, "SK", ".xpm");
	else if (!ft_strncmp(map->line, "WP", 2))
		parse_wpath(map, &map->wp_path, "WP", ".anim");
	else if (!ft_strncmp(map->line, "TP", 2))
		parse_wpath(map, &map->tp_path, "TP", ".anim");
	else if (!ft_strncmp(map->line, "DG", 2))
		parse_wpath(map, &map->dg_path, "DG", ".anim");
	else if (!ft_strncmp(map->line, "FT", 2))
		parse_path(map, &map->ft_path, "FT", ".xpm");
	else if (!ft_strncmp(map->line, "AS", 2))
		parse_path(map, &map->as_path, "AS", ".xpm");
	else if (!ft_strncmp(map->line, "KS", 2))
		parse_path(map, &map->csound, "KS", ".mp3");
	else if (!ft_strncmp(map->line, "MC", 2))
		parse_path(map, &map->music, "MC", ".mp3");
	else if (!ft_strncmp(map->line, "SD", 2))
		parse_path(map, &map->sound, "SD", ".mp3");
	else if (!ft_strncmp(map->line, "WS", 2))
		parse_path(map, &map->wsound, "WS", ".mp3");
	else
		throw_parse_error(ERR_ID_NOT_FOUND, 0);
}

void	parse_identify_line(t_map *map)
{
	if (!ft_strncmp(map->line, "R", 1))
		parse_resolution(map);
	else if (!ft_strncmp(map->line, "NO", 2))
		parse_path(map, &map->no_path, "NO", ".xpm");
	else if (!ft_strncmp(map->line, "SO", 2))
		parse_path(map, &map->so_path, "SO", ".xpm");
	else if (!ft_strncmp(map->line, "WE", 2))
		parse_path(map, &map->we_path, "WE", ".xpm");
	else if (!ft_strncmp(map->line, "EA", 2))
		parse_path(map, &map->ea_path, "EA", ".xpm");
	else if (!ft_strncmp(map->line, "S ", 2))
		parse_path(map, &map->sprite, "S", ".xpm");
	else if (!ft_strncmp(map->line, "F ", 2))
		parse_color(map, &map->f, "F");
	else if (!ft_strncmp(map->line, "C ", 2))
		parse_color(map, &map->c, "C");
	else if (map->bonus == 1)
		parse_identify_line_bonus(map);
	else
		throw_parse_error(ERR_ID_NOT_FOUND, 0);
}
