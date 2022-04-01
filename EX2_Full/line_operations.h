#ifndef LINE_OPERATIONS_H
#define LINE_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grep_functionality.h"

#define NO_MATCH_CODE -1
#define MATCH_CODE 1
#define CURR_IDX 0
#define NEXT_IDX 1
#define THIRD_IDX 3
#define FIFTH_INX 5


#define NULL_ASCII 0
#define ROUND_BRACKETS_OPEN_ASCII 40
#define ROUND_BRACKETS_CLOSE_ASCII 41
#define DOT_ASCII 46
#define SQUARE_BRACKETS_OPEN_ASCII 91
#define BACKSLASH_ASCII 92
#define SQUARE_BRACKETS_CLOSE_ASCII 93
#define VERTICAL_LINE_ASCII 124


bool is_exp_in_line(char* line, char* exp, Grep* grep);

void to_lower(char* line);

ssize_t read_line(char** line_buf, FILE* file, bool is_file);
#endif 
