/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:21:37 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/11 22:21:39 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_error(char *title, char *msg)
{
	write(2, title, ft_strlen(title));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}