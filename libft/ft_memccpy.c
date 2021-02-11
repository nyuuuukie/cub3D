/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:37:18 by mhufflep          #+#    #+#             */
/*   Updated: 2020/10/30 18:22:05 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	symbol;
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst != src)
	{
		i = 0;
		d = (unsigned char *)dst;
		s = (unsigned char *)src;
		symbol = (unsigned char)c;
		while (i < n)
		{
			d[i] = s[i];
			if (s[i] == symbol)
				return (&d[i + 1]);
			i++;
		}
	}
	return (NULL);
}
