#include "tictactoe.h"
#include <stdbool.h>
#include <stdio.h>

bool place_piece(board_t board, int place, int player);

int check_winner(board_t board) {
  for (int i = PLAYER_1; i <= PLAYER_2; ++i) {
    if (board[0] == i && board[1] == i && board[2] == i) {
      return i;
    } else if (board[3] == i && board[4] == i && board[5] == i) {
      return i;
    } else if (board[6] == i && board[7] == i && board[8] == i) {
      return i;
    } else if (board[0] == i && board[3] == i && board[6] == i) {
      return i;
    } else if (board[1] == i && board[4] == i && board[7] == i) {
      return i;
    } else if (board[2] == i && board[5] == i && board[8] == i) {
      return i;
    } else if (board[0] == i && board[4] == i && board[8] == i) {
      return i;
    } else if (board[2] == i && board[4] == i && board[6] == i) {
      return i;
    }
  }
  return PLAYER_NONE;
}

void fprint_board(FILE *file, board_t board) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    fprintf(file, "%i, ", board[i]);
    if (i == 2 || i == 5) {
      fprintf(file, "\n");
    }
  }
  fprintf(file, "\n");
};
