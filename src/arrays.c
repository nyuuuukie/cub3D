/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 21:40:51 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/17 22:51:17 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
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

char**	create_arr(int rows, int cols)
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

void	fill_arr(char **arr, t_list *lst)
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

void	replace_in_str(char *str, char to_replace, char replacer)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_replace)
			str[i] = replacer;
		i++;
	}
}

void	replace_in_arr(char **arr, char to_replace, char replacer)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		replace_in_str(arr[i], to_replace, replacer);
		i++;
	}
}

void	print_array(char **arr)
{
	int i;

	i = 0;
	//ft_putstr_fd("--------------------------------", 1);
	while (arr[i] != NULL)
	{
		ft_putstr_fd("|", 1);
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("|", 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	//ft_putstr_fd("--------------------------------", 1);
}