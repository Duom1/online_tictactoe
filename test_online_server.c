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
    fprintf(stderr, "could not accept connection with code: %i\n", err);
    close(online.sock);
    exit(EXIT_FAILURE);
  }

  board_t board;
  make_non_blocking(online.new_connection);
  while (true) {
    int n = recv_board(&online, board);
    if (n != 0 && n > 0) {
      fprintf(stderr, "the board revived by the server:\n");
      fprint_board(stderr, board);
    } else if (n == 0) {
      printf("connection closed\n");
      break;
    }
  }
  close(online.sock);
  return EXIT_SUCCESS;
}
