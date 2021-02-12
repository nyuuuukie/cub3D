/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 19:34:26 by mhufflep         ###   ########.fr       */
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

int		get_integer(char **str, unsigned int *number)
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

int		check_symbol(char **str, const char ex)
{
	if (**str != ex)
	{
		print_error("Map error", "Invalid map resolution line", *str);
		exit(1);
	}
	(*str)++;
	return (0);
}

int		check_resolution(char **ptr, t_prm *prm)
{
	skip_symbol(ptr, ' ');
	check_symbol(ptr, 'R');

	skip_symbol(ptr, ' ');
	get_integer(ptr, &prm->r_width);

	check_symbol(ptr, ' ');

	skip_symbol(ptr, ' ');
	get_integer(ptr, &prm->r_height);

	skip_symbol(ptr, ' ');
	check_symbol(ptr, '\0'); 

	return (0);
}

int	check_textures_abbr(char **ptr, int len)
{
	int res;

	res = 0;
	printf("ptr:%s\n", *ptr);
	if (ft_strncmp(*ptr, "NO", len - 1))
		res = -1;
	else if (ft_strncmp(*ptr, "SO", len))
		res = -1;
	else if (ft_strncmp(*ptr, "WE", len))
		res = -1;
	else if (ft_strncmp(*ptr, "EA", len))
		res = -1;
	*ptr += len;
	return (res);
}

int check_textures(char **ptr, t_prm *prm)
{
	(void)prm;

	skip_symbol(ptr, ' ');
	if (check_textures_abbr(ptr, 2))
	{
		print_error("Map error", "Invalid abbreviation of texture", 0);
		return (-1);
	}

	skip_symbol(ptr, ' ');
	if (check_file(*ptr, ".xpm"))
	{
		return (-1);
	}
	return (0);
}

int	check_map(char *map, t_prm *prm)
{
	int		fd;
	char	*tmp;

	fd = open(map, O_RDWR);
	if (get_next_line(fd, &tmp) < 0)
	{
		print_error("Internal error", "get_next_line caused crash", 0);
		return (-1);
	}
	printf("%s\n", tmp);

	if (check_resolution(&tmp, prm))
		return (-1);
	
	printf("w:%u\n", prm->r_width);
	printf("h:%u\n", prm->r_height);

	if (get_next_line(fd, &tmp) < 0)
	{
		print_error("Internal error", "get_next_line caused crash", 0);
		return (-1);
	}
	
	if (check_textures(&tmp, prm) != -1)
	{
		printf("textures check done!\n");
	}
	close(fd);
	return (0);
}