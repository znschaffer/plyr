#ifndef SONG_H
#define SONG_H

#include <stddef.h>
#include <sys/queue.h>

struct Song {
  char *Artist;
  char *Album;
  char *Track;
  char *FilePath;
  unsigned int TrackNumber;
  TAILQ_ENTRY(Song) songs;
};

struct Album {
  char *Artist;
  char *Album;
  int SongCount;
  struct Song *songs;
} __attribute__((aligned(32)));

extern struct Album *albums;
extern int album_count;

extern struct Song *songs;
extern int song_count;

extern struct Song *current_song;

void load_music_from_dir(const char *music_dir);
void free_songs();
void free_albums();
struct Song *deep_copy_song(const struct Song *src);
void list_audio_files(const char *dir_path, char ***file_paths,
                      size_t *capacity);
int compare_songs(void *arg, const void *a, const void *b);
int is_audio_file(const char *filename);

#endif
