/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 06:02:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 06:07:53 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
