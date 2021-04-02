/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:23:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:02:08 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# ifdef BONUS
#  define SKY
#  define MUSIC
#  define FLOOR
# endif

# define ANIM_FRAMES 6

# define R_MAX_LEN 6

/*
**Colors
*/
# define COLOR_MIN_VALUE 0
# define COLOR_MAX_VALUE 255
# define MIN_R 15
# define MIN_G 15
# define MIN_B 15
# define MAX_R 240
# define MAX_G 240
# define MAX_B 240

/*
**File
*/
# define EXTENSION_LEN 5
# define GNL_BUF_SIZE 10000000

/*
**Map
*/
# ifndef BONUS
#  define ALLOWED_MAP_SPEC "012NSWE "
#  define FLOOD_FILL_SPEC "02NSWE"
#  define SPRITES "2"
# else
#  define ALLOWED_MAP_SPEC "0123THNSWE "
#  define FLOOD_FILL_SPEC "023THNSWE"
#  define SPRITES "23TH"
# endif

# ifndef LINUX
#  define S_VOLUME "-f 10000"
#  define M_VOLUME "-f 5000"
# else
#  define S_VOLUME "-g 80"
#  define M_VOLUME "-g 40"
# endif

#endif
