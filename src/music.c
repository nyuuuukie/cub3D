/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:05:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 06:48:06 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_music(t_all *all, void *f(void *))
{
	if (all->map->bonus)
	{
		pthread_create(&all->pmusic, NULL, f, all);
		pthread_detach(all->pmusic);
	}
}

void	*init_music_fork(void *prm)
{
	t_all *all;

	all = (t_all*)prm;
	if (all->music_started == 0)
	{
		all->music_started = 1;
		music_start(all, &all->music, all->map->music, M_VOLUME);
		all->music_started = 0;
	}
	return (NULL);
}

void	*init_sound_fork(void *prm)
{
	t_all *all;

	all = (t_all*)prm;
	if (all->sound_started == 0)
	{
		all->sound_started = 1;
		music_start(all, &all->sound, all->map->sound, S_VOLUME);
		all->sound_started = 0;
	}
	return (NULL);
}

void	*init_wsound_fork(void *prm)
{
	t_all *all;

	all = (t_all*)prm;
	if (all->wsound_started == 0)
	{
		all->remove = 1;
		all->wsound_started = 1;
		music_start(all, &all->wsound, all->map->wsound, S_VOLUME);
		all->wsound_started = 0;
		all->remove = 0;
	}
	return (NULL);
}

void	*init_csound_fork(void *prm)
{
	t_all *all;

	all = (t_all*)prm;
	if (all->csound_started == 0)
	{
		all->csound_started = 1;
		music_start(all, &all->csound, all->map->csound, S_VOLUME);
		all->csound_started = 0;
	}
	return (NULL);
}

int		music_start(t_all *all, pid_t *x, char *filename, char *volume)
{
	(void)all;
	*x = fork();
	if (*x < 0)
		ft_putendl_fd("music fork error", 2);
	else if (*x == 0)
		execlp("mpg123", "mpg123", "-q", volume, filename, NULL);
	else
		waitpid(*x, 0, 0);
	return (0);
}
