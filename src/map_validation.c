/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 23:10:32 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/19 23:15:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	flood_fill_iter(char **arr, int row, int col)
{
	int i;
	int j;

	i = row + 1;
	while (i >= row - 1)
	{
		j = col + 1;
		while (j >= col - 1)
		{
			if ((i != row || j != col) && flood_fill(arr, i, j) > 0)
			{
				throw_error(ERR_MAP_NOT_CLOSED, line_num(i), 0);
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
		else if (ft_strchr("02NSEW", arr[row][col]))
		{
			if (arr[row][col] == '0')
				arr[row][col] = '#';
			flood_fill_iter(arr, row, col);
		}
	}
	return (0);
}

void	player_check(int count, int row)
{
	if (count > 1)
		throw_error(ERR_TOO_MANY_PLAYERS, line_num(row - 1), 0);
	if (count == 0)
		throw_error(ERR_PLAYER_NOT_FOUND, 0, 0);
}

void	parse_validate_map(t_map *map)
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
			if (ft_strchr("02NSWE", map->arr[i][j]))
				flood_fill(map->arr, i, j);
			if (ft_strchr("NSEW", map->arr[i][j]) != NULL)
				player_check(++count, i);
			j++;
		}
		i++;
	}

	player_check(count, 0);
}
