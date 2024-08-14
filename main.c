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

#include "grid.h"
button_t *placement_grid[BOARD_SIZE] = {
    &place_0, &place_1, &place_2, &place_3, &place_4,
    &place_5, &place_6, &place_7, &place_8,
};

char charX[] = "X";
char charO[] = "O";
char textUnknown[] = "Unknown";

int player_turn = PLAYER_1;
int last_to_win = PLAYER_NONE;
board_t board;

void update_draw_frame(void) {
  mouse_pos = GetMousePosition();
  switch (game_state) {
  case GAME_MENU:
    if (is_button_pressed(local_play_btn, mouse_pos)) {
      game_state = GAME_LOCAL;
    } else if (is_button_pressed(online_play_btn, mouse_pos)) {
      game_state = GAME_MENU_ONLINE;
    }
    break;
  case GAME_LOCAL:
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      for (int i = 0; i < BOARD_SIZE; ++i) {
        if (is_button_pressed(*placement_grid[i], mouse_pos)) {
          if (player_turn == PLAYER_1) {
            if (place_piece(board, i, PLAYER_1)) {
              placement_grid[i]->text = charX;
              player_turn = PLAYER_2;
            }
          } else if (player_turn == PLAYER_2) {
            if (place_piece(board, i, PLAYER_2)) {
              placement_grid[i]->text = charO;
              player_turn = PLAYER_1;
            }
          }
          int winner = check_winner(board);
          if (winner != PLAYER_NONE) {
            player_turn = PLAYER_1;
            last_to_win = winner;
            for (int i = 0; i < BOARD_SIZE; ++i) {
              placement_grid[i]->text = NULL;
            }
            zero_board(board);
          }
        }
      }
    }
    break;
  default:
    break;
  }

  BeginDrawing();
  ClearBackground(RAYWHITE);
  char winner_text[20];
  char *winner_tempate = "Winner %s";
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
    if (last_to_win == PLAYER_NONE) {
      DrawText("Local game", 10, 10, 60, GREEN);
    } else {
      switch (last_to_win) {
      case PLAYER_1:
        sprintf(winner_text, winner_tempate, charX);
        break;
      case PLAYER_2:
        sprintf(winner_text, winner_tempate, charO);
        break;
      default:
        sprintf(winner_text, winner_tempate, textUnknown);
        break;
      }
      DrawText(winner_text, 10, 10, 60, GREEN);
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
      draw_button(*placement_grid[i]);
    }
    break;
  default:
    DrawText("something went", 10, 10, 80, RED);
    DrawText("wrong", 10, 90, 80, RED);
  }
  DrawFPS(20, 100);
  EndDrawing();
}

int main(void) {
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(original_size.x, original_size.y, "tictactoe");
  SetExitKey(KEY_NULL);

  auto_scale(&online_play_btn);
  auto_scale(&local_play_btn);
  zero_board(board);

  // #ifdef PLATFORM_WEB
  //   emscripten_set_main_loop(updateDrawFrame, TARGET_FPS, 1);
  // #else
  SetTargetFPS(TARGET_FPS);
  while (!WindowShouldClose()) {
    update_draw_frame();
  }
  // #endif

  CloseWindow();

  return 0;
}
