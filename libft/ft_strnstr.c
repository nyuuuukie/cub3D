/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:00:57 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/04 15:43:17 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hstack, const char *ndl, size_t n)
{
	char	*p;
	size_t	i;
	size_t	k;

	i = 0;
	p = (char *)hstack;
	if (ndl[0] == '\0')
		return (p);
	while (hstack[i] != '\0' && i < n)
	{
		if (hstack[i] == ndl[0])
		{
			k = 0;
			while (hstack[i + k] == ndl[k] && i + k < n)
			{
				if (ndl[k + 1] == '\0')
					return (&p[i]);
				k++;
			}
		}
		i++;
	}
	return (NULL);
}
