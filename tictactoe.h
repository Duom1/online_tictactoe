#ifndef INCLUDE_TITACTOE_H_
#define INCLUDE_TITACTOE_H_

#include <inttypes.h>
#include <stdio.h>

#define BOARD_SIZE 9

typedef int board_t[BOARD_SIZE];

void fprint_board(FILE *file, board_t board);

#endif // INCLUDE_TITACTOE_H_
