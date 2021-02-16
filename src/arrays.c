/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:40:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/16 23:12:51 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_arr(char **arr, int index)
{
	while (index >= 0)
		free(arr[index--]);
	free(arr);	
}

char**	create_arr(int rows, int cols)
{
	char	**arr;
	int		i;
	int		j;
	
	i = 0;
	if (!(arr = ft_calloc(rows + 1, sizeof(char *))))
		throw_error(INTERNAL_ERROR, ERR_CANNOT_ALLOC, 0);
	while (i < rows)
	{
		j = 0;
		if (!(arr[i] = ft_calloc(cols + 1, sizeof(char))))
		{
			delete_arr(arr, i);
			throw_error(INTERNAL_ERROR, ERR_CANNOT_ALLOC, 0);
		}
		i++;
	}
	arr[rows] = NULL;
	return (arr);
}