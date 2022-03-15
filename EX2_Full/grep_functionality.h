#ifndef GREP_FUNCTIONALITY_H
#define GREP_FUNCTIONALITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
	char* E_exp;
	char* file_name;
} Grep;

void init_grep(int argc, char *argv[], Grep* grep);

#endif 



