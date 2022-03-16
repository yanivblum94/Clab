#ifndef LINE_OPERATIONS_H
#define LINE_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_exp_in_line(char* line, char* exp);

void to_lower(char* line);

int read_line(char* line_buf, FILE* file, bool is_file);
#endif 