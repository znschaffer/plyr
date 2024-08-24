#include <libgen.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <taglib/tag_c.h>

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
bool pause = false;
char *play_status = "▶";
char *pause_status = "⏸";

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
    isMusicLoaded = true;
    PlayMusicStream(currentMusic);
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
}

void DrawUIElements(int screenWidth, int screenHeight) {
  DrawRectangle(20, screenHeight - 20 - 12, screenWidth - 40, 12, LIGHTGRAY);
  DrawRectangle(20, screenHeight - 20 - 12, (int)timePlayed, 12, MAROON);
  DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, GRAY);

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

  char *status = pause ? pause_status : play_status;
  DrawTextEx(
      ft, status,
      (Vector2){screenWidth - 20 - MeasureTextEx(ft, status, FONT_SIZE, 1).x,
                screenHeight - 40 - 12},
      FONT_SIZE, 1, BLACK);
}

void UpdatePlaybackStatus() {
  if (IsKeyDown(KEY_SPACE)) {
    StopMusicStream(currentMusic);
    PlayMusicStream(currentMusic);
    pause = false;
  }

  if (IsKeyPressed(KEY_P)) {
    pause = !pause;
    if (pause)
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

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "PLYR");
  InitAudioDevice();
  SetTargetFPS(60);

  ft = LoadFontEx("./resources/fonts/Iosevka-Regular.ttf", 32, NULL, 40000);
  if (!ft.texture.id) {
    printf("Failed to load font\n");
    return -1;
  }

  audioFiles = LoadDirectoryFilesEx("/Users/znschaffer/Music/Music", ".mp3", 1);
  LoadAudioMetadata(); // Preload metadata

  while (!WindowShouldClose()) {
    UpdatePlaybackStatus();
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawScrollableList(
        (Rectangle){20, 20, screenWidth - 40, screenHeight - 100});
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
