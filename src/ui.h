#ifndef UI_H
#define UI_H

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "queue.h"
extern const char *status_pause;
extern const char *status_play;
extern char *music_dir;
void draw_timeline(void);
void draw_waveform(void);
void draw_controls(void);
void draw_albums_list(void);
void draw_tracks_list(void);
void draw_queue(struct playqueue_tq *queue, char *label);
void draw_tabs(void);
void draw_open_music_dir(void);

bool filtered_song(ImGuiTextFilter filter, size_t row);

#endif // !UI_H
