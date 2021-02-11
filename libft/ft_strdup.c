/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:36:06 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/04 19:33:39 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		length;
	int		index;
	char	*str2;

	index = 0;
	length = ft_strlen(src);
	str2 = (char*)malloc((length + 1));
	if (str2)
	{
		while (src[index] != '\0')
		{
			str2[index] = src[index];
			index++;
		}
		str2[index] = '\0';
	}
	return (str2);
}
