#ifndef LINE_OPERATIONS_H
#define LINE_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "grep_functionality.h"

bool is_exp_in_line(char* line, char* exp, Grep* grep);

void to_lower(char* line);

ssize_t read_line(char** line_buf, FILE* file, bool is_file);
#endif 
