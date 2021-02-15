/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:45:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/15 05:04:11 by mhufflep         ###   ########.fr       */
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
	if (i == EXTENSION_LEN)
		return (1);
	return (end != 0 && (ft_strcmp(&path[end], ext) == 0));
}

int		check_file_path(char *file, char *ext)
{
	int fd;

	if (!ft_strcmp(file, "\0"))
		throw_error(FILE_ERROR, ERR_NO_FILENAME, 0);
	if (!check_extension(file, ext))
		throw_error(FILE_ERROR, ERR_WRONG_EXT, 0);
	if ((fd = open(file, O_RDONLY)) < 0)
		throw_error(FILE_ERROR, ERR_NO_FILE, 0);
	return (0);
}

int check_save_arg(char *save)
{
	int code;
	
	code = ft_strcmp(save, "--save");
	if (code)
		print_error("Argument error", "Invalid argument", save);
	return (code);
}