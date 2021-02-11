/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:49:12 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/11 06:58:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		c;
	int		digits;
	char	*str;
	int		sign;

	sign = 0;
	digits = 1;
	if (n < 0 && digits++)
		sign = 1;
	c = n;
	while (c / 10 != 0 && digits++)
		c /= 10;
	if (!(str = (char *)malloc(digits + 1)))
		return (NULL);
	str[0] = '-';
	str[digits] = '\0';
	while (digits > sign)
	{
		str[--digits] = (n < 0) ? (n % 10) * (-1) + '0' : (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
