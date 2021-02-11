/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:55 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/01 18:24:57 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *newelem;

	if (!(newelem = malloc(sizeof(t_list))))
		return (NULL);
	newelem->next = NULL;
	newelem->content = content;
	return (newelem);
}
