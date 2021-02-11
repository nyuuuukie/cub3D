/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:53:29 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/05 19:27:30 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_parts(const char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**free_memory(char **s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
	return ((char **)0);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	int		arr_i;
	int		length;
	char	**result;

	arr_i = 0;
	count = count_parts(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * (count + 1))))
		return (free_memory(result));
	result[count] = NULL;
	i = 0;
	while (count--)
	{
		length = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i + length] != c && s[i + length] != '\0')
			length++;
		if (!(result[arr_i++] = ft_substr(s, i, length)))
			return (free_memory(result));
		i += length;
	}
	return (result);
}
