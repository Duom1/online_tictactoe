#include "tictactoe.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// clang-format off
int main(void) {
  int test_counter = 1;
  board_t board_1 = {
                     PLAYER_1, PLAYER_1, PLAYER_1, 
                     0, 0, 0, 
                     0, 0, 0
                    };
  assert(check_winner(board_1) == PLAYER_1);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_2 = {
                     0, 0, 0, 
                     PLAYER_2, PLAYER_2, PLAYER_2, 
                     0, 0, 0
                    };
  assert(check_winner(board_2) == PLAYER_2);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_3 = {
                     0, 0, 0, 
                     0, 0, 0, 
                     PLAYER_2, PLAYER_2, PLAYER_2
                    };
  assert(check_winner(board_3) == PLAYER_2);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_4 = {
                     PLAYER_1, 0, 0, 
                     PLAYER_1, 0, 0, 
                     PLAYER_1, 0, 0
                    };
  assert(check_winner(board_4) == PLAYER_1);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_5 = {
                     0, PLAYER_1, 0, 
                     0, PLAYER_1, 0, 
                     0, PLAYER_1, 0
                    };
  assert(check_winner(board_5) == PLAYER_1);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_6 = {
                     0, 0, PLAYER_2, 
                     0, 0, PLAYER_2, 
                     0, 0, PLAYER_2
                    };
  assert(check_winner(board_6) == PLAYER_2);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_7 = {
                     PLAYER_2, 0, 0, 
                     0, PLAYER_2, 0, 
                     0, 0, PLAYER_2
                    };
  assert(check_winner(board_7) == PLAYER_2);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  board_t board_8 = {
                     0, 0, PLAYER_2, 
                     0, PLAYER_2, 0, 
                     PLAYER_2, 0, 0 
                    };
  assert(check_winner(board_8) == PLAYER_2);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  assert(place_piece(board_8, 2, PLAYER_2) == false);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  assert(place_piece(board_8, 2, PLAYER_1) == false);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  assert(place_piece(board_8, 1, PLAYER_1));
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  assert(place_piece(board_8, 4, PLAYER_1) == false);
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  assert(place_piece(board_8, 3, PLAYER_1));
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  zero_board(board_8);
  for (int i = 0; i < BOARD_SIZE; ++i) {
    assert(board_8[i] == 0);
  }
  fprintf(stdout, "passed test n. %i\n", test_counter++);

  return EXIT_SUCCESS;
}
// clang-format on
