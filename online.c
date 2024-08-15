#include "online.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int server_setup(struct Online *online) {
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

int client_setup(struct Online *online, char *address) {
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

  if (connect(online->sock, (struct sockaddr *)&online->address,
              online->addrlen) < 0) {
    ret = 5;
    printf("failed to connect");
    goto return_from_func;
  }

return_from_func:
  return ret;
}
