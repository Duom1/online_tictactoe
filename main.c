#include "online.h"
#include "tictactoe.h"
#include "ui.h"
#include <raylib.h>
#include <stdio.h>

// #ifdef PLATFORM_WEB
// #include <emscripten/emscripten.h>
// #endif

#define TARGET_FPS 60

enum Game_state {
  GAME_MENU = 1,
  GAME_MENU_ONLINE,
  GAME_LOCAL,
  GAME_ONLINE,
};

online_t online;
int game_state = GAME_MENU;
Vector2 original_size = {800, 800};
Vector2 mouse_pos;

// the sizes for the text have to be auto set using auto_scale()
const char play_txt[] = "Play";
button_t local_play_btn = {(Vector2){20, 200},
                           (Vector2){300, 100},
                           (Vector2){0, 0},
                           (Vector2){0, 0},
                           GRAY,
                           GREEN,
                           (char *)play_txt,
                           15};
const char online_txt[] = "Online";
button_t online_play_btn = {(Vector2){20, 350},
                            (Vector2){340, 100},
                            (Vector2){0, 0},
                            (Vector2){0, 0},
                            GRAY,
                            GREEN,
                            (char *)online_txt,
                            15};

void updateDrawFrame(void) {
  mouse_pos = GetMousePosition();
  switch (game_state) {
  case GAME_MENU:
    if (is_button_pressed(local_play_btn, mouse_pos)) {
      game_state = GAME_LOCAL;
    } else if (is_button_pressed(online_play_btn, mouse_pos)) {
      game_state = GAME_MENU_ONLINE;
    }
    break;
  default:
    break;
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);
  switch (game_state) {
  case GAME_MENU:
    DrawText("Tic Tac Toe", 10, 10, 60, GREEN);
    draw_button(local_play_btn);
    draw_button(online_play_btn);
    break;
  case GAME_MENU_ONLINE:
    DrawText("Online menu", 10, 10, 60, GREEN);
    break;
  case GAME_LOCAL:
    DrawText("Local game", 10, 10, 60, GREEN);
    break;
  default:
    DrawText("something went", 10, 10, 80, RED);
    DrawText("wrong", 10, 90, 80, RED);
  }
  EndDrawing();
}

int main(void) {
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(original_size.x, original_size.y, "tictactoe");
  SetExitKey(KEY_NULL);
  auto_scale(&online_play_btn);
  auto_scale(&local_play_btn);

  // #ifdef PLATFORM_WEB
  //   emscripten_set_main_loop(updateDrawFrame, TARGET_FPS, 1);
  // #else
  SetTargetFPS(TARGET_FPS);
  while (!WindowShouldClose()) {
    updateDrawFrame();
  }
  // #endif

  CloseWindow();

  return 0;
}
