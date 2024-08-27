#include "song.h"
#include "bindings/c/tag_c.h"
#include <dirent.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadData {
  char **file_paths;
  size_t start;
  size_t end;
};

struct Song *songs = NULL;
int song_count = 0;

struct Album *albums = NULL;
int album_count = 0;

struct Song *current_song = NULL;

int is_audio_file(const char *filename) {
  const char *audio_extensions[] = {".mp3", ".wav"};
  size_t num_extensions =
      sizeof(audio_extensions) / sizeof(audio_extensions[0]);

  for (size_t i = 0; i < num_extensions; ++i) {
    if (strstr(filename, audio_extensions[i])) {
      return 1; // Found a matching extension
    }
  }
  return 0; // No matching extension
}

void *process_files(void *arg) {
  struct ThreadData *data = (struct ThreadData *)arg;

  for (size_t i = data->start; i < data->end; i++) {
    TagLib_File *file = taglib_file_new(data->file_paths[i]);
    if (file == NULL) {
      continue;
    }
    if (!taglib_file_is_valid(file)) {
      continue;
    }

    TagLib_Tag *tag = taglib_file_tag(file);
    if (tag == NULL) {
      continue;
    }

    if (file != NULL && tag != NULL) {
      pthread_mutex_lock(&mutex);

      // Process song data
      songs[i].FilePath = strdup(data->file_paths[i]);
      songs[i].Artist = strdup(taglib_tag_artist(tag));
      songs[i].Album = strdup(taglib_tag_album(tag));
      songs[i].TrackNumber = taglib_tag_track(tag);

      if (strlen(taglib_tag_title(tag)) != 0) {
        songs[i].Track = strdup(taglib_tag_title(tag));
      } else {
        songs[i].Track = strdup(basename(data->file_paths[i]));
      }

      // Handle album data
      bool new_album = true;
      size_t album_pointer = 0;

      for (size_t j = 0; j < album_count; j++) {
        if (strcmp(albums[j].Album, songs[i].Album) == 0) {
          new_album = false;
          album_pointer = j;
          break;
        }
      }

      if (new_album) {
        album_pointer = album_count;
        album_count++;

        albums[album_pointer].Album = strdup(songs[i].Album);
        albums[album_pointer].Artist = strdup(songs[i].Artist);
        albums[album_pointer].songs = malloc(
            1000 *
            sizeof(struct Song)); // Allocate space for 100 songs initially
        albums[album_pointer].SongCount = 0;
      }

      // Add song to album
      size_t a_s_count = albums[album_pointer].SongCount;
      if (a_s_count <
          1000) { // Ensure we stay within bounds of the pre-allocated array
        albums[album_pointer].songs[a_s_count] = songs[i];
        albums[album_pointer].SongCount++;
      }

      pthread_mutex_unlock(&mutex);
    }

    // taglib_tag_free_strings();
    taglib_file_free(file);
    free(data->file_paths[i]);
  }

  return NULL;
}

// Deep copy function for Song
struct Song *deep_copy_song(const struct Song *src) {
  if (src == NULL) {
    return NULL;
  }

  // Allocate memory for the new Song
  struct Song *dest = malloc(sizeof(struct Song));
  if (dest == NULL) {
    perror("Failed to allocate memory for Song");
    return NULL;
  }

  // Copy primitive members
  dest->Artist = src->Artist ? strdup(src->Artist) : NULL;
  dest->Album = src->Album ? strdup(src->Album) : NULL;
  dest->Track = src->Track ? strdup(src->Track) : NULL;
  dest->FilePath = src->FilePath ? strdup(src->FilePath) : NULL;

  // Ensure deep copy of pointers
  if (dest->Artist == NULL && src->Artist != NULL) {
    dest->Artist = malloc(strlen(src->Artist) + 1);
    strcpy(dest->Artist, src->Artist);
  }

  if (dest->Album == NULL && src->Album != NULL) {
    dest->Album = malloc(strlen(src->Album) + 1);
    strcpy(dest->Album, src->Album);
  }

  if (dest->Track == NULL && src->Track != NULL) {
    dest->Track = malloc(strlen(src->Track) + 1);
    strcpy(dest->Track, src->Track);
  }

  if (dest->FilePath == NULL && src->FilePath != NULL) {
    dest->FilePath = malloc(strlen(src->FilePath) + 1);
    strcpy(dest->FilePath, src->FilePath);
  }

  return dest;
}

void list_audio_files(const char *dir_path, char ***file_paths,
                      size_t *capacity) {
  struct dirent *entry = NULL;
  DIR *dp = opendir(dir_path);

  if (dp == NULL) {
    perror("opendir");
    return;
  }

#pragma unroll
  while ((entry = readdir(dp)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

    struct stat path_stat;
    stat(path, &path_stat);

    if (S_ISREG(path_stat.st_mode) && is_audio_file(entry->d_name)) {
      if (song_count >= *capacity) {
        *capacity *= 2;
        *file_paths = realloc(*file_paths, *capacity * sizeof(char *));
        if (*file_paths == NULL) {
          perror("realloc");
          exit(EXIT_FAILURE);
        }
      }
      (*file_paths)[song_count] = strdup(path);
      song_count++;
    } else if (S_ISDIR(path_stat.st_mode)) {
      list_audio_files(path, file_paths, capacity);
    }
  }

  closedir(dp);
}

int compare_songs_in_album(const void *a, const void *b) {

  struct Song *sa = (struct Song *)a;
  struct Song *sb = (struct Song *)b;

  return sa->TrackNumber - sb->TrackNumber;
}

void sort_albums(void) {

  for (size_t i = 0; i < album_count; i++) {
    qsort(albums[i].songs, albums[i].SongCount, sizeof(struct Song),
          compare_songs_in_album);
  }
}

void load_music_from_dir(const char *music_dir) {
  size_t capacity = 1000;
  char **file_paths = malloc(capacity * sizeof(char *));
  if (file_paths == NULL) {
    perror("malloc");
    exit(1);
  }

  list_audio_files(music_dir, &file_paths, &capacity);

  if (song_count > 0) {
    songs = calloc(song_count, sizeof(struct Song));
    albums = calloc(song_count, sizeof(struct Album));

    size_t num_threads = 1; // Number of threads to create
    pthread_t threads[num_threads];
    struct ThreadData thread_data[num_threads];

    size_t files_per_thread = song_count / num_threads;

    for (size_t i = 0; i < num_threads; i++) {
      thread_data[i].file_paths = file_paths;
      thread_data[i].start = i * files_per_thread;
      thread_data[i].end =
          (i == num_threads - 1) ? song_count : (i + 1) * files_per_thread;

      pthread_create(&threads[i], NULL, process_files, &thread_data[i]);
    }

    for (size_t i = 0; i < num_threads; i++) {
      pthread_join(threads[i], NULL);
    }

    sort_albums();
  }
  taglib_tag_free_strings();
  free(file_paths);
  pthread_mutex_destroy(&mutex);
}

void free_songs() {
  for (size_t i = 0; i < song_count; i++) {
    free(songs[i].FilePath);
    free(songs[i].Album);
    free(songs[i].Artist);
    free(songs[i].Track);
  }
  free(songs);
}

void free_albums() {
  for (size_t i = 0; i < album_count; i++) {
    free(albums[i].Artist);
    free(albums[i].Album);
  }
  free(albums);
}

int compare_songs(void *arg, const void *a, const void *b) {
  const struct Song *song_a = (const struct Song *)a;
  const struct Song *song_b = (const struct Song *)b;
  const ImGuiTableColumnSortSpecs *sort_spec =
      (const ImGuiTableColumnSortSpecs *)arg;

  int comparison = 0;
  if (sort_spec->ColumnIndex == 0) {
    comparison = strcmp(song_a->Artist, song_b->Artist);
  } else if (sort_spec->ColumnIndex == 1) {
    comparison = strcmp(song_a->Album, song_b->Album);
  } else if (sort_spec->ColumnIndex == 2) {
    comparison = strcmp(song_a->Track, song_b->Track);
  }

  if (sort_spec->SortDirection == ImGuiSortDirection_Descending) {
    comparison = -comparison;
  }

  return comparison;
}
