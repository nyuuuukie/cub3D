/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:24:16 by mhufflep          #+#    #+#             */
/*   Updated: 2020/10/31 20:24:53 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len_first;
	int		len_second;
	char	*res;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len_first = ft_strlen(s1);
	len_second = ft_strlen(s2);
	if (!(res = (char *)malloc(len_first + len_second + 1)))
		return (NULL);
	ft_memmove(&res[0], s1, len_first);
	ft_memmove(&res[len_first], s2, len_second);
	res[len_first + len_second] = '\0';
	return (res);
}
