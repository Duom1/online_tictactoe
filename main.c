#include "online.h"
#include "tictactoe.h"
#include <raylib.h>

// #ifdef PLATFORM_WEB
// #include <emscripten/emscripten.h>
// #endif

#define TARGET_FPS 60

enum Game_state {
  GAME_MENU,
  GAME_MENU_ONLINE,
  GAME_LOCAL,
  GAME_ONLINE,
};

void updateDrawFrame(void) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  EndDrawing();
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "tictactoe");

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
