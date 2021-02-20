/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/20 03:06:40 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//REMOVE
// void*	ft_print_list_node(void *content)
// {
// 	write(1, (char *)content, ft_strlen((char *)content));
// 	write(1, "\n", 1);
// 	return (NULL);
// }

//REMOVE
// void	print_all_params(t_map *map)
// {
// 	printf("\nRECEIVED:\n");
// 	printf("width:%d\n", map->r_width);
// 	printf("height:%d\n", map->r_height);
// 	printf("NO:%s\n", map->NO_path);
// 	printf("SO:%s\n", map->SO_path);
// 	printf("WE:%s\n", map->WE_path);
// 	printf("EA:%s\n", map->EA_path);
// 	printf("S:%s\n", map->sprite);
// 	printf("F:%d %d %d\n", map->c[0], map->c[1], map->c[2]);
// 	printf("C:%d %d %d\n", map->f[0], map->f[1], map->f[2]);

// 	printf("MAP:\n");
// 	ft_lstmap(map->lst, ft_print_list_node, free);

// 	printf("\nRows:%d\n", map->rows);
// }

//NEW FUCTIONS

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


int		check_and_skip(char *str, const char c)
{
	if (*str != c)
		throw_error(ERR_MISSING_SYMBOL, line_num(0), str);
	return (1);
}

int		is_allowed(char *str, const char c)
{
	if (*str != c)
		throw_error(ERR_MISSING_SYMBOL, line_num(0), str);
	return (1);
}

int		skip_symbol(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] == c)
		i++;
	return (i);
}

int		get_number(char *str, char *separators, int *number)
{
	int i;
	int res;

	i = 0;
	res = ft_atoi_u(str, number);
	if (res == 0 || !ft_strchr(separators, str[i + res]))
	{
		throw_error(ERR_MISSING_SYMBOL, line_num(0), *str);
	}
	return (i);
}

int		ft_atoui(char **str, int *number)
{
	char *s;
	int i;

	i = 0;
	s = *str;
    *number = 0;
	if (s[i] == '\0')
		return (-1);
	while (ft_isdigit(s[i]) && i < R_MAX_LEN)
	{
		*number = *number * 10 + (s[i++] - '0');
    }
	*str = &s[i];
    return (s[i] == '\0' || s[i] == ' ' || s[i] == ',' || i == R_MAX_LEN ? i : -1);
}

int		line_num(int add)
{
	static int line;

	line += add;
	return (line);
}

void	check_number(unsigned int num, long long min, long long max)
{
	if (num < min || num > max)
		throw_error(ERR_OUT_OF_BOUND, line_num(0), 0);
}

void	parse_resolution(char *ptr, t_map *map)
{
	int i;

	i = 0;
	i += check_and_skip(&ptr[i], 'R');
	i += check_and_skip(&ptr[i], ' ');
	i += get_number(&ptr[i], " ", &map->r_width);
	i += check_and_skip(&ptr[i], ' ');
	i += get_number(&ptr[i], " ", &map->r_height);
	check_symbol(&ptr[i], '\0');
	print_status("Resolution", 0, "OK");
}

void	parse_path(char **field, char *ptr, char *name)
{
	int	i;

	i = 0;
	if (*field != NULL)
		throw_error(ERR_DUPLICATE_SPEC, line_num(0), ptr);
	
	while (i < ft_strlen(name))
		i += check_and_skip(&ptr[i], name[i]);
	check_symbol(&ptr[i], ' ');
	i += skip_symbol(&ptr[i], ' ');
	check_file_path(&ptr[i], ".xpm");
	*field = ft_strdup(&ptr[i]);
	print_status("Texture", name, "OK");
}
//////////////

void	skip_symbol(char **str, char c)
{
	while (**str == c)
		(*str)++;
}

void	get_number(char **str, int *number)
{
	if (ft_atoui(str, number) == -1)
	{
		if (**str == '-')
			throw_error(ERR_NEGATIVE_VALUE, line_num(0), *str);
		else
			throw_error(ERR_MISSING_SYMBOL, line_num(0), *str);
	}
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

void	check_symbol(char *str, const char c)
{
	if (*str != c)
		throw_error(ERR_MISSING_SYMBOL, line_num(0), str);
}

int		line_num(int add)
{
	static int line;

	line += add;
	return (line);
}

void	check_number(unsigned int num, long long min, long long max)
{
	if (num < min || num > max)
		throw_error(ERR_OUT_OF_BOUND, line_num(0), 0);
}

void	parse_resolution(char *ptr, t_map *map)
{
	char **copy;

	copy = &ptr;
	check_symbol(*copy, 'R');
	skip_symbol(copy, 'R');
	check_symbol(*copy, ' ');
	skip_symbol(copy, ' ');
	get_number(copy, &map->r_width);
	check_number(map->r_width, R_MIN_WIDTH, R_MAX_WIDTH);
	check_symbol(*copy, ' ');
	skip_symbol(copy, ' ');
	get_number(copy, &map->r_height);
	check_number(map->r_height, R_MIN_HEIGHT, R_MAX_HEIGHT);
	check_symbol(*copy, '\0');
	print_status("Resolution", 0, "OK");
}

void	check_duplicate(char *texture_path, char *ptr)
{
	if (texture_path != NULL)
		throw_error(ERR_DUPLICATE_SPEC, line_num(0), ptr);
}

void	parse_path(char **field, char *ptr, char *name)
{
	char	**copy;
	int	i;

	i = 0;
	copy = &ptr;
	while (i < ft_strlen(name))
		skip_symbol(copy, name[i++]);
	check_symbol(*copy, ' ');
	skip_symbol(copy, ' ');
	check_duplicate(*field, *copy);
	check_file_path(*copy, ".xpm");
	*field = ft_strdup(*copy);
	print_status("Texture", name, "OK");
}

void	parse_color(t_map *map, char *line, char *name)
{
	char	**copy;
	int		*color;
	int		i;

	i = 0;
	copy = &line;
	color = *name == 'F' ? map->f : map->c;
	skip_symbol(copy, *name);
	check_symbol(*copy, ' ');
	while (i < 3)
	{
		skip_symbol(copy, ' ');
		get_number(copy, &color[i]);
		check_number(color[i], COLOR_MIN_VALUE, COLOR_MAX_VALUE);
		skip_symbol(copy, ' ');
		if (i != 2)
		{
			check_symbol(*copy, ',');
			skip_symbol(copy, ',');
		}
		i++;
	}
	check_symbol(*copy, '\0');
	map->f_set = (*name == 'F') ? 1 : map->f_set;
	map->c_set = (*name == 'C') ? 1 : map->c_set;
	print_status("Color", name, "OK");
}

void	parse_identify_line(char *line, t_map *map)
{
	if (!ft_strncmp(line, "R", 1))
		parse_resolution(line, map);
	else if (!ft_strncmp(line, "NO", 2))
		parse_path(&map->NO_path, line, "NO");
	else if (!ft_strncmp(line, "SO", 2))
		parse_path(&map->SO_path, line, "SO");
	else if (!ft_strncmp(line, "WE", 2))
		parse_path(&map->WE_path, line, "WE");
	else if (!ft_strncmp(line, "EA", 2))
		parse_path(&map->EA_path, line, "EA");
	else if (!ft_strncmp(line, "S", 1))
		parse_path(&map->sprite, line, "S");
	else if (!ft_strncmp(line, "F", 1))
		parse_color(map, line, "F");
	else if (!ft_strncmp(line, "C", 1))
		parse_color(map, line, "C");
	else
	{
		free(line);
		throw_error(ERR_ID_NOT_FOUND,  line_num(0), 0);
	}
}

int		parse_getline(int fd, char **line)
{
	int res;

	if ((res = get_next_line(fd, line)) < 0)
		throw_error(ERR_GNL, 0, 0);

	return (res);
}

int		is_prm_complete(t_map *map)
{
	int res;

	res = 1;
	if (map->r_width == -1 || map->r_height == -1)
		res = 0; 
	if (map->SO_path == 0 || map->NO_path == 0)
		res = 0;
	if (map->WE_path == 0 || map->EA_path == 0)
		res = 0;
	if (map->c_set == 0 || map->f_set == 0)
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
			throw_error(ERR_INVALID_SYMBOL, line_num(0), line);
		}
	}
	ft_lstadd_back(head, ft_lstnew(ft_strdup(line)));
	free(line);
	line = 0;
}

int		is_empty_line(char *str)
{
	if (!str || *str == '\0')
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

char*	skip_empty_lines(int fd)
{
	char	*line;
	int		res;
	
	res = 1;
	while ((res = parse_getline(fd, &line)) > 0 && is_empty_line(line))
	{
		line_num(1);
		free(line);
	}
	line_num(1);
	if (res == 0)
	{
		free(line);
		throw_error(ERR_MAP_MISSING, line_num(0), 0);
	}
	return (line);
}

int		parse_map_to_list(int fd, t_map *map)
{
	char	*line;
	int		res;

	res = 1;
	line = skip_empty_lines(fd);
	while (res)
	{
		map_add_node(&map->lst, line);
		res = parse_getline(fd, &line);
	}
	map_add_node(&map->lst, line);
	return (0);
}

