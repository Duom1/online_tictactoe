#include "online.h"
#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  online_t online;
  char *address_str = "127.0.0.1";
  if (client_setup(&online, address_str) != 0) {
    printf("failed server_setup()\n");
  }

  board_t board = {PLAYER_NONE, PLAYER_NONE, PLAYER_1,    PLAYER_NONE, PLAYER_1,
                   PLAYER_NONE, PLAYER_1,    PLAYER_NONE, PLAYER_NONE};

  printf("sending this board:\n");
  fprint_board(stdout, board);

  send_board(&online, board);

  close(online.sock);
  return EXIT_SUCCESS;
}
