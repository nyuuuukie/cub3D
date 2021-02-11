/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 05:07:30 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/11 19:23:40 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_node
{
	int				fd;
	char			*buf;
	struct s_node 	*next;
}					t_node;

t_node				*search_node(int fd, t_node **nodes);
t_node				*push_node(int fd, t_node **nodes);
void				delete_element(t_node **nodes, t_node *current);
void				reallocate(t_node *current, char *arg1, char *arg2);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				clean_buffer(char *buf);
char				*ft_strjoin(char *s1, char *s2);
int					get_next_line(int fd, char **line);

#endif
