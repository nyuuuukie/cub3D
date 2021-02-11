/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:54:11 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/04 05:29:46 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	s_length;
	char			*res;

	i = 0;
	if (!s || !f)
		return (NULL);
	s_length = ft_strlen(s);
	if (!(res = (char *)malloc(s_length + 1)))
		return (NULL);
	res[s_length] = '\0';
	while (i < s_length)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
