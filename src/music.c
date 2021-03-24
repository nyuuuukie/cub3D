/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:05:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/24 15:08:47 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_music(t_all *all)
{
	if (all->map->bonus && !all->started)
	{
		pthread_create(&all->pmusic, NULL, init_fork, all);
		pthread_detach(all->pmusic);
	}
}

void *init_fork(void * prm)
{
	t_all *all = (t_all*)prm;
	if (!all->started)
	{
		all->started = 1;
		sound_start(all, &all->sound, all->map->sound);
		waitpid(all->sound, 0, 0);
		all->started = 0;
	}
	return (NULL);
}

int music_start(t_all *all, pid_t *x, char *filename)
{
	(void)all;
	*x = fork();
	if (*x < 0) 
	{
		ft_putendl_fd("music fork error", 2);
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
		ft_putendl_fd(" <pid> mpg123", 1);
	}
	return (0);
}

int	sound_start(t_all *all, pid_t *id, char *filename)
{
	(void)all;
	*id = fork();
	if (*id < 0) 
	{
		ft_putendl_fd("sound fork error", 2);
		return (0);
	}  
	else if (*id == 0) 
	{
		execlp("mpg123", "mpg123", "-q", S_VOLUME, filename, NULL);
		exit(0);
	}
	else 
	{
		ft_putnbr_fd(*id, 1);
		ft_putendl_fd(" <pid> mpg123", 1);
	}
	return (0);
}

int music_stop(pid_t x)
{
	kill(x, SIGKILL);
	return (0);
}