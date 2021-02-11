/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 02:08:30 by kcaraway          #+#    #+#             */
/*   Updated: 2020/12/08 00:12:55 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst && *lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

t_list	*ft_lstcopy(t_list *list)
{
	t_list	*head;
	t_list 	*new;

	head = NULL;
	// head = ft_lstnew(list->content);
	// list = list->next;
	while (list && list->content)
	{
		if (!(new = ft_lstnew(list->content))) 
		{
			ft_lstclear(&head, free); //Возможен double free, зависит от реализации lstclear.
			return (NULL);
		}
		ft_lstadd_back(&head, new);	//Мой lstaddback работает с null, можешь раскомментировать две строчки сверху и попробовать со своим addback
		list = list->next;
	}
	return (head);
}

void	ft_lstsort(t_list *lst)
{
	int 	sorted;
	t_list	*tmp;
	char	*str;

	sorted = 0;
	while (!sorted)
	{
		tmp = lst;
		sorted = 1;
		while (tmp && tmp->next != NULL)
		{
			if (ft_memcmp(tmp->content, tmp->next->content, ft_strlen(tmp->content) + 1) > 0)
			{
				str = tmp->content;
				tmp->content = tmp->next->content;
				tmp->next->content = str;
				sorted = 0;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	print_envp(t_list *list, int fd)
{
	char	*tmp;

	while (list && list->content)
	{
		ft_putstr_fd("declare -x ", fd);
		if ((tmp = ft_strchr(list->content, '=')))
		{
			write(fd, list->content, tmp - list->content);
			write(fd, "\"", 1);
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\"", 1);
		}
		else
		{
			ft_putstr_fd(list->content, fd);
			ft_putstr_fd("\n", fd);
		}
		list = list->next;
	}
}

int		valid_argv(char *str, int fd) // исправить
{
	int		i;

	i = 0;
	if (ft_isalpha(str[i]))
	{
		while (ft_isalpha(str[i]) && ft_isdigit(str[i]))
			i++;
		if (str[i++] == '=')
			if (!ft_isprint(str[i]) && !ft_isdigit(str[i]))
			{
			}
	}
	else
	{
		ft_putstr_fd("export: `", fd);
		ft_putstr_fd(str, fd);
		ft_putstr_fd("': not a valid identifier", fd);
		return (0);
	}
	return (1);
}

int		ft_lstadd_back1(t_list **lst, t_list *new)
{
	t_list *temp;

	if (!lst && !new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
	new->next = NULL;
	return (1);
}

int		ft_export(t_all *all, t_cmd *cmd, int fd) // исправить все исправить нихера не работает
{
	int		i;
	t_list	*list;
	t_list	*list_copy;


	list = all->envp;
	i = 1;
	if (cmd->argv[i])
	{
		while (cmd->argv[i])
		{
			if (valid_argv(cmd->argv[i], fd))
				if (!ft_lstadd_back1(&list, ft_lstnew(cmd->argv[i])))
					return (1);
			i++;
		}
	}
	else
	{
		list_copy = ft_lstcopy(list);
		ft_lstsort(list_copy);
		print_envp(list_copy, fd); // Фд вроде тот передал
	}
	return (0);
}
