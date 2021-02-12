/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:25:56 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 14:46:01 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		skip_symbol(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] == c)
		i++;
	return (i);
}

int ft_atoui(char *s, unsigned int *number)
{
	int i;

	i = 0;
    *number = 0;
	while (ft_isdigit(s[i]) && i < PARSE_R_MAX_LEN)
	{
		*number = *number * 10 + (s[i++] - '0');
    }
    return (s[i] == '\0' || s[i] == ' ' || i == PARSE_R_MAX_LEN ? i : -1);
}

int check_resolution(char *str, t_prm *prm)
{
	int i;
	int res;

	i = 0;
	if (str)
	{
		i += skip_symbol(&str[i], ' ');
		if (str[i++] != 'R')
		{
			print_error("Map error", "Resolution was not found", 0);			
			return (-1);
		}
		
		i += skip_symbol(&str[i], ' ');
		if ((res = ft_atoui(&str[i], &prm->r_width)) == -1)
		{
			if (str[i] == '-')
				print_error("Map error", "Screen width value is negative", 0);
			else
				print_error("Map error", "Invalid screen width value", 0);
			return (-1);
		}
		i += res;
		
		if (str[i] != ' ')
		{
			if (ft_isdigit(str[i]))
				print_error("Map error", "Resolution has only one parameter", 0);
			else if (str[i] == '-')
				print_error("Map error", "Screen height value is negative", 0);
			else
				print_error("Map error", "Invalid symbols in map resolution", 0);
			return (-1);
		}	

		i += skip_symbol(&str[i], ' ');
		if (ft_atoui(&str[i], &prm->r_height) == -1)
		{
			print_error("Map error", "Invalid screen height value", 0);
			return (-1);
		}
	}
	return ((str == NULL) * -1);
}

int	check_map(char *map, t_prm *prm)
{
	int		fd;
	int		code;
	char	*tmp;

	fd = open(map, O_RDWR);
	code = get_next_line(fd, &tmp);
	if (code < 0)
	{
		print_error("Internal error", "get_next_line caused crash", 0);
		return (-1);
	}
	printf("%s\n", tmp);
	// if parameter is only one
	if (check_resolution(tmp, prm) != -1)
	{
		printf("w:%u\n", prm->r_width);
		printf("h:%u\n", prm->r_height);
	}
	return (0);
}