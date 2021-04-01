/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:42:43 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 04:05:23 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef LINUX
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_P 112
#  define KEY_F 102
#  define KEY_K0 48
#  define KEY_K1 49
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_SHIFT 65505
# else
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_F 3
#  define KEY_P 35
#  define KEY_K0 29
#  define KEY_K1 18
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_SHIFT 257
# endif

#endif
