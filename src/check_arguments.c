/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:45:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/11 22:11:44 by mhufflep         ###   ########.fr       */
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

int		check_map_arg(char *map)
{
	int i;
	int fd;
	int code;
	
	i = 0;
	if (check_extension(map, ".cub"))
	{
		fd = open(map, O_RDONLY);
		code = fd < 0 ? 2 : 0;
		close(fd);
	}
	else
		code = 1;
	return (code);
}

int check_save_arg(char *save)
{
	return (ft_strcmp(save, "--save") && ft_strcmp(save, "-s"));
}