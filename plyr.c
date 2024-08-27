#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/queue.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define MINIAUDIO_IMPLEMENTATION
#include "cimgui.h"
#include "miniaudio.h"
#include "nativefiledialog-cmake/src/include/nfd.h"
#include "playqueue.h"
#include "queue.h"
#include "sokol_imgui.h"
#include "song.h"

const char *music_dir;

const char *status_pause = ">";
const char *status_play = "||";

static struct {
  sg_pass_action pass_action;
} __attribute__((aligned(128))) state;

void draw_timeline() {
  float time = 0;
  float length = 1;
  int pcm_frame_time = 0;
  unsigned long long pcm_frame_length = 0;

  if (sound_initialized == true) {
    time = ma_sound_get_time_in_pcm_frames(&current_sound);
    ma_sound_get_cursor_in_seconds(&current_sound, &time);
    ma_sound_get_length_in_seconds(&current_sound, &length);
    pcm_frame_time = ma_sound_get_time_in_pcm_frames(&current_sound);
    ma_sound_get_length_in_pcm_frames(&current_sound, &pcm_frame_length);
  }

  char *buf = "";

  igBeginGroup();

  igText("%d:%02d", (int)time / 60, (int)time % 60);
  if (current_song != NULL) {

    ImVec2 text_size;
    char *artist_song = NULL;
    asprintf(&artist_song, "%s - %s", current_song->Artist,
             current_song->Track);
    igCalcTextSize(&text_size, artist_song, &artist_song[strlen(artist_song)],
                   false, 0);
    igSameLine((igGetWindowWidth() / 2) - (text_size.x / 2), 0);
    igText("%s - %s", current_song->Artist, current_song->Track);
  }

  igSameLine(igGetWindowWidth() - 48, 0);
  igText("%d:%02d", (int)length / 60, (int)length % 60);
  // igNewLine();

  igProgressBar(time / length, (ImVec2){-1.0, 0.0}, buf);
  ImVec2 progress_bar_size;
  ImVec2 progress_bar_min;
  ImVec2 progress_bar_max;
  igGetItemRectSize(&progress_bar_size);
  igGetItemRectMin(&progress_bar_min);
  igGetItemRectMax(&progress_bar_max);

  if (igIsItemHovered(0) &&
      igIsMouseClicked_Bool(ImGuiMouseButton_Left, true)) {

    // get point on progress bar where mouse is clicked - translate to time in
    // song and set song time to that

    if (sound_initialized == true) {
      ImVec2 pos;
      igGetMousePos(&pos);

      float clicked_fraction =
          (pos.x - progress_bar_min.x) / progress_bar_size.x;

      ma_uint64 time_in_pcm_frames =
          (ma_uint64)(pcm_frame_length * clicked_fraction);
      ma_sound_seek_to_pcm_frame(&current_sound, time_in_pcm_frames);
    }
  }

  igEndGroup();
}

void draw_controls() {
  igBeginGroup();

  const char *status;
  if (paused) {
    status = status_pause;
  } else {
    status = status_play;
  }

  if (igButton("Prev", (ImVec2){0, 0})) {
    prev_song();
  }
  igSameLine(0.0F, 1.0F);
  if (igButton(status, (ImVec2){0, 0})) {
    if (paused) {
      play_song();
    } else {
      pause_song();
    }
    paused = !paused;
  }
  igSameLine(0.0F, 1.0F);
  if (igButton("Next", (ImVec2){0, 0})) {
    next_song();
  }
  igEndGroup();
}

void update_audio() {
  if (!ma_sound_is_playing(&current_sound) && !paused) {
    if (!TAILQ_EMPTY(&playqueue_head)) {
      load_song_from_queue();
    }
  }
}

static void init(void) {

  init_queue(&playqueue_head);
  init_queue(&playhistory_head);

  if (init_audio() == false) {
    return;
  }
  music_dir = calloc(500, sizeof(char));

  sg_setup(&(sg_desc){
      .environment = sglue_environment(),
      .logger.func = slog_func,
  });
  simgui_setup(&(simgui_desc_t){0});

  // initial clear color
  state.pass_action =
      (sg_pass_action){.colors[0] = {.load_action = SG_LOADACTION_CLEAR,
                                     .clear_value = {0.0F, 0.5F, 1.0F, 1.0}}};
}

int set_music_dir(struct ImGuiInputTextCallbackData *data) {
  printf("music_dir: %s\n", data->Buf);
  return 0;
}

void draw_albums_list() {
  static int selected_row = -1;
  struct Album *selected_album = NULL;
  static ImGuiTableFlags flags =
      ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY |
      ImGuiTableFlags_RowBg | ImGuiTableFlags_Reorderable;
  if (igBeginTable("AlbumTable", 3, flags,
                   (ImVec2){0, igGetWindowHeight() -
                                   igGetTextLineHeightWithSpacing() * 8},
                   0)) {

    igTableSetupScrollFreeze(0, 1);
    igTableSetupColumn("Artist", ImGuiTableColumnFlags_DefaultSort, 0, 0);
    igTableSetupColumn("Album", ImGuiTableColumnFlags_None, 0, 0);
    igTableHeadersRow();

    ImGuiTableSortSpecs *sort_specs = igTableGetSortSpecs();
    if (sort_specs && sort_specs->SpecsDirty) {

      // Perform sorting based on the sort specs
      qsort_r(songs, song_count, sizeof(struct Song), (void *)sort_specs->Specs,
              compare_songs); // qsort_r is used for passing extra argument
      sort_specs->SpecsDirty = false;
    }

    for (int row = 0; row < album_count; row++) {
      igTableNextRow(ImGuiTableRowFlags_None, 0.0F);
      igTableSetColumnIndex(0);
      igText("%s", albums[row].Artist);
      igTableSetColumnIndex(1);
      if (igSelectable_Bool(albums[row].Album, selected_album == &albums[row],
                            ImGuiSelectableFlags_SpanAllColumns,
                            (ImVec2){0, 0})) {

        for (int i = 0; i < albums[row].SongCount; i++) {
          push_to_tail_queue(&playqueue_head, &albums[row].songs[i]);
        }

        selected_album = &albums[row]; // Update selected row
      }
    }

    // igEndChild();
    igEndTable();
  }
}

bool filtered_song(ImGuiTextFilter filter, size_t row) {
  if (!ImGuiTextFilter_PassFilter(
          &filter, songs[row].Artist,
          &songs[row].Artist[strlen(songs[row].Artist)])) {
    if (!ImGuiTextFilter_PassFilter(
            &filter, songs[row].Album,
            &songs[row].Album[strlen(songs[row].Album)])) {
      if (!ImGuiTextFilter_PassFilter(
              &filter, songs[row].Track,
              &songs[row].Track[strlen(songs[row].Track)])) {
        // doesn't match any filter
        return false;
      }
    }
  }
  return true;
}

void draw_tracks_list() {
  static ImGuiTextFilter filter;
  ImGuiTextFilter_Draw(&filter, "Filter", 0);

  struct Song *selected_song = NULL;

  static ImGuiTableFlags flags =
      ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY |
      ImGuiTableFlags_RowBg | ImGuiTableFlags_Reorderable;

  if (igBeginTable("SongTable", 3, flags,
                   (ImVec2){0, igGetWindowHeight() -
                                   igGetTextLineHeightWithSpacing() * 9},
                   0)) {

    igTableSetupScrollFreeze(0, 1);
    igTableSetupColumn("Artist", ImGuiTableColumnFlags_DefaultSort, 0, 0);
    igTableSetupColumn("Album", ImGuiTableColumnFlags_None, 0, 0);
    igTableSetupColumn("Track", ImGuiTableColumnFlags_None, 0, 0);
    igTableHeadersRow();

    ImGuiTableSortSpecs *sort_specs = igTableGetSortSpecs();
    if (sort_specs && sort_specs->SpecsDirty) {

      // Perform sorting based on the sort specs
      qsort_r(songs, song_count, sizeof(struct Song), (void *)sort_specs->Specs,
              compare_songs); // qsort_r is used for passing extra argument
      sort_specs->SpecsDirty = false;
    }

    for (int row = 0; row < song_count; row++) {

      if (!filtered_song(filter, row)) {
        continue;
      }

      if (songs[row].Track) {
        igTableNextRow(ImGuiTableRowFlags_None, 0.0F);
      }
      igTableSetColumnIndex(0);
      igText("%s", songs[row].Artist);
      igTableSetColumnIndex(1);
      igText("%s", songs[row].Album);
      igTableSetColumnIndex(2);
      if (igSelectable_Bool(songs[row].Track, selected_song == &songs[row],
                            ImGuiSelectableFlags_SpanAllColumns,
                            (ImVec2){0, 0})) {
        if (igIsKeyDown_Nil(ImGuiKey_LeftShift)) {
          push_to_tail_queue(&playqueue_head, &songs[row]);
        } else {
          selected_song = &songs[row]; // Update selected row
          push_to_head_queue(&playqueue_head, &songs[row]);
          load_song_from_queue();
        }
      }
    }

    // igEndChild();
    igEndTable();
  }
}

void draw_queue(struct playqueue_tq *queue, char *label) {
  static ImGuiTableFlags flags =
      ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg;

  if (igBeginTable(label, 3, flags,
                   (ImVec2){0, igGetWindowHeight() -
                                   igGetTextLineHeightWithSpacing() * 8},
                   0)) {

    igTableSetupScrollFreeze(0, 1);
    igTableSetupColumn("Artist", ImGuiTableColumnFlags_DefaultSort, 0, 0);
    igTableSetupColumn("Album", ImGuiTableColumnFlags_None, 0, 0);
    igTableSetupColumn("Track", ImGuiTableColumnFlags_None, 0, 0);
    igTableHeadersRow();

    struct Song *cur_song = NULL;

    size_t pos = 0;
    TAILQ_FOREACH(cur_song, queue, songs) {
      igTableNextRow(ImGuiTableRowFlags_None, 0.0f);
      igTableSetColumnIndex(0);
      igText("%s", cur_song->Artist);
      igTableSetColumnIndex(1);
      igText("%s", cur_song->Album);
      igTableSetColumnIndex(2);
      if (igSelectable_Bool(cur_song->Track, false,
                            ImGuiSelectableFlags_SpanAllColumns,
                            (ImVec2){0, 0})) {
        skip_to_song(queue, cur_song, pos);
        load_song_from_queue();
      }
      pos++;
    }

    // igEndChild();
    igEndTable();
  }
}

void draw_tabs(void) {
  ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
  ImGuiTabItemFlags tab_item_flags = ImGuiTabItemFlags_NoCloseButton;
  bool yes = true;
  if (igBeginTabBar("MyTabBar", tab_bar_flags)) {
    if (igBeginTabItem("Tracks", &yes, tab_item_flags)) {
      draw_tracks_list();
      igEndTabItem();
    }
    if (igBeginTabItem("Albums", NULL, tab_item_flags)) {
      draw_albums_list();
      igEndTabItem();
    }
    if (igBeginTabItem("Up Next", NULL, tab_item_flags)) {
      draw_queue(&playqueue_head, "Up Next");
      igEndTabItem();
    }
    if (igBeginTabItem("History", NULL, tab_item_flags)) {
      draw_queue(&playhistory_head, "History");
      igEndTabItem();
    }
    igEndTabBar();
  }
}

static void frame(void) {

  // ImGuiIO *io = igGetIO();
  // ImFontConfig *cfg = NULL;
  //
  // ImFont *font = ImFontAtlas_AddFontFromFileTTF(
  //     io->Fonts,
  //     "/Users/znschaffer/src/plyr/resources/fonts/Iosevka-Regular.ttf", 18,
  //     NULL, ImFontAtlas_GetGlyphRangesDefault(io->Fonts));
  // ImFontAtlas_Build(io->Fonts);

  // igPushFont(font);
  simgui_new_frame(&(simgui_frame_desc_t){
      .width = sapp_width(),
      .height = sapp_height(),
      .delta_time = sapp_frame_duration(),
      .dpi_scale = sapp_dpi_scale(),
  });

  update_audio();

  /*=== UI CODE STARTS HERE ===*/
  igSetNextWindowPos((ImVec2){0, 0}, ImGuiCond_Once, (ImVec2){0, 0});
  igSetNextWindowSize((ImVec2){sapp_width(), sapp_height()}, ImGuiCond_None);
  igBegin("Hello Dear ImGui!", 0,
          ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration |
              ImGuiWindowFlags_NoMove);

  if (igButton("Open Music Directory", (ImVec2){0, 0})) {
    nfdchar_t res = NFD_PickFolder(NULL, &music_dir);
    if (res == NFD_OKAY) {
      if (song_count > 0) {
        pause_song();
        current_song = NULL;

        if (sound_initialized) {
          ma_sound_uninit(&current_sound);
          sound_initialized = false;
        }

        // In the future - find a way to append
        clear_queue(&playqueue_head);
        free_songs();
        free_albums();
        song_count = 0;
        album_count = 0;
      }

      load_music_from_dir(music_dir);
    }
  }

  // printf("music_dir buf: %s\n", music_dir);
  // file picker somehow
  // maybe just input box?
  // then load all songs from there - run them through threaded TagLib calls
  // fill the lis

  draw_tabs();
  draw_timeline();
  draw_controls();

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
  free_albums();
  free(music_dir);
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
      .window_title = "plyr",
      .width = 800,
      .height = 600,
      .icon.sokol_default = false,
      .logger.func = slog_func,
  };
}
