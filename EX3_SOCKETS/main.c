#include "sockets.h"
#include "utils.h"
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define FAILURE_CODE 0
#define SUCCESS_CODE 1
#define SERVERS_NUMBER 3
#define HTTP_SOCKET_TYPE 'h'

int CheckForSuccess(int res, char* msg)
{
  if (res < 0) {
    printf("ERROR: %s", msg);
    return FAILURE_CODE;
  }
  return SUCCESS_CODE;
}

int main()
{
  int servers_socket, http_socket, server[SERVERS_NUMBER], client, i = 0, msgLen = 0;
  char *clientMessage, *responseMessage;
  srand(time(0));
  servers_socket = InitSocket(SERVER_SOCKET_TYPE);
  if (CheckForSuccess(servers_socket, "Socket init failed") != 1) {
    return FAILURE_CODE;
  }
  listen(servers_socket, SERVERS_NUMBER);
  http_socket = InitSocket(HTTP_SOCKET_TYPE);
  if (CheckForSuccess(http_socket, "Socket init failed") != 1) {
    return FAILURE_CODE;
  }
  listen(http_socket, 1);
  for (i = 0; i < SERVERS_NUMBER; i++) {
    server[i] = accept(servers_socket, NULL, NULL);
  }
  while (true) {
    if (i >= SERVERS_NUMBER) {
      i = 0;
    }
    clientMessage = (char*)malloc(BUFFER_BLOCK);
    client = accept(http_socket, NULL, NULL);
    GetMessageFromSocket(client, 1, clientMessage);
    msgLen = GetMessageLen(clientMessage, 1);
    if (CheckForSuccess(msgLen, "No end of msg found") != 1) {
      return FAILURE_CODE;
    }
    send(server[i], clientMessage, msgLen, 0);

    responseMessage = (char*)malloc(BUFFER_BLOCK);
    GetMessageFromSocket(server[i], 2, responseMessage);
    msgLen = GetMessageLen(responseMessage, 2);
    if (CheckForSuccess(msgLen, "No end of msg found") != 1) {
      return FAILURE_CODE;
    }
    send(client, responseMessage, msgLen, 0);
    free(clientMessage);
    free(responseMessage);
    close(client);
    i++;
  }

  return SUCCESS_CODE;
}