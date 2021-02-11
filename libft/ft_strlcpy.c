/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:48:05 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/02 12:24:16 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_index;

	src_index = 0;
	if (src == NULL || dst == NULL)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while (src[src_index] != '\0' && src_index + 1 < size)
	{
		dst[src_index] = src[src_index];
		src_index++;
	}
	dst[src_index] = '\0';
	return (ft_strlen(src));
}
