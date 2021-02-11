/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:25:27 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/05 19:27:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_str(const char *s, char c)
{
	while (*s)
		if (*s++ == c)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		length;
	int		rev_length;
	int		s_length;
	char	*res;

	length = 0;
	rev_length = 0;
	if (!s1 || !set || !ft_strncmp("", s1, 1))
		return (ft_strdup(""));
	s_length = ft_strlen(s1);
	while (is_in_str(set, s1[length]))
		length++;
	if (length == s_length)
		return (ft_strdup(""));
	while (is_in_str(set, s1[s_length - rev_length - 1]))
		rev_length++;
	res = ft_substr(s1, length, s_length - length - rev_length);
	return (res);
}
