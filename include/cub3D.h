/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/17 23:27:41 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_base.h"
# include "ft_map.h"
# include "ft_settings.h"
# include "ft_error.h"

/* Check input arguments */
int		check_extension(char *map, const char *ext);
int		check_save_arg(char *save);
int		check_file_path(char *map, char *ext);

/* Check scene file */
void	parse_scene_file(char *map, t_map *prm);
int		parse_prm(int fd, t_map *map);
int		parse_map(int fd, t_map *map);
int		parse_map_to_list(int fd, t_map *map);
void	parse_validate_map(t_map *map);
void	print_status(char *title, char *name, char *status);

int		is_prm_complete(t_map *map);
int		parse_getline(int fd, char **line);
void	parse_identify_line(char *line, t_map *map);

//REMOVE
void	print_all_params(t_map *map);
/* Print error */
void	print_error(char *msg, int line, char *add);
int		inc_line_number(int add);

/* Errors.c */
char*	get_error_msg(t_error code);
void	throw_error(t_error msg, int line, char *add);

/* get_next_line */
int get_next_line(int fd, char **line);

/* Arrays */
char	**create_arr(int rows, int cols);
void	delete_arr(char **arr);
void	print_array(char **arr);
void	replace_in_arr(char **arr, char to_replace, char replacer);
void	replace_in_str(char *arr, char to_replace, char replacer);
void	fill_arr(char **arr, t_list *lst);

/* Flood fill */
int		flood_fill(char **arr, int x, int y);
void	flood_fill_iter(char **arr, int x, int y);

t_map	*get_map(t_map *map);

#endif