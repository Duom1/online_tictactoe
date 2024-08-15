#include "online.h"
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

  char data = 'j';

  send(online.sock, &data, 1, 0);

  close(online.sock);
  return EXIT_SUCCESS;
}
