/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:05:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/31 21:06:26 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_music(t_all *all, void *f(void *))
{
	if (all->map->bonus)
	{
		pthread_create(&all->pmusic, NULL, f, all);
		pthread_detach(all->pmusic);
	}
}

void *init_music_fork(void * prm)
{
	t_all *all = (t_all*)prm;
	if (all->music_started == 0)
	{
		all->music_started = 1;
		music_start(all, &all->music, all->map->music, M_VOLUME);
		waitpid(all->music, 0, 0);
		all->music_started = 0;
	}
	return (NULL);
}

void *init_sound_fork(void * prm)
{
	t_all *all = (t_all*)prm;
	if (all->sound_started == 0)
	{
		all->sound_started = 1;
		music_start(all, &all->sound, all->map->sound, S_VOLUME);
		waitpid(all->sound, 0, 0);
		all->sound_started = 0;
	}
	return (NULL);
}

void *init_wsound_fork(void * prm)
{
	t_all *all = (t_all*)prm;
	if (all->wsound_started == 0)
	{
		all->remove = 1;
		all->wsound_started = 1;
		music_start(all, &all->wsound, all->map->wsound, S_VOLUME);
		waitpid(all->wsound, 0, 0);
		all->wsound_started = 0;
		all->remove = 0;
	}
	return (NULL);
}

void *init_csound_fork(void * prm)
{
	t_all *all = (t_all*)prm;
	if (all->csound_started == 0)
	{
		all->csound_started = 1;
		music_start(all, &all->csound, "music/keys.mp3", S_VOLUME);
		waitpid(all->csound, 0, 0);
		all->csound_started = 0;
	}
	return (NULL);
}

int music_start(t_all *all, pid_t *x, char *filename, char *volume)
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
		execlp("mpg123", "mpg123", "-q", volume, filename, NULL);
		exit(0);
	}
	else 
	{
		ft_putnbr_fd(*x, 1);
		ft_putendl_fd(" <pid> mpg123", 1);
	}
	return (0);
}
