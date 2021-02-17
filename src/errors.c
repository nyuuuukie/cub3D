/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:34:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/17 07:47:22 by mhufflep         ###   ########.fr       */
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
	errors[ERR_INVALID_SYMBOL] = "Invalid symbol";
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

void	throw_error(t_error msg, int line, char *add)
{
	if (msg == ERR_NO_FILE)
		print_error(strerror(errno), line, add);
	else
		print_error(get_error_msg(msg), line, add);
	errno = 0;
	exit(1);
}

void	print_error(char *msg, int line, char *add)
{
	write(2, "Error\n", 6);
	write(2, "[", 1);
	if (line != 0)
	{
		write(2, "Line ", 5);
		ft_putnbr_fd(line, 2);
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "]", 1);
	if (add != NULL)
	{
		write(2, "\n>> \"", 5);
		write(2, add, ft_strlen(add));
		write(2, "\"", 1);
	}
	write(2, "\n", 1);
}
