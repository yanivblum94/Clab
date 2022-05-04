#ifndef SOCKETS_H
#define SOCKETS_H

#define BUFFER_BLOCK 120

int InitSocket(char sockType);
void GetMessageFromSocket(int connectedSocket, int expectedEnds, char* buffer);

#endif
