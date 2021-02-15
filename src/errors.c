/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:34:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/15 20:26:49 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_error_title(t_err_ttl code)
{
	static char *titles[10];

	titles[ARGUMENT_ERROR] = "Argument error";
	titles[FILE_ERROR] = "File error";
	titles[MAP_ERROR] = "Map error";
	titles[INTERNAL_ERROR] = "Internal error";
	code = (code < 1 && code > 9) ? 0 : code;
	return (titles[code]);
}

char	*get_error_msg(t_err_msg code)
{
	static char *errors[11];

	errors[ERR_ARG_NUM] = "Invalid number of arguments";
	errors[ERR_WRONG_EXT] = "Wrong file extension";
	errors[ERR_NO_FILE] = "No such file or directory";
	errors[ERR_NO_FILENAME] = "Filename is missing";
	errors[ERR_OUT_OF_BOUND] = "Value(s) out of bounds";
	errors[ERR_INVALID_SYMBOL] = "Invalid symbol";
	errors[ERR_DUPLICATE_SPEC] = "Specifier duplicated";
	errors[ERR_NEGATIVE_VALUE] = "Negative value";
	errors[ERR_ID_NOT_FOUND] = "Identifier not found";
	errors[ERR_MAP_MISSING] = "Map is missing";
	errors[ERR_GNL] = "get_next_line caused crash";
	code = (code < 1 && code > 10) ? 0 : code;
	return (errors[code]);
}

void	throw_error(t_err_ttl title, t_err_msg msg, char *add)
{
	if (msg == ERR_NO_FILE)
		print_error(get_error_title(title), strerror(errno), add);
	else
		print_error(get_error_title(title), get_error_msg(msg), add);
	errno = 0;
	exit(1);
}

void	print_error(char *title, char *msg, char *add)
{
	write(2, title, ft_strlen(title));
	write(2, " in line ", 9);
	ft_putnbr_fd(inc_line_number(0), 2);
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	if (add != NULL)
	{
		write(2, "\n=> \"", 5);
		write(2, add, ft_strlen(add));
		write(2, "\"", 1);
	}
	write(2, "\n", 1);
}
