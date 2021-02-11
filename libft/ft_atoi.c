/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:11:01 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/05 19:22:51 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_spaces(const char *s)
{
	char	*str;

	str = (char *)s;
	while (*str == ' ' || *str == '\t' || *str == '\r' ||
			*str == '\n' || *str == '\f' || *str == '\v')
		str++;
	return (str);
}

int			ft_atoi(const char *s)
{
	int sign;
	int result;
	int	len;

	result = 0;
	sign = 1;
	len = 0;
	s = skip_spaces(s);
	if (s[0] == '-' && (sign = -1) < 0)
		s++;
	else if (s[0] == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10;
		result += *s - '0';
		s++;
		if (result != 0)
			len++;
		if (len > 19 && sign > 0)
			return (-1);
		if (len > 19 && sign < 0)
			return (0);
	}
	return (result * sign);
}
