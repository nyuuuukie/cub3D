/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:21:37 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/12 05:18:50 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_base.h"

void	print_error(char *title, char *msg, char *add)
{
	write(2, title, ft_strlen(title));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	if (add != NULL)
	{
		write(2, " ", 1);
		write(2, add, ft_strlen(add)); 
	}
	write(2, "\n", 1);
}