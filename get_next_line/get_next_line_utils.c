/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 05:14:01 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/20 04:36:45 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_buffer(char *buf)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buf[i] = '\0';
		i++;
	}
}

void	delete_element(t_thread **threads, t_thread *current)
{
	t_thread *prev;
	t_thread *curr;

	prev = *threads;
	curr = *threads;
	if (curr)
	{
		if (curr->fd != current->fd)
		{
			while (curr->fd != current->fd)
			{
				prev = curr;
				curr = curr->next;
			}
			prev->next = curr->next;
		}
		else
			*threads = curr->next;
		(curr->buf != NULL) ? free(curr->buf) : NULL;
		(curr != NULL) ? free(curr) : NULL;
	}
}

void	reallocate(t_thread *current, char *arg1, char *arg2)
{
	char	*tmp;

	tmp = current->buf;
	current->buf = ft_strjoin(arg1, arg2);
	if (tmp)
		free(tmp);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstcpy;
	char	*srccpy;

	if (dst != src)
	{
		dstcpy = (char *)dst;
		srccpy = (char *)src;
		while (n--)
		{
			*dstcpy++ = *srccpy++;
		}
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_first;
	int		len_second;
	char	*res;

	len_first = 0;
	len_second = 0;
	while (s1 && s1[len_first])
		len_first++;
	while (s2 && s2[len_second])
		len_second++;
	if (!(res = (char *)malloc(len_first + len_second + 1)))
		return (NULL);
	ft_memcpy(&res[0], s1, len_first);
	ft_memcpy(&res[len_first], s2, len_second);
	res[len_first + len_second] = '\0';
	return (res);
}
