#include "grep_functionality.h"

void init_grep(int argc, char* argv[], Grep* grep) {
	for (int i = 1; i < argc-1; i++) {
		if (strcmp(argv[i], MINUS_A) == 0) {
			grep->is_A = true;
			grep->A_num = atoi(argv[++i]);
			continue;
		}
		else if(strcmp(argv[i], MINUS_B) == 0) {
			grep->is_b = true;
			continue;
		}
		else if (strcmp(argv[i], MINUS_C) == 0) {
			grep->is_c = true;
			continue;
		}
		else if (strcmp(argv[i], MINUS_I) == 0) {
			grep->is_i = true;
			continue;
		}
		else if (strcmp(argv[i], MINUS_N) == 0) {
			grep->is_n = true;
			continue;
		}
		else if (strcmp(argv[i], MINUS_V) == 0) {
			grep->is_v = true;
			continue;
		}
		else if (strcmp(argv[i], MINUS_X) == 0) {
			grep->is_x = true;
			continue;
		}
		else if (strcmp(argv[i], MINUS_E) == 0) {
			grep->is_E = true;
			grep->exp = argv[++i];
			continue;
		}
		else {
			grep->exp = argv[i];
		}
	}
}


void handle_grep(char* line_buf, bool exp_in_line, Grep* grep) {
	if (exp_in_line) {
		printf("%s", line_buf);
	}
	else {
		if (grep->is_v)
			printf("%s", line_buf);
	}
}