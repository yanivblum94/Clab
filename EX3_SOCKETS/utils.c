#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NO_END_FOUND_CODE -1
#define LF_CODE 10
#define CR_CODE 13
#define MIN_PORT 1024
#define MAX_PORT 64000


int GetValidPort()
{
    int res = rand();
    while (res > MAX_PORT || res < MIN_PORT) {
        res = rand();
    }
    return res;
}

void WriteOutputPortFile(int port, char sockType)
{
    FILE* fp;

    if (sockType == SERVER_SOCKET_TYPE) {
        fp = fopen(SERVERS_PORT_FILE, "w");
    }
    else {
        fp = fopen(HTTP_PORT_FILE, "w");
    }

    if (fp == NULL) {
        printf("ERROR: cannot open file.");
        return;
    }

    fprintf(fp, "%d", port);
    fclose(fp);
}

int GetMessageLen(const char* message, int expectedEnds)
{
    int endsCounter = 0;

    for(int i=0; i < strlen(message) - 3; i++) {
        if (FindEndMatch(message, i)) {
            endsCounter++;
        }
        if (endsCounter == expectedEnds) {
            return i + 4;
        }
    }
    return NO_END_FOUND_CODE;
}

bool FindEndMatch(const char* buffer, int indx) {
    if (buffer[indx] == CR_CODE && buffer[indx + 1] == LF_CODE && buffer[indx + 2] == CR_CODE && buffer[indx + 3] == LF_CODE) {
        return true;
    }
    return false;
}

int CountEndMsgAppearences(const char* buffer, int len)
{
    int i, res = 0;
    for (i = 0; i < len - 3; i++) {
        if (FindEndMatch(buffer, i)) {
            res++;
        }
    }
    return res;
}