/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:10:32 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/23 18:40:35 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_validate(t_map *map)
{
	int 	i;
	int 	j;
	int 	count;
	
	i = 1;
	count = 0;
	while (i < map->rows - 1)
	{
		j = 0;
		while (map->arr[i][j] != '\0')
		{
			if (ft_strchr(FLOOD_FILL_SPEC, map->arr[i][j]))
				flood_fill(map->arr, i, j);
			if (ft_strchr("NSEW", map->arr[i][j]) != NULL)
				player_check(++count, i, j);
			j++;
		}
		i++;
	}
	player_check(count, i, j);
}

void	flood_fill_iter(char **arr, int row, int col)
{
	t_map	*map;
	int		i;
	int		j;

	i = row + 1;
	while (i >= row - 1)
	{
		j = col + 1;
		while (j >= col - 1)
		{
			if ((i != row || j != col) && flood_fill(arr, i, j) > 0)
			{
				map = get_map(0);
				map->tr.i = col;
				map->tr.line += i - 2;
				throw_parse_error(ERR_MAP_NOT_CLOSED, 0);
			}
			j--;
		}
		i--;
	}
}

int		flood_fill(char **arr, int row, int col)
{
	if (row >= 0 && col >= 0)
	{
		if (arr[row][col] == ' ' || arr[row][col] == '\0')
			return (row);
		else if (ft_strchr(FLOOD_FILL_SPEC, arr[row][col]))
		{
			if (arr[row][col] == '2')
				arr[row][col] = 'x';
			if (arr[row][col] == '0')
				arr[row][col] = '#';
			if (arr[row][col] == '3')
				arr[row][col] = '.';
			flood_fill_iter(arr, row, col);
		}
	}
	return (0);
}

void	player_check(int count, int row, int col)
{
	t_map *map;

	if (count != 1)
	{
		map = get_map(0);
		map->tr.i = col - 1;
		map->tr.line += row - 1;
		if (count == 0)
			throw_parse_error(ERR_PLAYER_NOT_FOUND, 0);
		else 
			throw_parse_error(ERR_TOO_MANY_PLAYERS, 0);
	}
}
