#include "tictactoe.h"
#include <stdio.h>

// This function uses board_t instead of board_t *
// because it will decay into a pointer regardless.
void fprint_board(FILE *file, board_t board) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    fprintf(file, "%i, ", board[i]);
    if (i == 2 || i == 5) {
      fprintf(file, "\n");
    }
  }
  fprintf(file, "\n");
};
