/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 23:42:24 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	skip_symbol(char **str, char c)
{
	while (**str == c)
		(*str)++;
}

int		ft_atoui(char **str, unsigned int *number)
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
    return (s[i] == '\0' || s[i] == ' ' || i == R_MAX_LEN ? i : -1);
}

int		get_number(char **str, unsigned int *number)
{
	int res;
	
	if ((res = ft_atoui(str, number)) == -1)
	{
		if (**str == '-')
			print_error("Map error", "Resolution value is negative", 0);
		else
			print_error("Map error", "Invalid resolution value", *str);
		exit(1);
	}
	return (res);
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

int		check_symbol(char **str, const char *example)
{
	if (ft_strcmp(*str, example) == 0)
	{
		print_error("Map error", "Invalid symbol in map line", *str);
		exit(1);
	}
	(*str)++;
	return (0);
}

void	check_resolution(char **ptr, t_map *map)
{
	check_symbol(ptr, "R");

	skip_symbol(ptr, ' ');
	get_number(ptr, &map->r_width);

	check_symbol(ptr, " ");

	skip_symbol(ptr, ' ');
	get_number(ptr, &map->r_height);

	skip_symbol(ptr, ' ');
	if (**ptr != '\0')
		exit(1);
	//check_symbol(ptr, "\0");
	print_status("Resolution", "", "OK");
}

void check_texture(char *field, char **ptr, char *name)
{
	size_t i;

	i = 0; 
	while (i < ft_strlen(name))
		skip_symbol(ptr, name[i++]);
	check_file(*ptr, ".xpm");
	field = *ptr;
	print_status("Texture", name, "OK");
}

void	check_color(t_map *map, char *name)
{
	map->f[0] = 1;
	map->f[1] = 1;
	map->f[2] = 1;
	map->c[0] = 1;
	map->c[1] = 1;
	map->c[2] = 1;
	print_status("Color", name, "OK");
}

void	identify_line(char **ptr, t_map *map)
{
	if (!ft_strncmp(*ptr, "R ", 2))
		check_resolution(ptr, map);
	else if (!ft_strncmp(*ptr, "NO ", 3))
		check_texture(map->NO_texture, ptr, "NO");
	else if (!ft_strncmp(*ptr, "SO ", 3))
		check_texture(map->SO_texture, ptr, "SO");
	else if (!ft_strncmp(*ptr, "WE ", 3))
		check_texture(map->WE_texture, ptr, "WE");
	else if (!ft_strncmp(*ptr, "EA ", 3))
		check_texture(map->EA_texture, ptr, "EA");
	else if (!ft_strncmp(*ptr, "S ", 2))
		check_texture(map->sprite, ptr, "S");
	else if (!ft_strncmp(*ptr, "F ", 2))
		check_color(map, "F");
	else if (!ft_strncmp(*ptr, "C ", 2))
		check_color(map, "C");
	else
		print_error("Map error", "Identificator not found", *ptr);
}

int	get_map_line(int fd, char **tmp)
{
	if (get_next_line(fd, tmp) < 0)
	{
		print_error("Internal error", "get_next_line caused crash", 0);
		exit(1);
	}
	return (0);
}

int	check_entirety(t_map *map)
{
	int res;

	res = 1;
	if (map->r_width == 0 || map->r_height == 0)
		res = 0; 
	if (map->SO_texture == 0 || map->NO_texture == 0)
		res = 0;
	if (map->WE_texture == 0 || map->EA_texture == 0)
		res = 0;
	if (map->sprite == 0)
		res = 0;
	if (map->c_color_set == 0 || map->f_color_set == 0)
		res = 0;
	return (res);
}

int	check_map(char *file, t_map *map)
{
	int		fd;
	char	*tmp;

	fd = open(file, O_RDWR);
	while (!check_entirety(map))
	{
		get_map_line(fd, &tmp);
		skip_symbol(&tmp, ' ');
		identify_line(&tmp, map);
		free(tmp);
	}
	close(fd);
	return (0);
}