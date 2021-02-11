/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:01:22 by mhufflep          #+#    #+#             */
/*   Updated: 2020/10/30 19:16:37 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t type_size)
{
	void	*ptr;

	ptr = malloc(count * type_size);
	if (ptr)
	{
		ft_memset(ptr, 0, count * type_size);
	}
	return (ptr);
}
