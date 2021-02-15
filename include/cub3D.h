/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/15 06:17:39 by mhufflep         ###   ########.fr       */
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
int		parse_scene_file(char *map, t_map *prm);

/* Print error */
void	print_error(char *title, char *msg, char *add);
int		inc_line_number(int add);

/* Errors.c */
char*	get_error_msg(t_err_msg code);
char*	get_error_title(t_err_ttl code);
void	throw_error(t_err_ttl title, t_err_msg msg, char *add);

/* get_next_line */
int get_next_line(int fd, char **line);


#endif