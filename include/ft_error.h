/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:40:31 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/15 05:51:29 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

typedef enum	e_err_ttl {
	ARGUMENT_ERROR = 0,
	FILE_ERROR = 1,
	MAP_ERROR = 2,
	INTERNAL_ERROR = 3
}				t_err_ttl;

typedef enum	e_err_msg {
	ERR_ARG_NUM = 0,
	ERR_WRONG_EXT = 1,
	ERR_NO_FILE = 2,
	ERR_NO_FILENAME = 3,
	ERR_OUT_OF_BOUND = 4,
	ERR_INVALID_SYMBOL = 5,
	ERR_DUPLICATE_SPEC = 6,
	ERR_NEGATIVE_VALUE = 7,
	ERR_ID_NOT_FOUND = 8, 
	ERR_GNL = 9
}				t_err_msg;

#endif