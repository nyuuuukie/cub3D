/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 07:23:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/22 15:15:00 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SETTINGS
# define FT_SETTINGS

#ifdef BONUS
    #define RAIN
    // #define CEIL
    #define SKY
    #define MUSIC
    #define FLOOR
    #define WEAPON
#endif

//#define CEIL

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
# define ALLOWED_MAP_SPEC "012NSWE "

#define S_VOLUME "-f 15000"
#define M_VOLUME "-f 5000"

#endif