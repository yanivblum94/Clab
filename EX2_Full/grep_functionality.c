#include "grep_functionality.h"

void init_grep(int argc, char* argv[], Grep* grep, bool is_file) {
	int i;
	grep->is_A = false;
	grep->A_num =0;
	grep->is_b = false;
	grep->is_c = false;
	grep->is_i = false;
	grep->is_n = false;
	grep->is_v = false;
	grep->is_x = false;
	grep->is_E = false;
	grep->argv_exp = -1;
	for(i = 1; i < argc; i++) {
    //printf("%s\n",  argv[i]);
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
			grep->argv_exp = ++i;
			continue;
		}
		else if(is_file && i == argc-1){
			continue;
		}
   else{
     grep->argv_exp = i;
   }
	}
}


void handle_grep(char* line_buf, bool exp_in_line, Grep* grep, int lines_count, int bytes_count) {
	if (exp_in_line) {
    if(grep->is_n)
      printf("%d:\t", lines_count);
    if(grep->is_b)
      printf("%d:\t", bytes_count);
		printf("%s", line_buf);
   }
}