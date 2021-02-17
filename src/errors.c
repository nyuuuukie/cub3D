/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:34:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/17 20:01:22 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_error_msg(t_error code)
{
	static char *errors[16];

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
	errors[ERR_MAP_NOT_CLOSED] = "Map is not closed";
	errors[ERR_PLAYER_NOT_FOUND] = "Player not found";
	errors[ERR_TOO_MANY_PLAYERS] = "Too many players";
	code = (code < 1 && code > 10) ? 0 : code;
	return (errors[code]);
}

void	free_map(t_map *map)
{
	map->lst ? ft_lstclear(&map->lst, free) : NULL;
	map->arr ? delete_arr(map->arr) : NULL;
	map->sprite ? free(map->sprite) : NULL;
	map->NO_path ? free(map->NO_path) : NULL;
	map->SO_path ? free(map->SO_path) : NULL;
	map->WE_path ? free(map->WE_path) : NULL;
	map->EA_path ? free(map->EA_path) : NULL;
}

t_map	*get_map(t_map *map)
{
	static t_map *ptr;

	if (ptr == NULL)
		ptr = map;
	return (ptr);
}

void	throw_error(t_error msg, int line, char *add)
{
	if (msg == ERR_NO_FILE)
		print_error(strerror(errno), line, add);
	else
		print_error(get_error_msg(msg), line, add);
	errno = 0;
	free_map(get_map(0));
	exit(1);
}

void	print_error(char *msg, int line, char *add)
{
	if (LOGS_FD > 2 && write(LOGS_FD, "1", 0) < 0)
		return ;
	ft_putstr_fd("Error\n[", LOGS_FD);
	if (line != 0)
	{
		ft_putstr_fd("Line ", LOGS_FD);
		ft_putnbr_fd(line, LOGS_FD);
		ft_putstr_fd(": ", LOGS_FD);
	}
	ft_putstr_fd(msg, LOGS_FD);
	ft_putstr_fd("]", LOGS_FD);
	if (add != 0)
	{
		ft_putstr_fd("\n>> \"", LOGS_FD);
		ft_putstr_fd(add, LOGS_FD);
		ft_putstr_fd("\"", LOGS_FD);
	}
	ft_putstr_fd("\n", LOGS_FD);
}
