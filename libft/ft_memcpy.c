/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:26:28 by mhufflep          #+#    #+#             */
/*   Updated: 2020/10/30 21:38:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstcpy;
	char	*srccpy;

	if (dst != src)
	{
		dstcpy = (char *)dst;
		srccpy = (char *)src;
		while (n--)
		{
			*dstcpy++ = *srccpy++;
		}
	}
	return (dst);
}
