/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:05:04 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/21 02:27:22 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int music_start(pid_t *x, char *filename)
{
	*x = fork();
	if (*x < 0) 
	{
		ft_putendl_fd("Music error", 2);
		return (0);
	}  
	else if (*x == 0) 
	{
		execlp("mpg123", "mpg123", "-q", filename, NULL);
	}
	else 
	{
		printf("from parent: mpg123 is pid %ls\n", x);		
	}
	return (0);      
}

int music_stop(pid_t x)
{
	kill(x, SIGKILL);
	return (0);
}