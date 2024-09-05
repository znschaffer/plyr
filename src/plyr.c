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
#include "audio.h"
#include "cimgui.h"
#include "miniaudio.h"
#include "nfd.h"
#include "queue.h"
#include "sokol_imgui.h"
#include "song.h"
#include "ui.h"

static struct {
  sg_pass_action pass_action;
} __attribute__((aligned(128))) state;

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

static void frame(void) {

  // still need to figure out font rendering...
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
