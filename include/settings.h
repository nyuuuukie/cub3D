/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:23:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/26 21:19:25 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SETTINGS
# define FT_SETTINGS

#ifdef BONUS
    // #define CEIL
    #define SKY
    #define MUSIC
    #define FLOOR
#endif

# define START_CUB3D 1
# define MAKE_SCREENSHOT 2

# define SCALE 6

/* Resolution */
# define R_MAX_LEN 6
# define R_MIN_WIDTH 10
# define R_MAX_WIDTH 1000000
# define R_MIN_HEIGHT 10
# define R_MAX_HEIGHT 1000000

/* Colors */
# define COLOR_MIN_VALUE 0
# define COLOR_MAX_VALUE 255

# define MIN_R 15
# define MIN_G 15
# define MIN_B 15
# define MAX_R 240
# define MAX_G 240
# define MAX_B 240

/* File */
# define EXTENSION_LEN 5

/* Map */
#ifndef BONUS
	# define ALLOWED_MAP_SPEC "012NSWE "
	# define FLOOD_FILL_SPEC "02NSWE"
	# define SPRITES "2"
#else
	# define ALLOWED_MAP_SPEC "0123NSWE "
	# define FLOOD_FILL_SPEC "023NSWE"
	# define SPRITES "23"
#endif

#ifndef LINUX
	# define S_VOLUME "-f 10000"
	# define M_VOLUME "-f 5000"
#else
	# define S_VOLUME "-g 80"
	# define M_VOLUME "-g 40"
#endif

#endif