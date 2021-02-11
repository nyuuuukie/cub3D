/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:58:32 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/02 08:05:08 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		s_length;
	size_t		i;
	char		*sub;

	i = 0;
	if (s == 0)
		return (0);
	s_length = ft_strlen(s);
	len = (len > (s_length - start)) ? s_length - start : len;
	if (start >= s_length)
		return (ft_strdup(""));
	if (!(sub = (char *)malloc(len + 1)))
		return (NULL);
	while (len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
