#include "audio.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

ma_engine engine;
ma_sound current_sound;
ma_decoder decoder;
float *audio_data = NULL;
size_t audio_data_size = 0;
bool sound_initialized = false;

bool paused = false;

void cleanup_decoder(void) {
  if (audio_data != NULL) {
    free(audio_data);
    audio_data = NULL;
  }
  audio_data_size = 0;
}

bool load_decode_audio(struct Song *s) {
  ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 2, 48000);

  if (ma_decoder_init_file(s->FilePath, &config, &decoder) != MA_SUCCESS) {
    return false;
  }
  ma_uint64 frame_count;
  ma_decoder_get_length_in_pcm_frames(&decoder, &frame_count);

  audio_data_size = frame_count * decoder.outputChannels;
  audio_data = (float *)malloc(audio_data_size * sizeof(float));

  ma_uint64 frames_read;
  ma_decoder_read_pcm_frames(&decoder, audio_data, frame_count, &frames_read);
  ma_decoder_uninit(&decoder);

  // float maxSample = 0.0f;
  // for (size_t i = 0; i < audio_data_size; i++) {
  //   float absSample = fabsf(audio_data[i]);
  //   if (absSample > maxSample) {
  //     maxSample = absSample;
  //   }
  // }
  // if (maxSample > 0.0f) {
  //   for (size_t i = 0; i < audio_data_size; i++) {
  //     audio_data[i] /= maxSample;
  //   }
  // }
  return true;
}

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
  if (ma_sound_init_from_file(&engine, current_song->FilePath,
                              MA_SOUND_FLAG_STREAM, NULL, NULL,
                              &current_sound) != MA_SUCCESS) {
    printf("Failed to load song: %s\n", curr_song->FilePath);
  } else {
    sound_initialized = true;
    cleanup_decoder();
    load_decode_audio(current_song);
    ma_sound_set_end_callback(&current_sound, song_end_callback, current_song);
    play_song();
    paused = false;
  }
}
