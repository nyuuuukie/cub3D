/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:49:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 22:29:25 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_base.h"
# include "ft_map.h"

/* Check input arguments */
int		check_extension(char *map, const char *ext);
int		check_save_arg(char *save);
int		check_file(char *map, char *ext);

/* Check map */
int		check_map(char *map, t_map *prm);

/* Print error */
void	print_error(char *title, char *msg, char *add);
char*	get_error_msg(int code);

/* get_next_line */
int get_next_line(int fd, char **line);


#endif