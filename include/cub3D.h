/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/18 23:53:05 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* standard headers */
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# define _USE_MATH_DEFINES

////HERE
//# define BONUS

//#ifdef BONUS
//# include <time.h>
//#endif

# include "mlx.h"
# include "libft.h"
# include "error.h"
# include "events.h"
# include "keycodes.h"
# include "settings.h"
# include "structures.h"

/* Check input arguments */
int		check_save_arg(int argc, char **argv);
int		check_extension(t_map *map, const char *ext);
int		check_file_path(t_map *map, char *ext);

/* Check scene file */
void	parse_scene_file(t_map *prm, char *path);
int		parse_prm(t_map *map);
int		parse_map(t_map *map);
int		map_to_list(t_map *map);
void	map_validate(t_map *map);
int		map_getline(t_map *map);
void	parse_identify_line(t_map *map);
int		is_prm_complete(t_map *map);

void	print_status(char *title, char *name, char *status);

/* Errors.c */
char*	get_error_msg(t_error code);
void	throw_error(t_error msg, char *add);
void	print_error(char *msg, t_track *track, char *add);

/* get_next_line */
int		get_next_line(int fd, char **line);

/* arrays.c */
void	arr_delete(char **arr);
void	arr_fill(char **arr, t_list *lst);
void	arr_create(char ***arr, int rows, int cols);
int		arr_replace(char **arr, char to_replace, char replacer);

/* map.c */
void	free_map(t_map *map);
void	set_defaults(t_map *map);
t_map	*get_map(t_map *map);

/* flood fill */
int		flood_fill(char **arr, int x, int y);
void	flood_fill_iter(char **arr, int x, int y);
void	player_check(int count, int row, int col);

/* engine.c */
int 	start_engine(t_map *map, int mode);
int		stop_engine(void *ptr);

/* raycasting.c */
void	start_main_loop(t_all *all);
void    draw_walls(t_all *all);
int		render(t_all *all);

void	init_all(t_all *all);
void	init_coord(t_all *all);

/* init.c */
void	init_window(t_all *all);
void	init_textures(t_all *all);
void	init_screen_size(t_all *all);
void	init_img(t_all *all, t_img *img);
void	init_vectors(t_all *all, int i, int j);
void	init_texture(void *mlx, char *path, t_texture *t);

void	init_shadow_params(t_all *all);



/* vector.c */
void    vector_init(t_vector *vect, double x, double y);
void	vector_int_init(t_v_int *vect, int x, int y);
double  vector_mlp(t_vector *v1, t_vector *v2);
double  vector_len(t_vector *v);
double  vector_angle(t_vector *v1, t_vector *v2);
void	vector_rotate(t_vector *v, double angle);

/* key_action.c */
void	init_keys(t_all* all);
int		key_action(t_all *all);
int		key_release(int keycode, t_all *all);
int		key_press(int keycode, t_all *all);

/* engine_move.c */
void	rotate(t_all *all, int sign);
void	move(t_all *all, t_vector *base, int sign);

/* colors.c */
//int		color_trgb(int t, int r, int g, int b);
//int		color_get_t(int trgb);
//int		color_get_r(int trgb);
//int		color_get_g(int trgb);
//int		color_get_b(int trgb);
int		color_make_lighter(double perc, int color);
int		color_make_darker(double perc, int color);
int		color_from_img(t_img *img, int x, int y);
int		color_negative(int color);
int		color_from_prm(t_clr *clr);


/* angle_radian.c */
double	get_radian(double angle);
double	get_angle(double radian);


void make_screenshot(t_all *all);

#endif