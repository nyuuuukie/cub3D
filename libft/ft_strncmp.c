/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:50:25 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/04 16:29:42 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*first;
	unsigned char	*second;

	index = 0;
	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (first[index] == second[index] && index + 1 < n)
	{
		if (first[index] == '\0' && second[index] == '\0')
			return (0);
		index++;
	}
	return (n == 0 ? 0 : (first[index] - second[index]));
}
