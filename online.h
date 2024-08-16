#ifndef INCLUDE_ONLINE_H_
#define INCLUDE_ONLINE_H_

#include "tictactoe.h"
#include <arpa/inet.h>
#include <stdbool.h>

#define DEFAULT_PORT 12055

// I want there to be a struct that i can store in my main
// program that i can call functions on and send or recieve
// data from the server or client.

typedef struct Online {
  bool is_server;
  int sock;
  int new_connection;
  struct sockaddr_in address;
  socklen_t addrlen;
} online_t;

// all fucntions retun 0 if the operarion was successfull
// sets up the online variable for server
int server_setup(online_t *online);
// sets up the online variable for client
int client_setup(online_t *online, char *address);
// sends the board variable to online.sock
int send_board(online_t *online, board_t board);
// recieves board to the board variable
// this returns waht ever the recv function returns
int recv_board(online_t *online, board_t board);
// make a socket non blocking
void make_non_blocking(int fd);

#endif // INCLUDE_ONLINE_H_
