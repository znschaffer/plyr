#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define MINIAUDIO_IMPLEMENTATION
#include "bindings/c/tag_c.h"
#include "cimgui.h"
#include "miniaudio.h"
#include "sokol_imgui.h"

typedef struct {
  char *Artist;
  char *Album;
  char *Track;
  char *FilePath;
} Song;
Song *songs;
int song_count = 0;

ma_engine engine;
ma_sound current_sound;
bool sound_initialized = false;
static struct {
  sg_pass_action pass_action;
} state;

void init_audio() {

  if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    printf("Failed to initialize audio engine\n");
    exit(1);
  }
}

void play_song() {
  ma_sound_start((&current_sound));
  printf("Playing song\n");
}

void pause_song() {
  ma_sound_stop(&current_sound);
  printf("Paused song\n");
}

void load_song(const char *file_path) {

  if (sound_initialized) {
    ma_sound_uninit(&current_sound);
    sound_initialized = false;
  }
  ma_sound_stop(&current_sound);
  if (ma_sound_init_from_file(&engine, file_path, MA_SOUND_FLAG_STREAM, NULL,
                              NULL, &current_sound) != MA_SUCCESS) {
    printf("Failed to load song: %s\n", file_path);
  } else {
    sound_initialized = true;
    printf("Loaded song: %s\n", file_path);
    play_song();
  }
}

void draw_controls() {
  if (igButton("Play", (ImVec2){0, 0})) {
    play_song();
  }
  igSameLine(0.0f, -1.0f);

  if (igButton("Pause", (ImVec2){0, 0})) {
    pause_song();
  }
}
static void init(void) {
  init_audio();
  sg_setup(&(sg_desc){
      .environment = sglue_environment(),
      .logger.func = slog_func,
  });
  simgui_setup(&(simgui_desc_t){0});

  // initial clear color
  state.pass_action =
      (sg_pass_action){.colors[0] = {.load_action = SG_LOADACTION_CLEAR,
                                     .clear_value = {0.0f, 0.5f, 1.0f, 1.0}}};
}

int compare_songs(void *arg, const void *a, const void *b) {
  const Song *song_a = (const Song *)a;
  const Song *song_b = (const Song *)b;
  const ImGuiTableColumnSortSpecs *sort_spec =
      (const ImGuiTableColumnSortSpecs *)arg;

  // Determine which column is being sorted and the direction
  int comparison = 0;

  if (sort_spec[0].ColumnIndex == 0) {
    comparison = strcmp(song_a->Artist, song_b->Artist);
  } else if (sort_spec[0].ColumnIndex == 1) {
    comparison = strcmp(song_a->Album, song_b->Album);
  } else if (sort_spec[0].ColumnIndex == 2) {
    comparison = strcmp(song_a->Track, song_b->Track);
  }

  // Reverse comparison if the sort direction is descending
  if (sort_spec[0].SortDirection == ImGuiSortDirection_Descending) {
    comparison = -comparison;
  }

  return comparison;
}

int is_audio_file(const char *filename) {
  const char *audio_extensions[] = {".mp3", ".wav", ".flac",
                                    ".aac", ".ogg", ".m4a"};
  size_t num_extensions =
      sizeof(audio_extensions) / sizeof(audio_extensions[0]);

  for (size_t i = 0; i < num_extensions; ++i) {
    if (strstr(filename, audio_extensions[i])) {
      return 1; // Found a matching extension
    }
  }
  return 0; // No matching extension
}

void list_audio_files(const char *dir_path, char ***file_paths, size_t *count,
                      size_t *capacity) {
  struct dirent *entry;
  DIR *dp = opendir(dir_path);

  if (dp == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dp)) != NULL) {
    // Ignore the "." and ".." entries
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

    struct stat path_stat;
    stat(path, &path_stat);

    if (S_ISREG(path_stat.st_mode) && is_audio_file(entry->d_name)) {
      // Ensure there's enough space in the array
      if (*count >= *capacity) {
        *capacity *= 2;
        *file_paths = realloc(*file_paths, *capacity * sizeof(char *));
        if (*file_paths == NULL) {
          perror("realloc");
          exit(EXIT_FAILURE);
        }
      }
      // Store the file path
      (*file_paths)[*count] = strdup(path);
      (*count)++;
    } else if (S_ISDIR(path_stat.st_mode)) {
      // If it's a directory, recurse into it
      list_audio_files(path, file_paths, count, capacity);
    }
  }

  closedir(dp);
}

void load_music_from_dir(char *music_dir) {
  size_t capacity = 100;
  size_t count = 0;
  char **file_paths = malloc(capacity * sizeof(char *));
  list_audio_files(music_dir, &file_paths, &count, &capacity);

  if (count > 0) {
    songs = malloc(count * sizeof(Song));

    for (size_t i = 0; i < count; i++) {
      TagLib_File *f = taglib_file_new(file_paths[i]);
      TagLib_Tag *t = taglib_file_tag(f);
      songs[i].FilePath = strdup(file_paths[i]);
      songs[i].Artist = strdup(taglib_tag_artist(t));
      songs[i].Album = strdup(taglib_tag_album(t));
      songs[i].Track = strdup(taglib_tag_title(t));
      taglib_tag_free_strings();
      taglib_file_free(f);
      free(file_paths[i]);
    }
  }
  free(file_paths);
  song_count = count;
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

int set_music_dir(struct ImGuiInputTextCallbackData *data) {

  printf("music_dir: %s\n", data->Buf);

  return 0;
}

void draw_table(Song *songs, int song_count) {
  static int selected_row = -1;
  static ImGuiTableFlags flags =
      ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY |
      ImGuiTableFlags_RowBg | ImGuiTableFlags_Reorderable;
  if (igBeginTable("SongTable", 3, flags,
                   (ImVec2){0, igGetWindowHeight() -
                                   igGetTextLineHeightWithSpacing() * 4},
                   0)) {

    igTableSetupScrollFreeze(0, 1);
    igTableSetupColumn("Artist", ImGuiTableColumnFlags_DefaultSort, 0, 0);
    igTableSetupColumn("Album", ImGuiTableColumnFlags_None, 0, 0);
    igTableSetupColumn("Track", ImGuiTableColumnFlags_None, 0, 0);
    igTableHeadersRow();

    ImGuiTableSortSpecs *sort_specs = igTableGetSortSpecs();
    if (sort_specs && sort_specs->SpecsDirty) {

      // Perform sorting based on the sort specs
      qsort_r(songs, song_count, sizeof(Song), (void *)sort_specs->Specs,
              compare_songs); // qsort_r is used for passing extra argument
      sort_specs->SpecsDirty = false;
    }

    for (int row = 0; row < song_count; row++) {
      igTableNextRow(ImGuiTableRowFlags_None, 0.0f);
      igTableSetColumnIndex(0);
      igText("%s", songs[row].Artist);
      igTableSetColumnIndex(1);
      igText("%s", songs[row].Album);
      igTableSetColumnIndex(2);
      if (igSelectable_Bool(songs[row].Track, selected_row == row,
                            ImGuiSelectableFlags_SpanAllColumns,
                            (ImVec2){0, 0})) {
        selected_row = row;             // Update selected row
        load_song(songs[row].FilePath); // Play the selected song
      }
    }

    // igEndChild();
    igEndTable();
  }
}

void draw_tabs() {
  ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
  bool yes = true;
  if (igBeginTabBar("MyTabBar", tab_bar_flags)) {
    if (igBeginTabItem("Tracks", &yes, 0)) {
      igText("This is the Avocado tab!\nblah blah blah blah blah");
      igEndTabItem();
    }
    if (igBeginTabItem("Albums", NULL, 0)) {
      igText("This is the Broccoli tab!\nblah blah blah blah blah");
      igEndTabItem();
    }
    if (igBeginTabItem("Playlist", NULL, 0)) {
      igText("This is the Cucumber tab!\nblah blah blah blah blah");
      igEndTabItem();
    }
    igEndTabBar();
  }
}

static void frame(void) {
  simgui_new_frame(&(simgui_frame_desc_t){
      .width = sapp_width(),
      .height = sapp_height(),
      .delta_time = sapp_frame_duration(),
      .dpi_scale = sapp_dpi_scale(),
  });

  /*=== UI CODE STARTS HERE ===*/
  igSetNextWindowPos((ImVec2){0, 0}, ImGuiCond_Once, (ImVec2){0, 0});
  igSetNextWindowSize((ImVec2){sapp_width(), sapp_height()}, ImGuiCond_None);
  igBegin("Hello Dear ImGui!", 0,
          ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration |
              ImGuiWindowFlags_NoMove);

  char music_dir[500];
  if (igInputText("Music Directory", music_dir, 500,
                  ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL)) {

    load_music_from_dir(music_dir);
  }

  // printf("music_dir buf: %s\n", music_dir);
  // file picker somehow
  // maybe just input box?
  // then load all songs from there - run them through threaded TagLib calls
  // fill the lis

  draw_tabs();
  draw_table(songs, song_count);
  draw_controls();

  igNewLine();
  igButton("Play", (ImVec2){igGetFrameHeight(), igGetFrameHeight()});

  igEnd();
  /*=== UI CODE ENDS HERE ===*/

  sg_begin_pass(
      &(sg_pass){.action = state.pass_action, .swapchain = sglue_swapchain()});
  simgui_render();
  sg_end_pass();
  sg_commit();
}

static void cleanup(void) {
  free_songs();
  simgui_shutdown();
  sg_shutdown();
  ma_sound_uninit(&current_sound);
  ma_engine_uninit(&engine);
}

static void event(const sapp_event *ev) { simgui_handle_event(ev); }

sapp_desc sokol_main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  return (sapp_desc){
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = cleanup,
      .event_cb = event,
      .window_title = "Hello Sokol + Dear ImGui",
      .width = 800,
      .height = 600,
      .icon.sokol_default = true,
      .logger.func = slog_func,
  };
}
