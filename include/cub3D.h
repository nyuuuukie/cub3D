/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/08 22:56:24 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_base.h"
# include "ft_map.h"
# include "ft_settings.h"
# include "ft_error.h"
# include "ft_keycodes.h"

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

/* Print error */
void	print_error(char *msg, t_track *track, char *add);

/* Errors.c */
char*	get_error_msg(t_error code);
void	throw_error(t_error msg, char *add);

/* get_next_line */
int		get_next_line(int fd, char **line);

/* arrays.c */

void	arr_delete(char **arr);
void	arr_fill(char **arr, t_list *lst);
void	arr_create(char ***arr, int rows, int cols);
void	arr_replace(char **arr, char to_replace, char replacer);

/* map.c */
void	free_map(t_map *map);
void	set_defaults(t_map *map);
t_map	*get_map(t_map *map);


/* Flood fill */
int		flood_fill(char **arr, int x, int y);
void	flood_fill_iter(char **arr, int x, int y);
void	player_check(int count, int row, int col);


/* raycasting.c */
void	init_raycast(t_map *map);
void    raycasting(t_all *all);
void	setup_textures(t_all *all);

/* vector.c */
void    vector_init(t_vector *vect, double x, double y);
double  vector_mlp(t_vector *v1, t_vector *v2);
double  vector_len(t_vector *v);
double  vector_angle(t_vector *v1, t_vector *v2);


void	arr_print(char **arr); //HELPER
#endif