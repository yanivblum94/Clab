#ifndef SOCKETS_H
#define SOCKETS_H

#define SERVER_SOCKET_TYPE 'c'
#define HTTP_SOCKET_TYPE 'h'
#define BUFFER_BLOCK 100
#define NO_BINDING -1

int InitSocket(char sockType);
void GetMessageFromSocket(int connectedSocket, int expectedEnds, char* buffer);

#endif
