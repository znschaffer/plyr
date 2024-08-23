#include <libgen.h>
#include <raylib.h>
#include <stdio.h>
#include <taglib/tag_c.h>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 150;

  InitWindow(screenWidth, screenHeight, "PLYR");
  Font ft = LoadFont("./resources/fonts/Go-Mono.ttf");

  char *status;
  InitAudioDevice();

  char *song_name = "Amor Satyr & Siu Mata - AHE.mp3";

  char *song_path;

  asprintf(&song_path, "resources/%s", song_name);

  float timePlayed = 0.0f;

  bool pause = false;
  FilePathList audio_files =
      LoadDirectoryFilesEx("/Users/znschaffer/Music/Music", ".mp3", 1);

  size_t song_idx = 0;
  Music music = LoadMusicStream(audio_files.paths[0]);
  music.looping = true;

  TagLib_File *file = taglib_file_new(audio_files.paths[0]);
  TagLib_Tag *tag;
  if (file) {
    tag = taglib_file_tag(file);
  }
  PlayMusicStream(music);
  SetTargetFPS(60);
  char *play_status = "▶";
  char *pause_status = "⏸";

  while (!WindowShouldClose()) {
    UpdateMusicStream(music);
    timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music) *
                 (float)(screenWidth - 40);
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (IsKeyDown(KEY_SPACE)) {
      StopMusicStream(music);
      PlayMusicStream(music);
      pause = false;
    }

    if (IsKeyPressed(KEY_P)) {
      pause = !pause;
      if (pause)
        PauseMusicStream(music);
      else
        ResumeMusicStream(music);
    }

    if (IsKeyDown(KEY_RIGHT)) {
      song_idx = (song_idx + 1) % audio_files.count;
      music = LoadMusicStream(audio_files.paths[song_idx]);
      file = taglib_file_new(audio_files.paths[song_idx]);
      tag = taglib_file_tag(file);
      PlayMusicStream(music);
    } else if (IsKeyDown(KEY_LEFT) && song_idx > 0) {
      song_idx = (song_idx - 1) % audio_files.count;
      music = LoadMusicStream(audio_files.paths[song_idx]);
      file = taglib_file_new(audio_files.paths[song_idx]);
      tag = taglib_file_tag(file);
      PlayMusicStream(music);
    }

    DrawRectangle(20, screenHeight - 20 - 12, screenWidth - 40, 12, LIGHTGRAY);
    DrawRectangle(20, screenHeight - 20 - 12, (int)timePlayed, 12, MAROON);
    DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, GRAY);

    const char *timestamp =
        TextFormat("%02d:%02d", (int)GetMusicTimePlayed(music) / 60,
                   (int)GetMusicTimePlayed(music) % 60);

    char *title = taglib_tag_title(tag);
    char *artist = taglib_tag_artist(tag);

    const char *info_line = TextFormat("%s - %s", artist, title);

    DrawTextEx(ft, timestamp, (Vector2){20, (float)screenHeight - 40 - 12}, 16,
               1, BLACK);

    const int textWidth = (int)MeasureTextEx(ft, info_line, 16, 1).x;

    DrawTextEx(ft, info_line,
               (Vector2){((float)screenWidth / 2) - ((float)textWidth / 2),
                         (float)screenHeight - 40 - 12},
               16, 1, BLACK);

    if (pause) {
      status = pause_status;
    } else {
      status = play_status;
    }

    DrawTextEx(ft, status,
               (Vector2){screenWidth - 20 - MeasureTextEx(ft, status, 16, 1).x,
                         screenHeight - 40 - 12},
               16, 1, BLACK);
    EndDrawing();
  }

  UnloadFont(ft);
  taglib_tag_free_strings();
  taglib_file_free(file);
  UnloadMusicStream(music);

  CloseAudioDevice();

  CloseWindow();

  return 0;
}
