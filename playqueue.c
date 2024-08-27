#include "playqueue.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

ma_engine engine;
ma_sound current_sound;
bool sound_initialized = false;

bool paused = false;
bool init_audio(void) {
  if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    printf("Failed to initialize audio engine\n");
    return false;
  }
  return true;
}

void play_song(void) { ma_sound_start(&current_sound); }

void pause_song(void) { ma_sound_stop(&current_sound); }

void next_song(void) {
  if (is_queue_empty(&playqueue_head)) {
    return;
  }

  load_song_from_queue();
}

void prev_song(void) {
  if (is_queue_empty(&playhistory_head)) {
    return;
  }
  struct Song *s = pop_head_from_queue(&playhistory_head);

  push_to_head_queue(&playqueue_head, s);
  load_song_from_queue();
}

void song_end_callback(void *arg, struct ma_sound *sound) {
  struct Song *c_song = arg;
  push_to_head_queue(&playhistory_head, c_song);
  return;
}

void load_song_from_queue() {
  if (sound_initialized) {
    ma_sound_uninit(&current_sound);
    sound_initialized = false;
  }
  ma_sound_stop(&current_sound);
  struct Song *curr_song = TAILQ_FIRST(&playqueue_head);
  current_song = deep_copy_song(curr_song);
  TAILQ_REMOVE(&playqueue_head, curr_song, songs);
  if (ma_sound_init_from_file(&engine, curr_song->FilePath,
                              MA_SOUND_FLAG_STREAM, NULL, NULL,
                              &current_sound) != MA_SUCCESS) {
    printf("Failed to load song: %s\n", curr_song->FilePath);
  } else {
    sound_initialized = true;
    ma_sound_set_end_callback(&current_sound, song_end_callback, current_song);
    play_song();
    paused = false;
  }
}
