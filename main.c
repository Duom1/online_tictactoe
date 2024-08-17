#include "online.h"
#include "tictactoe.h"
#include "ui.h"
#include <arpa/inet.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

// #ifdef PLATFORM_WEB
// #include <emscripten/emscripten.h>
// #endif

#define TARGET_FPS 60
#define ORIGINAL_SCREEN_X 800
#define ORIGINAL_SCREEN_Y 800

enum Game_state {
  GAME_MENU = 1,
  GAME_MENU_ONLINE,
  GAME_LOCAL,
  GAME_ONLINE,
};

enum Online_menu_state {
  ONLINE_STATE_NONE = 0,
  ONLINE_WAITING_FOR_CLIENT = 1,
  ONLINE_JOINING_GAME,
  ONLINE_PLAYING
};

Vector2 original_size = {ORIGINAL_SCREEN_X, ORIGINAL_SCREEN_Y};

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
const char back_txt[] = "Back";
button_t back_btn = {(Vector2){20, ORIGINAL_SCREEN_Y - 100},
                     (Vector2){340, 60},
                     (Vector2){0, 0},
                     (Vector2){0, 0},
                     GRAY,
                     GREEN,
                     (char *)back_txt,
                     15};
const char host_txt[] = "Host";
button_t host_btn = {(Vector2){20, 150},
                     (Vector2){340, 100},
                     (Vector2){0, 0},
                     (Vector2){0, 0},
                     GRAY,
                     GREEN,
                     (char *)host_txt,
                     15};
const char join_txt[] = "Join";
button_t join_btn = {(Vector2){20, 300},
                     (Vector2){340, 100},
                     (Vector2){0, 0},
                     (Vector2){0, 0},
                     GRAY,
                     GREEN,
                     (char *)join_txt,
                     15};
ip_box_t input_ip_box = {(Vector2){200, 300},
                         (Vector2){400, 100},
                         (Vector2){205, 305},
                         (Vector2){0, 90},
                         GRAY,
                         GREEN,
                         15,
                         LOCAL_HOST};

online_t online;
int game_state = GAME_MENU;
Vector2 mouse_pos;

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
ip_box_t *selected_input = NULL;
int online_state = ONLINE_STATE_NONE;
int connect_status = -1;

void reset_for_local_game(int *last_to_win, int winner, int *player_turn,
                          button_t **placement_grid, int *board) {
  *player_turn = PLAYER_1;
  *last_to_win = winner;
  for (int i = 0; i < BOARD_SIZE; ++i) {
    placement_grid[i]->text = NULL;
  }
  zero_board(board);
}

void update_draw_frame(void) {
  mouse_pos = GetMousePosition();
  switch (game_state) {
  case GAME_MENU:
    if (is_button_pressed(local_play_btn, mouse_pos)) {
      game_state = GAME_LOCAL;
      reset_for_local_game(&last_to_win, PLAYER_NONE, &player_turn,
                           placement_grid, board);
    } else if (is_button_pressed(online_play_btn, mouse_pos)) {
      game_state = GAME_MENU_ONLINE;
    }
    break;
  case GAME_LOCAL:
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (is_button_pressed(back_btn, mouse_pos)) {
        game_state = GAME_MENU;
      }
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
            reset_for_local_game(&last_to_win, winner, &player_turn,
                                 placement_grid, board);
          }
        }
      }
    }
    break;
  case GAME_MENU_ONLINE:
    if (is_button_pressed(host_btn, mouse_pos)) {
      server_setup(&online);
      online_state = ONLINE_WAITING_FOR_CLIENT;
      game_state = GAME_ONLINE;
      make_non_blocking(online.sock);
    } else if (is_button_pressed(join_btn, mouse_pos)) {
      client_setup(&online, input_ip_box.text);
      online_state = ONLINE_JOINING_GAME;
      game_state = GAME_ONLINE;
      make_non_blocking(online.sock);
    } else if (is_button_pressed(back_btn, mouse_pos)) {
      game_state = GAME_MENU;
    } else if (was_box_cliked(input_ip_box, mouse_pos)) {
      selected_input = &input_ip_box;
    } else if (selected_input != NULL) {
      get_box_input(selected_input);
    }
    break;
  case GAME_ONLINE:
    switch (online_state) {
    case ONLINE_WAITING_FOR_CLIENT:
      online.new_connection =
          accept(online.sock, (struct sockaddr *)&(online.address),
                 (socklen_t *)&(online.addrlen));
      if (!(online.new_connection < 0)) {
        fprintf(stderr, "acceped new connection\n");
        online_state = ONLINE_PLAYING;
      }
      break;
    case ONLINE_JOINING_GAME:
      connect_status = connect(
          online.sock, (struct sockaddr *)&(online.address), online.addrlen);
      if (connect_status == 0) {
        fprintf(stderr, "connected!");
        online_state = ONLINE_PLAYING;
        online.new_connection = online.sock;
      }
    case ONLINE_PLAYING:
      break;
    }

    break;
  default:
    fprintf(stderr, "something went wrong!!!");
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
    draw_button(join_btn);
    draw_button(host_btn);
    draw_button(back_btn);
    draw_IP_box(input_ip_box);
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
    draw_button(back_btn);
    for (int i = 0; i < BOARD_SIZE; ++i) {
      draw_button(*placement_grid[i]);
    }
    break;
  case GAME_ONLINE:
    switch (online_state) {
    case ONLINE_WAITING_FOR_CLIENT:
      DrawText("waiting for other player", 10, 10, 50, GREEN);
      break;
    case ONLINE_JOINING_GAME:
      DrawText("joining game", 10, 10, 50, GREEN);
      break;
    case ONLINE_PLAYING:
      DrawText("playing online", 10, 10, 50, GREEN);
      break;
    }
    break;
  default:
    DrawText("something went", 10, 10, 80, RED);
    DrawText("wrong", 10, 90, 80, RED);
    break;
  }
  DrawFPS(original_size.x - 110, 40);
  EndDrawing();
}

int main(void) {
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(original_size.x, original_size.y, "tictactoe");
  SetExitKey(KEY_NULL);

  auto_scale(&online_play_btn);
  auto_scale(&local_play_btn);
  auto_scale(&back_btn);
  auto_scale(&host_btn);
  auto_scale(&join_btn);
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
