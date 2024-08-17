#include "online.h"
#include "tictactoe.h"
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int server_setup(online_t *online) {
  int ret = 0;
  online->addrlen = sizeof(online->address);

  if ((online->sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    ret = 1;
    fprintf(stderr, "failed to create socket\n");
    goto return_from_func;
  }

  online->address.sin_family = AF_INET;
  online->address.sin_addr.s_addr = INADDR_ANY;
  online->address.sin_port = htons(DEFAULT_PORT);

  if (bind(online->sock, (struct sockaddr *)&online->address, online->addrlen) <
      0) {
    int err = errno;
    ret = 2;
    fprintf(stderr, "failed to bind with code: %i\n", err);
    goto return_from_func;
  }

  if (listen(online->sock, 1) < 0) {
    ret = 3;
    fprintf(stderr, "failed to listen\n");
    goto return_from_func;
  }

return_from_func:
  return ret;
}

int client_setup(online_t *online, char *address) {
  int ret = 0;
  online->addrlen = sizeof(online->address);
  if ((online->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    ret = 1;
    fprintf(stderr, "failed to create socket\n");
    goto return_from_func;
  }

  online->address.sin_family = AF_INET;
  online->address.sin_port = htons(DEFAULT_PORT);

  if (inet_pton(AF_INET, address, &online->address.sin_addr) <= 0) {
    ret = 4;
    fprintf(stderr, "failed to convert address\n");
    goto return_from_func;
  }

return_from_func:
  return ret;
}

int send_board(online_t *online, board_t board) {
  int ret = 0;
  board_t network_bo;
  for (int i = 0; i < BOARD_SIZE; ++i) {
    network_bo[i] = htonl(board[i]);
  }
  send(online->sock, &network_bo, sizeof(board_t), 0);
  return ret;
}

int recv_board(online_t *online, board_t board) {
  board_t network_bo;
  int ret = recv(online->new_connection, &network_bo, sizeof(board_t), 0);
  if (ret != 0 && ret > 0) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
      board[i] = ntohl(network_bo[i]);
    }
  }
  return ret;
}

void make_non_blocking(int fd) { fcntl(fd, F_SETFL, O_NONBLOCK); }
