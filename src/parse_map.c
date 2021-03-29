/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/29 22:06:22 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_atoi_u(char *s, int *number)
{
	int i;

	i = 0;
	*number = 0;
	while (ft_isdigit(s[i]) && i < R_MAX_LEN)
	{
		*number = *number * 10 + (s[i++] - '0');
    }
    return (i);
}

void	check_symbol(t_map *map, const char c)
{
	if (map->line[map->tr.i] != c)
		throw_parse_error(ERR_MISSING_SYMBOL, &map->line[map->tr.i]);
}

void	check_and_skip(t_map *map, const char c)
{
	check_symbol(map, c);
	map->tr.i++;
}

void	skip_symbol(t_map *map, char c)
{
	while (map->line[map->tr.i] == c)
		map->tr.i++;
}

void	get_number(t_map *map, char *separators, int *number)
{
	int res;

	if (map->line[map->tr.i] == '0' && ft_isdigit(map->line[map->tr.i + 1]))
		throw_parse_error(ERR_ZERO_BEFORE_NUM, &map->line[map->tr.i]);
	res = ft_atoi_u(&map->line[map->tr.i], number);
	map->tr.i += res;
	while (ft_isdigit(map->line[map->tr.i]))
		map->tr.i++;
	if (res == 0 || !ft_strchr(separators, map->line[map->tr.i]))
		throw_parse_error(ERR_MISSING_SYMBOL, &map->line[map->tr.i]);
}

void	check_number(unsigned int num, long long min, long long max)
{
	if (num < min || num > max)
		throw_parse_error(ERR_OUT_OF_BOUND, 0);
}

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

void	check_duplicate(char *texture, char *ptr)
{
	if (texture != NULL)
		throw_parse_error(ERR_DUPLICATE_SPEC, ptr);
}

// void	parse_music(t_map *map, char **path, char *name, char *ext)
// {
// 	map->tr.i = 0;

// 	check_duplicate(*path, map->line);
// 	while (map->tr.i < ft_strlen(name))
// 		check_and_skip(map, name[map->tr.i]);
// 	check_symbol(map, ' ');
// 	skip_symbol(map, ' ');
// 	check_file_path(map, ext);
// 	*path = ft_strdup(&map->line[map->tr.i]);
// 	print_status("Texture", name, "OK");
// }

void check_anim_dir(t_map *map)
{
	int i;
	int fd;
	int len;
	char *path;

	i = 0;
	path = ft_strjoin(&map->line[map->tr.i], "/0.xpm");
	len  = ft_strlen(path);
	while (i < ANIM_FRAMES)
	{
		path[len - 5] = '0' + i;
		if ((fd = open(path, O_RDONLY)) < 0)
			throw_parse_error(ERR_NO_FILE, path);
		else
			close(fd);
		i++;
	}
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

void	print_status(char *title, char *name, char *status)
{
	write(1, title, ft_strlen(title));
	if (name)
		write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, ": ", 2);
	write(1, "[", 1);
	write(1, status, ft_strlen(status));
	write(1, "]\n", 2);
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

void	parse_identify_line_bonus(t_map *map)
{
	if (!ft_strncmp(map->line, "SK", 2))
		parse_path(map, &map->SK_path, "SK", ".xpm");
	else if (!ft_strncmp(map->line, "WP", 2))
		parse_wpath(map, &map->WP_path, "WP", ".anim");
	else if (!ft_strncmp(map->line, "FT", 2))
		parse_path(map, &map->FT_path, "FT", ".xpm");
	else if (!ft_strncmp(map->line, "AS", 2))
		parse_path(map, &map->AS_path, "AS", ".xpm");
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
		parse_path(map, &map->NO_path, "NO", ".xpm");
	else if (!ft_strncmp(map->line, "SO", 2))
		parse_path(map, &map->SO_path, "SO", ".xpm");
	else if (!ft_strncmp(map->line, "WE", 2))
		parse_path(map, &map->WE_path, "WE", ".xpm");
	else if (!ft_strncmp(map->line, "EA", 2))
		parse_path(map, &map->EA_path, "EA", ".xpm");
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

int		map_getline(t_map *map)
{
	int res;

	if ((res = get_next_line(map->fd, &map->line)) < 0)
		throw_parse_error(ERR_GET_NEXT_LINE, 0);
	return (res);
}

int		is_prm_complete(t_map *map)
{
	int res;

	res = 1;
	if (map->w == 0 || map->h == 0)
		res = 0;
	if (map->SO_path == 0 || map->NO_path == 0)
		res = 0;
	if (map->WE_path == 0 || map->EA_path == 0)
		res = 0;
	if (map->c.set == 0 || map->f.set == 0)
		res = 0;
	if (map->sprite == 0)
		res = 0;
	if (map->bonus)
	{
		if (map->WP_path == 0 || map->SK_path == 0)
			res = 0;
		if (map->FT_path == 0 || map->AS_path == 0)
			res = 0;
		if (map->sound == 0 || map->music == 0 || map->wsound == 0)
			res = 0;
	}
	return (res);
}

void	map_add_node(t_list **head, char *line)
{
	size_t		i;
	size_t		line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (ft_strchr(ALLOWED_MAP_SPEC, line[i++]) == NULL)
		{
			ft_lstclear(head, free);
			throw_parse_error(ERR_MISSING_SYMBOL, line);
		}
	}
	ft_lstadd_back(head, ft_lstnew(ft_strdup(line)));
}

void	skip_empty_lines(t_map *map)
{
	int	res;
	
	res = 1;
	while ((res = map_getline(map)) > 0 && map->line[0] == '\0')
	{
		map->tr.line++;
		free(map->line);
	}
	map->tr.line++;
	if (res == 0)
	{
		free(map->line);
		throw_parse_error(ERR_MAP_MISSING, 0);
	}
}

int		map_to_list(t_map *map)
{
	int	res;

	res = 1;
	skip_empty_lines(map);
	while (res)
	{
		map_add_node(&map->lst, map->line);
		free(map->line);
		res = map_getline(map);
		if (map->line[0] == '\0')
			throw_parse_error(ERR_MISSING_SYMBOL, "Empty line in map");
	}
	map_add_node(&map->lst, map->line);
	free(map->line);
	map->rows = ft_lstsize(map->lst) + 2;
	map->cols = ft_lstmax_cont_len(map->lst);
	return (0);
}
