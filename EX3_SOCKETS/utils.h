#ifndef UTILS_H
#define UTILS_H

#define SERVERS_PORT_FILE "server_port"
#define HTTP_PORT_FILE "http_port"
#define SERVER_SOCKET_TYPE 'c'

int GetValidPort();
void WriteOutputPortFile(int port, char sockType);
int GetMessageLen(const char* message, int expectedEnds);
int CountEndMsgAppearences(const char* buffer, int len);

#endif