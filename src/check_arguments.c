/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:45:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 15:21:57 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_extension(char *map, const char *ext)
{
	int end;
	
	end = ft_strlen(map);
	while (end != 0 && map[end] != '.')
		end--;
	
	return (end != 0 && (ft_strcmp(&map[end], ext) == 0));
}

int		check_file(char *file, char *ext)
{
	int fd;
	int code;
	
	code = 1;
	if (check_extension(file, ext))
	{
		fd = open(file, O_RDONLY);
		code = fd < 0 ? 2 : 0;
		close(fd);
	}
	if (code)
		print_error("File error", get_map_error(code), 0); //CHANGE
	return (code);
}

int check_save_arg(char *save)
{
	int code;
	
	code = (ft_strcmp(save, "--save") && ft_strcmp(save, "-s"));
	if (code)
		print_error("Argument error", "Invalid flag", save);
	return (code);
}