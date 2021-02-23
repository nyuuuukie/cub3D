/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:40:31 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/23 00:49:26 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

typedef enum	e_err_msg {
	ERR_ARG_NUM = 0,
	ERR_WRONG_EXT = 1,
	ERR_NO_FILE = 2,
	ERR_NO_FILENAME = 3,
	ERR_OUT_OF_BOUND = 4,
	ERR_ZERO_BEFORE_NUM = 5,
	ERR_DUPLICATE_SPEC = 6,
	ERR_NEGATIVE_VALUE = 7,
	ERR_ID_NOT_FOUND = 8, 
	ERR_MAP_MISSING = 9,
	ERR_GET_NEXT_LINE = 10,
	ERR_CANNOT_ALLOC = 11,
	ERR_MAP_NOT_CLOSED = 12,
	ERR_PLAYER_NOT_FOUND = 13,
	ERR_TOO_MANY_PLAYERS = 14,
	ERR_INVALID_ARG = 15,
	ERR_MISSING_SYMBOL = 16
}				t_error;

#endif