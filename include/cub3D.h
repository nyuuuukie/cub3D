/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/21 10:08:16 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_base.h"
# include "ft_map.h"
# include "ft_settings.h"
# include "ft_error.h"

/* Check input arguments */
int		check_extension(t_map *map, const char *ext);
int		check_save_arg(char *save);
int		check_file_path(t_map *map, char *ext);

/* Check scene file */
void	parse_scene_file(t_map *prm, char *path);
int		parse_prm(t_map *map);
int		parse_map(t_map *map);
int		parse_map_to_list(t_map *map);
void	parse_validate_map(t_map *map);
void	print_status(char *title, char *name, char *status);

int		is_prm_complete(t_map *map);
int		parse_getline(t_map *map);
void	parse_identify_line(t_map *map);

/////////////////////////////////////////////////////////////////REMOVE
void	print_all_params(t_map *map);


/* Print error */
void	print_error(char *msg, t_track *track, char *add);
int		line_num(int add);

/* Errors.c */
char*	get_error_msg(t_error code);
void	throw_error(t_error msg, int line, char *add);

/* get_next_line */
int get_next_line(int fd, char **line);

/* Arrays */
char	**arr_create(int rows, int cols);
void	arr_delete(char **arr);
void	arr_print(char **arr);
void	arr_replace(char **arr, char to_replace, char replacer);
void	arr_fill(char **arr, t_list *lst);

/* Flood fill */
int		flood_fill(char **arr, int x, int y);
void	flood_fill_iter(char **arr, int x, int y);

t_map	*get_map(t_map *map);

#endif