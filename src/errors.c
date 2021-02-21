/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:34:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/21 09:43:25 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_error_msg(t_error code)
{
	static char *errors[17];

	errors[ERR_ARG_NUM] = "Invalid number of arguments";
	errors[ERR_INVALID_ARG] = "Invalid argument";
	errors[ERR_WRONG_EXT] = "Wrong file extension";
	errors[ERR_NO_FILE] = "No such file or directory";
	errors[ERR_NO_FILENAME] = "Filename is missing";
	errors[ERR_OUT_OF_BOUND] = "Value out of bounds";
	errors[ERR_INVALID_SYMBOL] = "Invalid symbol in line";
	errors[ERR_DUPLICATE_SPEC] = "Specifier duplicated";
	errors[ERR_NEGATIVE_VALUE] = "Negative value";
	errors[ERR_ID_NOT_FOUND] = "Identifier not found";
	errors[ERR_MAP_MISSING] = "Map is missing";
	errors[ERR_GNL] = "Get_next_line caused crash";
	errors[ERR_CANNOT_ALLOC] = "Malloc cannot allocate required memory";
	errors[ERR_MAP_NOT_CLOSED] = "Player can go outside the map";
	errors[ERR_PLAYER_NOT_FOUND] = "Player not found";
	errors[ERR_TOO_MANY_PLAYERS] = "Too many players";
	errors[ERR_MISSING_SYMBOL] = "Missing symbol or symbol is invalid";
	code = (code < 1 && code > 10) ? 0 : code;
	return (errors[code]);
}

void	free_map(t_map *map)
{
	// map->line ? free(map->line) : NULL;
	map->sprite ? free(map->sprite) : NULL;
	map->NO_path ? free(map->NO_path) : NULL;
	map->SO_path ? free(map->SO_path) : NULL;
	map->WE_path ? free(map->WE_path) : NULL;
	map->EA_path ? free(map->EA_path) : NULL;
	map->arr ? arr_delete(map->arr) : NULL;
	map->lst ? ft_lstclear(&map->lst, free) : NULL;
}

t_map	*get_map(t_map *map)
{
	static t_map	*ptr;

	if (ptr == NULL)
		ptr = map;
	return (ptr);
}

void	throw_error(t_error msg, int line, char *add)
{
	t_map	*map;

	map = get_map(0);
	map->tr.line += line;
	// if (msg == ERR_NO_FILE)
	// 	print_error(strerror(errno), &map->tr, add);
	// else
		print_error(get_error_msg(msg), &map->tr, add);
	errno = 0;
	free_map(get_map(0));
	exit(1);
}

void	print_error(char *msg, t_track *track, char *add)
{
	ft_putstr_fd("Error\n", 2);
	if (track->line != 0)
	{
		ft_putstr_fd("Line [", 2);
		ft_putnbr_fd(track->line, 2);
		ft_putstr_fd(":", 2);
		ft_putnbr_fd(track->i, 2);
		ft_putstr_fd("]: ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (add != 0)
	{
		ft_putstr_fd("\n>> \"", 2);
		ft_putstr_fd(add, 2);
		ft_putstr_fd("\"", 2);
	}
	ft_putstr_fd("\n", 2);
}
