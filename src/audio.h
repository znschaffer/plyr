#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"
#include <stdbool.h>

extern ma_engine engine;
extern ma_sound current_sound;
extern bool sound_initialized;
extern bool paused;
extern ma_decoder decoder;
extern float *audio_data;
extern size_t audio_data_size;

void load_song_from_queue(void);
void play_song(void);
void pause_song(void);
void prev_song(void);
void next_song(void);
bool init_audio(void);

void play_next_song_callback(void *data);

#endif
