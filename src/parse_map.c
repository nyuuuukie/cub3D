/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/19 21:53:59 by mhufflep         ###   ########.fr       */
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
		throw_error(ERR_MISSING_SYMBOL, &map->line[map->tr.i]);
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
		throw_error(ERR_ZERO_BEFORE_NUM, &map->line[map->tr.i]);
	res = ft_atoi_u(&map->line[map->tr.i], number);
	map->tr.i += res;
	while (ft_isdigit(map->line[map->tr.i]))
		map->tr.i++;
	if (res == 0 || !ft_strchr(separators, map->line[map->tr.i]))
		throw_error(ERR_MISSING_SYMBOL, &map->line[map->tr.i]);
}

void	check_number(unsigned int num, long long min, long long max)
{
	if (num < min || num > max)
		throw_error(ERR_OUT_OF_BOUND, 0);
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
		throw_error(ERR_DUPLICATE_SPEC, ptr);
}

void	parse_path(t_map *map, char **texture, char *name)
{
	map->tr.i = 0;
	check_duplicate(*texture, map->line);
	while (map->tr.i < ft_strlen(name))
		check_and_skip(map, name[map->tr.i]);
	check_symbol(map, ' ');
	skip_symbol(map, ' ');
	check_file_path(map, ".xpm");
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

void	parse_identify_line(t_map *map)
{
	if (!ft_strncmp(map->line, "R", 1))
		parse_resolution(map);
	else if (!ft_strncmp(map->line, "NO", 2))
		parse_path(map, &map->NO_path, "NO");
	else if (!ft_strncmp(map->line, "SO", 2))
		parse_path(map, &map->SO_path, "SO");
	else if (!ft_strncmp(map->line, "WE", 2))
		parse_path(map, &map->WE_path, "WE");
	else if (!ft_strncmp(map->line, "EA", 2))
		parse_path(map, &map->EA_path, "EA");
	else if (!ft_strncmp(map->line, "S", 1))
		parse_path(map, &map->sprite, "S");
	else if (!ft_strncmp(map->line, "F", 1))
		parse_color(map, &map->f, "F");
	else if (!ft_strncmp(map->line, "C", 1))
		parse_color(map, &map->c, "C");
	else
		throw_error(ERR_ID_NOT_FOUND, 0);
}

int		map_getline(t_map *map)
{
	int res;

	if ((res = get_next_line(map->fd, &map->line)) < 0)
		throw_error(ERR_GET_NEXT_LINE, 0);

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
			throw_error(ERR_MISSING_SYMBOL, line);
		}
	}
	ft_lstadd_back(head, ft_lstnew(ft_strdup(line)));
}

int		is_empty(char *str)
{
	// int i;

	// i = 0;
	// while (str[i] == ' ')
	// {
	// 	i++;
	// }
	return (!str || *str == '\0');
}

void	skip_empty_lines(t_map *map)
{
	int	res;
	
	res = 1;
	while ((res = map_getline(map)) > 0 && is_empty(map->line))
	{
		map->tr.line++;
		free(map->line);
	}
	map->tr.line++;
	if (res == 0)
	{
		free(map->line);
		throw_error(ERR_MAP_MISSING, 0);
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
	}
	map_add_node(&map->lst, map->line);
	free(map->line);
	map->rows = ft_lstsize(map->lst) + 2;
	map->cols = ft_lstmax_cont_len(map->lst);
	return (0);
}
