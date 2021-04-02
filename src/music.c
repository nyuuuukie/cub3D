/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:05:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	init_music(t_all *all, void *f(void *))
{
	if (all->map->bonus)
	{
		pthread_create(&all->pmusic, NULL, f, all);
		pthread_detach(all->pmusic);
	}
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

#else

void	init_music(t_all *all, void *f(void *))
{
	(void)all;
	(void)f;
}

int		music_start(t_all *all, pid_t *x, char *filename, char *volume)
{
	(void)all;
	(void)x;
	(void)filename;
	(void)volume;
	return (0);
}

#endif
