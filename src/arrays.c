/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:40:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/17 07:36:18 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_arr(char **arr, int size)
{
	while (--size >= 0)
		free(arr[size]);
	free(arr);
}

char**	create_arr(t_map *map)
{
	t_list 	*node;
	char	**arr;
	int		i;

	i = 0;
	node = map->lst;
	if (!(arr = ft_calloc(map->rows + 1, sizeof(char *))))
		throw_error(ERR_CANNOT_ALLOC, 0, 0);
	while (i < map->rows)
	{
		if (!(arr[i] = ft_calloc(map->cols + 1, sizeof(char))))
		{
			throw_error(ERR_CANNOT_ALLOC, 0, 0);
			delete_arr(arr, i);
		}
		ft_strlcpy(arr[i], node->content, ft_strlen(node->content) + 1);
		node = node->next;
		i++;
	}
	arr[map->rows] = NULL;
	return (arr);
}

char **copy_arr(char **arr, int rows)
{
	char **copy;
	int i;

	i = 0;
	if (!(copy = ft_calloc(rows + 1, sizeof(char *))))
		throw_error(ERR_CANNOT_ALLOC, 0, 0);
	while (i < rows)
	{
		if (!(copy[i] = ft_strdup(arr[i])))
		{
			throw_error(ERR_CANNOT_ALLOC, 0, 0);
			delete_arr(copy, i);
		}
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}

void	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}