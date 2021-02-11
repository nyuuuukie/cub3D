/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:05:59 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/02 07:42:55 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *p;
	char *last;

	p = (char *)s;
	last = 0;
	while (*p != '\0')
	{
		if (*p == c)
			last = p;
		p++;
	}
	if (*p == c)
		last = p;
	return (last);
}
