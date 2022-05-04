#include "sockets.h"
#include "utils.h"
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define NO_BINDING -1

bool BindSocket(int port, int sock)
{
  struct sockaddr_in socket_addr;

  socket_addr.sin_family = AF_INET;
  socket_addr.sin_addr.s_addr = INADDR_ANY;
  socket_addr.sin_port = htons(port);

  if (bind(sock, (struct sockaddr*)&socket_addr, sizeof(socket_addr)) < 0) {
    return true;
  }
  return false;
}

int CreateSocket()
{
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == NO_BINDING) {
    return NO_BINDING;
  }
  return sock;
}

int InitSocket(char sockType)
{

  int port, sock = NO_BINDING;
  bool newPort = true;
  sock = CreateSocket();
  if (sock == NO_BINDING) {
      return NO_BINDING;
  }
  do {
    port = GetValidPort();
    newPort = BindSocket(port, sock);
  } while (newPort);

  WriteOutputPortFile(port, sockType);

  return sock;
}

void GetMessageFromSocket(int connectedSocket, int expectedEnds, char* buffer)
{

  int bufferLen = 0, recvDataSize, endsCount;

  while (endsCount != expectedEnds) {

    recvDataSize = recv(connectedSocket, &(buffer[bufferLen]), BUFFER_BLOCK, 0);
    bufferLen += recvDataSize;

    endsCount = CountEndMsgAppearences(buffer, bufferLen);

    buffer = (char*)realloc(buffer, bufferLen + BUFFER_BLOCK);
  }

  return;
}
