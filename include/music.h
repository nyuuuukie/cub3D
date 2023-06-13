#ifndef MUSIC_H
#define MUSIC_H

#include "cub3d.h"

void soundlib_init(t_all *all);
void soundlib_deinit(void);

soundid	load_sound(t_all *all, char *path);

void play_sound(soundid sid, bool loop);

void pause_sound(soundid sid);

#endif