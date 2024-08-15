#ifndef INCLUDE_TITACTOE_H_
#define INCLUDE_TITACTOE_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define BOARD_SIZE 9
#define PLAYER_1 0x61
#define PLAYER_2 0x62
#define PLAYER_NONE 0x0

typedef int32_t board_t[BOARD_SIZE];

// This function uses board_t instead of board_t *
// because it will decay into a pointer regardless.
void fprint_board(FILE *file, board_t board);
// Return weather or not you can place a piece there
// if it is possible returns true and places it.
bool place_piece(board_t board, int place, int player);
// Returns 0 if not player has won and returns thge player number
// if that player has won
int check_winner(board_t board);
// This function zeroes out the entire board
void zero_board(board_t board);

#endif // INCLUDE_TITACTOE_H_
