#ifndef INCLUDE_ONLINE_H_
#define INCLUDE_ONLINE_H_

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

// both fucntions retun 0 if the operarion was successfull
int server_setup(struct Online *online);
int client_setup(struct Online *online, char *address);

#endif // INCLUDE_ONLINE_H_
