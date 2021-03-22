/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:05:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/22 18:52:07 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int music_start(t_all *all, pid_t *x, char *filename)
{
	(void)all;
	*x = fork();
	if (*x < 0) 
	{
		ft_putendl_fd("music error", 2);
		return (0);
	}  
	else if (*x == 0) 
	{
		execlp("mpg123", "mpg123", "-q", M_VOLUME, filename, NULL);
		exit(0);
	}
	else 
	{
		ft_putnbr_fd(*x, 1);
		ft_putendl_fd("mpg123 <== ", 1);
	}
	return (0);
}

int	sound_start(t_all *all, pid_t *id, char *filename)
{
	(void)all;
	*id = fork();
	if (*id < 0) 
	{
		ft_putendl_fd("music error", 2);
		return (0);
	}  
	else if (*id == 0) 
	{
		execlp("mpg123", "mpg123", "-q", S_VOLUME, filename, NULL);
		exit(0);
	}
	else 
	{
		ft_putstr_fd("mpg123 pid:", 1);
		ft_putnbr_fd(*id, 1);
		ft_putendl_fd("", 1);
	}
	return (0);
}

int music_stop(pid_t x)
{
	kill(x, SIGKILL);
	return (0);
}