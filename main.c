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

int game_state = GAME_MENU;
online_t online;
Vector2 original_size = {800, 800};
Vector2 mouse_pos;

void updateDrawFrame(void) {
  mouse_pos = GetMousePosition();

  BeginDrawing();
  ClearBackground(RAYWHITE);
  switch (game_state) {
  case GAME_MENU:
    DrawText("Tic Tac Toe", 10, 10, 60, GREEN);
    break;
  default:
    DrawText("something went wrong", 10, 10, 80, RED);
  }
  EndDrawing();
}

int main(void) {
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(original_size.x, original_size.y, "tictactoe");

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
