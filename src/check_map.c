/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/15 06:21:12 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	skip_symbol(char **str, char c)
{
	while (**str == c)
		(*str)++;
}

int		ft_atoui(char **str, int *number)
{
	char *s;
	int i;

	i = 0;
	s = *str;
    *number = 0;
	while (ft_isdigit(s[i]) && i < R_MAX_LEN)
	{
		*number = *number * 10 + (s[i++] - '0');
    }
	*str = &s[i];
    return (s[i] == '\0' || s[i] == ' ' || s[i] == ',' || i == R_MAX_LEN ? i : -1);
}

void	get_number(char **str, int *number)
{
	if (ft_atoui(str, number) == -1)
	{
		if (**str == '-')
			throw_error(MAP_ERROR, ERR_NEGATIVE_VALUE, *str);
		else
			throw_error(MAP_ERROR, ERR_INVALID_SYMBOL, *str);
	}
}

void	print_status(char *title, char *name, char *status)
{
	write(1, title, ft_strlen(title));
	write(1, " ", 1);
	write(1, name, ft_strlen(name));
	write(1, ": ", 2);
	write(1, "[", 1);
	write(1, status, ft_strlen(status));
	write(1, "]\n", 2);
}

void	check_symbol(char *str, const char c)
{
	if (*str != '\0' && *str != c)
		throw_error(MAP_ERROR, ERR_INVALID_SYMBOL, str);
}

int		inc_line_number(int add)
{
	static int line;

	line += add;
	return (line);
}

void	check_number(unsigned int num, long long min, long long max)
{
	if (num < min || num > max)
		throw_error(MAP_ERROR, ERR_OUT_OF_BOUND, 0);
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
	print_status("Resolution", "", "OK");
}

void	check_duplicate(char *texture_path, char *ptr)
{
	if (texture_path != 0)
		throw_error(MAP_ERROR, ERR_DUPLICATE_SPEC, ptr);
	//{
		//print_error("Map error", "Texture specifier duplicated", ptr);
		//exit(1);
	//}
}

void	parse_path(char **field, char *ptr, char *name)
{
	char	**copy;
	size_t	i;

	i = 0;
	copy = &ptr;
	while (i < ft_strlen(name))
		skip_symbol(copy, name[i++]);
	check_symbol(*copy, ' ');
	skip_symbol(copy, ' ');
	check_file_path(*copy, ".xpm");
	check_duplicate(*field, *copy);
	*field = ft_strdup(*copy);
	print_status("Texture", name, "OK");
}

void	parse_color(t_map *map, char *line, char *name)
{
	char	**copy;
	int		*color;

	copy = &line;
	color = *name == 'F' ? map->f : map->c;
	skip_symbol(copy, *name);
	check_symbol(*copy, ' ');
	skip_symbol(copy, ' ');
	get_number(copy, &color[0]);
	skip_symbol(copy, ' ');
	check_symbol(*copy, ',');
	skip_symbol(copy, ',');
	skip_symbol(copy, ' ');
	get_number(copy, &color[1]);
	skip_symbol(copy, ' ');
	check_symbol(*copy, ',');
	skip_symbol(copy, ',');
	skip_symbol(copy, ' ');
	get_number(copy, &color[2]);
	check_symbol(*copy, '\0');
	
	map->f_set = (*name == 'F') ? 1 : map->f_set;
	map->c_set = (*name == 'C') ? 1 : map->c_set;
	print_status("Color", name, "OK");
}

void	identify_line(char *line, t_map *map)
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
		throw_error(MAP_ERROR, ERR_ID_NOT_FOUND, line);
	}
}

int		get_map_line(int fd, char **line)
{
	if (get_next_line(fd, line) < 0)
		throw_error(INTERNAL_ERROR, ERR_GNL, 0);

	return (0);
}

int		check_entirety(t_map *map)
{
	int res;

	res = 1;
	if (map->r_width == -1 || map->r_height == -1)
		res = 0; 
	if (map->SO_path == 0 || map->NO_path == 0)
		res = 0;
	if (map->WE_path == 0 || map->EA_path == 0)
		res = 0;
	if (map->sprite == 0)
		res = 0;
	if (map->c_set == 0 || map->f_set == 0)
		res = 0;
	return (res);
}

int		check_map(t_map *map)
{
	(void) map;
	return (0);
}

void	print_all_params(t_map *map)
{
	printf("\nRECEIVED:\n");
	printf("width:%d\n", map->r_width);
	printf("height:%d\n", map->r_height);
	printf("NO:%s\n", map->NO_path);
	printf("SO:%s\n", map->SO_path);
	printf("WE:%s\n", map->WE_path);
	printf("EA:%s\n", map->EA_path);
	printf("S:%s\n", map->sprite);
	printf("F:%d %d %d\n", map->c[0], map->c[1], map->c[2]);
	printf("C:%d %d %d\n", map->f[0], map->f[1], map->f[2]);
}

int		parse_scene_file(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDWR);
	while (!check_entirety(map))
	{
		inc_line_number(1);
		get_map_line(fd, &line);
		if (ft_strcmp(line, "\0"))
			identify_line(line, map);
		free(line);
	}
	print_all_params(map);
	check_map(map);
	close(fd);
	return (0);
}
