/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:45:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/20 03:29:52 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_extension(char *path, const char *ext)
{
	int i;
	int end;
	
	i = 0; 
	end = ft_strlen(path) - 1;
	while (i < EXTENSION_LEN && end != 0 && path[end] != '.')
	{
		i++;
		end--;
	}
	if (path[end] != '.' && ) //ДОПИСАТЬ
	if (i == EXTENSION_LEN)
		return (1);
	if (!(end != 0 && !ft_strcmp(&path[end], ext)))
		throw_error(ERR_WRONG_EXT, line_num(0), &path[end]);	
	return (0);
}

int		check_file_path(char *file, char *ext)
{
	int fd;

	if (!ft_strcmp(file, "\0"))
		throw_error(ERR_NO_FILENAME, line_num(0), 0);
	check_extension(file, ext);
	if ((fd = open(file, O_RDONLY)) < 0)
		throw_error(ERR_NO_FILE, line_num(0), 0);
	return (0);
}

int check_save_arg(char *save)
{
	if (ft_strcmp(save, "--save"))
		throw_error(ERR_INVALID_ARG, 0, save);
	return (0);
}