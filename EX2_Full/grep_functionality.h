#ifndef GREP_FUNCTIONALITY_H
#define GREP_FUNCTIONALITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MINUS_A "-A"
#define MINUS_B "-b"
#define MINUS_C "-c"
#define MINUS_I "-i"
#define MINUS_N "-n"
#define MINUS_V "-v"
#define MINUS_X "-x"
#define MINUS_E "-E"

typedef struct Grep_struct {
	bool is_A;
	int A_num;
	bool is_b;
	bool is_c;
	bool is_i;
	bool is_n;
	bool is_v;
	bool is_x;
	bool is_E;
	int argv_exp;
} Grep;

void init_grep(int argc, char *argv[], Grep* grep, bool is_file);

void handle_grep(char* line_buf, bool exp_in_line, Grep* grep, int lines_count, int bytes_count);
#endif 



