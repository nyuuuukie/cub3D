/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:34:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 07:04:26 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_error_msg(t_error code)
{
	static char *errors[22];

	errors[ERR_ARG_NUM] = "Invalid number of arguments";
	errors[ERR_INVALID_ARG] = "Invalid argument";
	errors[ERR_WRONG_EXT] = "Wrong file extension";
	errors[ERR_NO_FILE] = "File cannot be opened";
	errors[ERR_NO_FILENAME] = "Filename is missing";
	errors[ERR_OUT_OF_BOUND] = "Value out of bounds";
	errors[ERR_ZERO_BEFORE_NUM] = "Zero(s) before number";
	errors[ERR_DUPLICATE_SPEC] = "Specifier duplicated";
	errors[ERR_NEGATIVE_VALUE] = "Negative value";
	errors[ERR_ID_NOT_FOUND] = "Identifier not found";
	errors[ERR_MAP_MISSING] = "Map is missing";
	errors[ERR_GET_NEXT_LINE] = "Get_next_line caused crash";
	errors[ERR_CANNOT_ALLOC] = "Malloc cannot allocate required memory";
	errors[ERR_MAP_NOT_CLOSED] = "Player can go outside the map";
	errors[ERR_PLAYER_NOT_FOUND] = "Player not found";
	errors[ERR_TOO_MANY_PLAYERS] = "Too many players";
	errors[ERR_MISSING_SYMBOL] = "Missing symbol or symbol is invalid";
	errors[ERR_MLX_TXT_FAIL] = "Cannot load texture";
	errors[ERR_MLX_WIN_FAIL] = "Cannot create window";
	errors[ERR_MLX_IMG_FAIL] = "Cannot create screen image";
	errors[ERR_SOUNDLIB_INIT] = "Cannot init sound library";
	errors[ERR_SOUNDLIB_LOAD] = "Cannot load sound file";
	return (errors[code]);
}

void	throw_parse_error(t_error msg, char *add)
{
	t_map	*map;

	map = get_map(0);
	print_error(get_error_msg(msg), &map->tr, add);
	free_map(map);
	exit(1);
}

void	throw_engine_error(t_all *all, t_error msg, char *add)
{
	print_error(get_error_msg(msg), 0, add);
	stop_engine(all);
	exit(1);
}

void	print_error(char *msg, t_track *track, char *add)
{
	ft_putstr_fd("Error\n", 2);
	if (track && track->line != 0)
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
