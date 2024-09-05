#include "ui.h"
#include "audio.h"
#include "cimgui.h"
#include "nfd.h"
#include "queue.h"
#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *status_pause = ">";
const char *status_play = "||";
char *music_dir;

void draw_waveform(void) {

  if (true) {
    return;
  }
  if (audio_data_size == 0 || audio_data == NULL) {
    return;
  }
  ImVec2 size = {-1.0f, -1.0f};
  igPlotLines_FloatPtr("", audio_data, audio_data_size, 0, NULL, -1.0F, 1.0F,
                       size, sizeof(float));
}

void draw_timeline() {
  float time = 0;
  float length = 1;
  int pcm_frame_time = 0;
  unsigned long long pcm_frame_length = 0;

  // waveform decoding - it currently takes way too long to do
  if (sound_initialized == true) {
    time = ma_sound_get_time_in_pcm_frames(&current_sound);
    ma_sound_get_cursor_in_seconds(&current_sound, &time);
    ma_sound_get_length_in_seconds(&current_sound, &length);
    pcm_frame_time = ma_sound_get_time_in_pcm_frames(&current_sound);
    ma_sound_get_length_in_pcm_frames(&current_sound, &pcm_frame_length);
  }

  char *buf = "";

  // igBeginChild_Str("Timeline", (ImVec2){igGetWindowWidth(), 100.f}, false,
  // 0);
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
  // igEndChild();
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

void draw_albums_list() {
  static int selected_row = -1;
  struct Album *selected_album = NULL;
  static ImGuiTableFlags flags =
      ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY |
      ImGuiTableFlags_RowBg | ImGuiTableFlags_Reorderable;
  if (igBeginTable("AlbumTable", 3, flags,
                   (ImVec2){0, igGetWindowHeight() * 0.5}, 0)) {

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
                   (ImVec2){0,igGetWindowHeight() * 0.75}, 0)) {

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

  if (igBeginTable(label, 3, flags, (ImVec2){0, igGetWindowHeight() * 0.5},
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

void draw_open_music_dir(void) {
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
}
