/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:40:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/23 18:31:43 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	arr_delete(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
		i++;
	while (--i >= 0)
		free(arr[i]);
	free(arr);
}

char*	create_line(int cols, char def)
{
	char *line;
	int i;

	i = 0;
	if (!(line = ft_calloc(cols + 1, sizeof(char))))
		throw_parse_error(ERR_CANNOT_ALLOC, 0);
	while (i < cols)
		line[i++] = def;
	return (line);
}

void	arr_create(char ***arr, int rows, int cols)
{
	int	i;

	i = 0;
	if (!(*arr = ft_calloc(rows + 1, sizeof(char *))))
		throw_parse_error(ERR_CANNOT_ALLOC, 0);
	while (i < rows)
	{
		(*arr)[i] = create_line(cols + 2, ' ');
		i++;
	}
	(*arr)[rows] = NULL; 
}

void	arr_fill(char **arr, t_list *lst)
{
	int		len;
	int		i;

	i = 1;
	while (lst)
	{
		len = ft_strlen(lst->content);
		ft_memmove(&arr[i][1], lst->content, len);
		lst = lst->next;
		i++;
	}
}

int		arr_replace(char **arr, char to_replace, char replacer)
{
	int i;
	int j;
	int n;

	i = 0;
	n = 0;
	while (arr && arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == to_replace)
			{
				arr[i][j] = replacer;
				n++;
			}
			j++;
		}
		i++;
	}
	return (n);
}
