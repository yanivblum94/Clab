#include "grep_functionality.h"
#include "line_operations.h"

bool contains_file_name(int argc, char* argv[]) {
	if (strcmp(argv[argc - 1], MINUS_B) == 0 || strcmp(argv[argc - 1], MINUS_C) == 0 || strcmp(argv[argc - 1], MINUS_I) == 0 ||
		strcmp(argv[argc - 1], MINUS_N) == 0 || strcmp(argv[argc - 1], MINUS_V) == 0 || strcmp(argv[argc - 1], MINUS_X) == 0 ||
		strcmp(argv[argc - 2], MINUS_A) == 0 || strcmp(argv[argc - 2], MINUS_E) == 0) {
		return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	bool is_file;
	char* line_buf = NULL;
	int line_len = 0;
	FILE* input_file;
	Grep *grep = malloc(sizeof(struct Grep_struct));
	init_grep(argc, argv, grep);
	if (grep->is_i)
		to_lower(grep->exp);
	is_file = contains_file_name(argc, argv);
	if (is_exp_in_line)
		input_file = fopen(argv[argc-1], "r");
	if (input_file == NULL) {
		printf("error in open file");
		return -1;
	}
	line_len = read_line(line_buf, input_file, is_file);
	while (line_len != -1) {
		if (grep->is_i)
			to_lower(line_buf);
		bool exp_in_line = is_exp_in_line(line_buf, grep->exp);
		handle_grep(line_buf, exp_in_line, grep);
		line_len = read_line(line_buf, input_file, is_file);
	}
	return 0;
}