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

void soundlib_init(t_all *all) {
	BOOL res = BASS_Init(-1, 48000, 0, 0, 0);

	if (!res) {
		throw_engine_error(all, ERR_SOUNDLIB_INIT, EMPTY_EXTRA_MSG);
	}
}

void soundlib_deinit(void) {
	BASS_Free();
}




soundid	load_sound(t_all *all, char *path) {
	
	soundid sid = 0;

	if (path == NULL) {
		throw_engine_error(all, ERR_SOUNDLIB_LOAD, "Sound path cannot be empty");
		return 0;
	}

	sid = BASS_StreamCreateFile(false, path, 0, 0, 0);
	if (sid == 0) {
		throw_engine_error(all, ERR_SOUNDLIB_LOAD, EMPTY_EXTRA_MSG);
	}

	return sid;
}

void play_sound(soundid sid, bool loop)
{
	if (sid == 0) {
		ft_putendl_fd("play_sound: sid cannot be empty", 2);
		return ;
	}

	if (loop) {
		BASS_ChannelFlags(sid, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	}

	// BASS_ChannelStop(sid);
	// BASS_ChannelSetPosition(sid, 0, BASS_POS_BYTE);

	BASS_ChannelPlay(sid, 0);
}


void pause_sound(soundid sid) {

	if (sid == 0) {
		ft_putendl_fd("pause_sound: sid cannot be empty", 2);
		return ;
	}

	BASS_ChannelPause(sid);
}


#else

void soundlib_init(t_all *all) {
	(void)all;
}


soundid	load_sound(t_all *all, char *path) {
	(void)all;
	(void)path;
}

void play_sound(soundid sid, bool loop) {
	(void)sid;
	(void)loop;
}


void pause_sound(soundid sid) {
	(void)sid;
}

#endif




