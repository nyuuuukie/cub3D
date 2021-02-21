/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:40:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/21 09:27:12 by mhufflep         ###   ########.fr       */
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
		throw_error(ERR_CANNOT_ALLOC, 0, 0);
	while (i < cols)
		line[i++] = def;
	return (line);
}

char**	arr_create(int rows, int cols)
{
	char	**arr;
	int		i;

	i = 0;
	if (!(arr = ft_calloc(rows + 1, sizeof(char *))))
		throw_error(ERR_CANNOT_ALLOC, 0, 0);
	while (i < rows)
	{
		arr[i] = create_line(cols + 2, ' ');
		i++;
	}
	arr[rows] = NULL;
	return (arr);
}

void	arr_fill(char **arr, t_list *lst)
{
	t_list 	*node;
	int	i;

	i = 1;
	node = lst;
	while (node)
	{
		ft_memmove(&arr[i][1], node->content, ft_strlen(node->content));
		node = node->next;
		i++;
	}
}

void	arr_replace(char **arr, char to_replace, char replacer)
{
	int i;
	int j;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == to_replace)
				arr[i][j] = replacer;
			j++;
		}
		i++;
	}
}

void	arr_print(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd("|", 1);
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("|", 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}