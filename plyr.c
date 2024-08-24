#include <math.h>
#define RINI_IMPLEMENTATION
#include "rini.h"
#include <libgen.h>
#include <pwd.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <taglib/tag_c.h>
#include <unistd.h>
#include <wordexp.h>

#define FONT_SIZE 16
#define SCROLL_SPEED 4

typedef struct {
  char *filename;
  char *artist;
  char *title;
} AudioMetadata;

FilePathList audioFiles;
AudioMetadata *metadataList = NULL;
int scrollOffset = 0;
int selectedIndex = 0;
bool isMusicLoaded = false;
Music currentMusic;

Font ft;
float timePlayed = 0.0f;
bool paused = true;
char *play_status = "⏸";
char *pause_status = "▶";

// Function prototypes
void LoadSelectedMusic();
void DrawScrollableList(Rectangle listRect);
void DrawUIElements(int screenWidth, int screenHeight);
void UpdatePlaybackStatus();
void LoadAudioMetadata();

void LoadSelectedMusic() {
  if (isMusicLoaded) {
    UnloadMusicStream(currentMusic);
    isMusicLoaded = false;
  }

  if (selectedIndex >= 0 && selectedIndex < audioFiles.count) {
    currentMusic = LoadMusicStream(audioFiles.paths[selectedIndex]);
    currentMusic.looping = false;
    isMusicLoaded = true;
    PlayMusicStream(currentMusic);
    paused = false;
  }
}

void LoadAudioMetadata() {
  metadataList =
      (AudioMetadata *)malloc(audioFiles.count * sizeof(AudioMetadata));

  for (int i = 0; i < audioFiles.count; i++) {
    TagLib_File *file = taglib_file_new(audioFiles.paths[i]);
    TagLib_Tag *tag = file ? taglib_file_tag(file) : NULL;

    metadataList[i].filename = basename(audioFiles.paths[i]);
    metadataList[i].artist =
        tag ? strdup(taglib_tag_artist(tag)) : strdup("Unknown Artist");
    metadataList[i].title =
        tag ? strdup(taglib_tag_title(tag)) : strdup("Unknown Title");

    if (file)
      taglib_file_free(file);
  }
}

void DrawScrollableList(Rectangle listRect) {
  BeginScissorMode(listRect.x, listRect.y, listRect.width, listRect.height);
  int itemHeight = FONT_SIZE + 4;
  int visibleItems = listRect.height / itemHeight;

  for (int i = 0; i < visibleItems && (i + scrollOffset) < audioFiles.count;
       i++) {
    int itemIndex = i + scrollOffset;
    Rectangle itemRect = {listRect.x, listRect.y + i * itemHeight,
                          listRect.width, itemHeight};

    if (itemIndex == selectedIndex) {
      DrawRectangleRec(itemRect, LIGHTGRAY);
    }

    char displayText[256];
    snprintf(displayText, sizeof(displayText), "%s - %s",
             metadataList[itemIndex].artist, metadataList[itemIndex].title);

    DrawTextEx(ft, displayText, (Vector2){itemRect.x + 10, itemRect.y + 2},
               FONT_SIZE, 1, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(), itemRect) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      selectedIndex = itemIndex;
      LoadSelectedMusic();
    }
  }

  int mouseWheel = GetMouseWheelMove();
  scrollOffset -= mouseWheel * SCROLL_SPEED;
  if (scrollOffset < 0)
    scrollOffset = 0;
  if (scrollOffset > audioFiles.count - visibleItems)
    scrollOffset = audioFiles.count - visibleItems;

  EndScissorMode();
}

void DrawUIElements(int screenWidth, int screenHeight) {
  Rectangle timebar = {20, screenHeight - 20 - 12, screenWidth - 40, 12};
  DrawRectangleRec(timebar, LIGHTGRAY);
  DrawRectangle(20, screenHeight - 20 - 12, (int)timePlayed, 12, MAROON);
  DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, GRAY);

  if (CheckCollisionPointRec(GetMousePosition(), timebar) &&
      IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

    float time = (GetMousePosition().x - timebar.x) / timebar.width *
                 GetMusicTimeLength(currentMusic);
    SeekMusicStream(currentMusic, time);
  }

  const char *timestamp =
      TextFormat("%02d:%02d", (int)GetMusicTimePlayed(currentMusic) / 60,
                 (int)GetMusicTimePlayed(currentMusic) % 60);
  DrawTextEx(ft, timestamp, (Vector2){20, screenHeight - 40 - 12}, FONT_SIZE, 1,
             BLACK);

  if (isMusicLoaded) {
    char *title = metadataList[selectedIndex].title;
    char *artist = metadataList[selectedIndex].artist;
    const char *info_line = TextFormat("%s - %s", artist, title);
    int textWidth = (int)MeasureTextEx(ft, info_line, FONT_SIZE, 1).x;

    DrawTextEx(
        ft, info_line,
        (Vector2){(screenWidth / 2) - (textWidth / 2), screenHeight - 40 - 12},
        FONT_SIZE, 1, BLACK);
  }

  char *status = paused ? pause_status : play_status;
  Vector2 pause_button_size = MeasureTextEx(ft, status, FONT_SIZE, 1);
  Rectangle pause_button = {screenWidth - 20 - pause_button_size.x,
                            screenHeight - 40 - 12, pause_button_size.x,
                            pause_button_size.y};

  if (CheckCollisionPointRec(GetMousePosition(), pause_button) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

    paused = !paused;
    if (paused)
      PauseMusicStream(currentMusic);
    else
      ResumeMusicStream(currentMusic);
  }
  DrawTextEx(ft, status, (Vector2){pause_button.x, pause_button.y}, FONT_SIZE,
             1, BLACK);
}

void UpdatePlaybackStatus() {
  if (IsKeyDown(KEY_SPACE)) {
    StopMusicStream(currentMusic);
    PlayMusicStream(currentMusic);
    paused = false;
  }

  if (IsKeyPressed(KEY_P)) {
    paused = !paused;
    if (paused)
      PauseMusicStream(currentMusic);
    else
      ResumeMusicStream(currentMusic);
  }

  if (isMusicLoaded) {
    UpdateMusicStream(currentMusic);
    timePlayed = GetMusicTimePlayed(currentMusic) /
                 GetMusicTimeLength(currentMusic) *
                 (float)(GetScreenWidth() - 40);
  }
}

void CheckAndMoveToNextSong() {
  // Ensure the music is loaded and is currently playing
  if (isMusicLoaded) {
    // Get the current playback time and the length of the music
    float timePlayed = GetMusicTimePlayed(currentMusic);
    float timeLength = GetMusicTimeLength(currentMusic);

    // Check if the current playback time is greater than or equal to the length
    if (timePlayed >=
        (timeLength -
         0.1f)) { // Allowing a small tolerance for end of song detection
      // Stop the current music
      StopMusicStream(currentMusic);

      // Move to the next song in the list
      selectedIndex++;
      if (selectedIndex >= audioFiles.count) {
        selectedIndex = 0; // Loop back to the start if at the end
      }

      // Load and play the next song
      LoadSelectedMusic();
    }
  }
}

#define DEFAULT_CONFIG_DIR ".config"

// Function to get the XDG configuration path
const char *get_xdg_config_path(const char *subpath) {
  const char *xdg_config_home = getenv("XDG_CONFIG_HOME");

  if (xdg_config_home) {
    // If XDG_CONFIG_HOME is set, use it
    static char path[1024];
    snprintf(path, sizeof(path), "%s/%s", xdg_config_home, subpath);
    return path;
  } else {
    // If XDG_CONFIG_HOME is not set, use the default location
    struct passwd *pw = getpwuid(geteuid());
    const char *home_dir = pw->pw_dir;
    static char path[1024];
    snprintf(path, sizeof(path), "%s/%s/%s", home_dir, DEFAULT_CONFIG_DIR,
             subpath);
    return path;
  }
}
int main(void) {

  const char *config_path = get_xdg_config_path("plyr/config.ini");
  rini_config config = rini_load_config(config_path);
  char *music_dir = rini_get_config_value_text(config, "music_dir");

  int screenWidth = 800;
  int screenHeight = 600;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "PLYR");
  InitAudioDevice();
  SetTargetFPS(60);

  const char *app_dir = GetApplicationDirectory();
  ft = LoadFontEx(TextFormat("%sresources/fonts/Iosevka-Regular.ttf", app_dir),
                  32, NULL, 40000);
  if (!ft.texture.id) {
    printf("Failed to load font\n");
    return -1;
  }

  printf("MusicDir:%s", music_dir);
  audioFiles = LoadDirectoryFilesEx(music_dir, ".mp3", 1);
  LoadAudioMetadata(); // Preload metadata

  while (!WindowShouldClose()) {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    CheckAndMoveToNextSong(); // Check if song ended and move to next song if
    UpdatePlaybackStatus();
    // needed

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawScrollableList(
        (Rectangle){20, 20, screenWidth - 40, screenHeight - 80});
    DrawUIElements(screenWidth, screenHeight);

    EndDrawing();
  }

  // Cleanup
  for (int i = 0; i < audioFiles.count; i++) {
    free(metadataList[i].artist);
    free(metadataList[i].title);
  }
  free(metadataList);
  UnloadFont(ft);
  UnloadMusicStream(currentMusic);
  UnloadDirectoryFiles(audioFiles);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}
