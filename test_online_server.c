#include "online.h"
#include "tictactoe.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  online_t online;
  if (server_setup(&online) != 0) {
    printf("failed server_setup()\n");
  }
  online.new_connection =
      accept(online.sock, (struct sockaddr *)&(online.address),
             (socklen_t *)&(online.addrlen));
  int err = errno;
  if (online.new_connection < 0) {
    fprintf(stderr, "%i\n", online.new_connection);
    fprintf(stderr, "could not accept connection with code: %i\n", err);
    close(online.sock);
    exit(EXIT_FAILURE);
  }

  board_t board;
  recv_board(&online, board);

  printf("the board revived by the server:\n");
  fprint_board(stdout, board);

  close(online.sock);
  return EXIT_SUCCESS;
}
