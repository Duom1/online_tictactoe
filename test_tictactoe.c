#include "tictactoe.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// clang-format off
int main(void) {
  board_t board_1 = {
                     PLAYER_1, PLAYER_1, PLAYER_1, 
                     0, 0, 0, 
                     0, 0, 0
                    };
  fprint_board(stdout, board_1);
  assert(check_winner(board_1) == PLAYER_1);
  fprintf(stdout, "passed test n. 1\n");

  board_t board_2 = {
                     0, 0, 0, 
                     PLAYER_2, PLAYER_2, PLAYER_2, 
                     0, 0, 0
                    };
  fprint_board(stdout, board_2);
  assert(check_winner(board_2) == PLAYER_2);
  fprintf(stdout, "passed test n. 2\n");

  board_t board_3 = {
                     0, 0, 0, 
                     0, 0, 0, 
                     PLAYER_2, PLAYER_2, PLAYER_2
                    };
  fprint_board(stdout, board_3);
  assert(check_winner(board_3) == PLAYER_2);
  fprintf(stdout, "passed test n. 3\n");

  board_t board_4 = {
                     PLAYER_1, 0, 0, 
                     PLAYER_1, 0, 0, 
                     PLAYER_1, 0, 0
                    };
  fprint_board(stdout, board_4);
  assert(check_winner(board_4) == PLAYER_1);
  fprintf(stdout, "passed test n. 4\n");

  board_t board_5 = {
                     0, PLAYER_1, 0, 
                     0, PLAYER_1, 0, 
                     0, PLAYER_1, 0
                    };
  fprint_board(stdout, board_5);
  assert(check_winner(board_5) == PLAYER_1);
  fprintf(stdout, "passed test n. 5\n");

  board_t board_6 = {
                     0, 0, PLAYER_2, 
                     0, 0, PLAYER_2, 
                     0, 0, PLAYER_2
                    };
  fprint_board(stdout, board_6);
  assert(check_winner(board_6) == PLAYER_2);
  fprintf(stdout, "passed test n. 6\n");

  board_t board_7 = {
                     PLAYER_2, 0, 0, 
                     0, PLAYER_2, 0, 
                     0, 0, PLAYER_2
                    };
  fprint_board(stdout, board_7);
  assert(check_winner(board_7) == PLAYER_2);
  fprintf(stdout, "passed test n. 7\n");

  board_t board_8 = {
                     0, 0, PLAYER_2, 
                     0, PLAYER_2, 0, 
                     PLAYER_2, 0, 0 
                    };
  fprint_board(stdout, board_8);
  assert(check_winner(board_8) == PLAYER_2);
  fprintf(stdout, "passed test n. 8\n");

  return EXIT_SUCCESS;
}
// clang-format on
