/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:10:08 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/05 19:40:06 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newlist;
	t_list *tmp;

	if (!lst)
		return (NULL);
	if (!(newlist = malloc(ft_lstsize(lst) * sizeof(t_list))))
		return (NULL);
	tmp = newlist;
	if (f != NULL)
	{
		while (lst)
		{
			if (tmp)
				tmp->content = f(lst->content);
			if (lst->next)
				if (!(tmp->next = ft_lstnew(NULL)))
				{
					ft_lstclear(&lst, del);
					return (0);
				}
			lst = lst->next;
			tmp = tmp->next;
		}
	}
	return (newlist);
}
