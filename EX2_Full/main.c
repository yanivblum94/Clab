//#pragma warning(disable : 4996)
#include "grep_functionality.h"
#include "line_operations.h"

bool contains_file_name(int argc, char* argv[]) {
	if (argc < 3)
		return false;
	if (strcmp(argv[argc - 1], MINUS_B) == 0 || strcmp(argv[argc - 1], MINUS_C) == 0 || strcmp(argv[argc - 1], MINUS_I) == 0)
		return false;
	else if (strcmp(argv[argc - 1], MINUS_N) == 0 || strcmp(argv[argc - 1], MINUS_V) == 0 || strcmp(argv[argc - 1], MINUS_X) == 0)
		return false;
	else if (strcmp(argv[argc - 2], MINUS_A) == 0 || strcmp(argv[argc - 2], MINUS_E) == 0) {
		return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	bool is_file;
	char* line_buf;
	ssize_t line_len = 0;
	FILE* input_file;
	Grep* grep = malloc(sizeof(struct Grep_struct));
	is_file = contains_file_name(argc, argv);
	//printf("is_file = %d\n", is_file);
	init_grep(argc, argv, grep, is_file);
	//printf("index of exp in argv = %d\n", grep->argv_exp);
	//fflush(stdout);
	//printf("exp = %s\n", argv[grep->argv_exp]);
	if (grep->is_i)
		to_lower(argv[grep->argv_exp]);
	if (is_file) {
		input_file = fopen(argv[argc - 1], "r");
		if (input_file == NULL) {
			printf("error in open file");
			return -1;
		}
	}
	line_len = read_line(&line_buf, input_file, is_file);
	//printf("line_len = %d\n", line_len);
	while (line_len != -1) {
		if (grep->is_i)
			to_lower(line_buf);
		//printf("linebuf= %s exp = %s\n", line_buf, grep->exp);
		//fflush(stdout);
		bool exp_in_line = is_exp_in_line(line_buf, argv[grep->argv_exp]);
		//printf("is_exp_in_line=%d\n", exp_in_line);
		handle_grep(line_buf, exp_in_line, grep);
		free(line_buf);
		line_len = read_line(&line_buf, input_file, is_file);
		//printf("line_len = %d\n", line_len);
	}
	free(grep);
	free(line_buf);
	if (is_file)
		fclose(input_file);
	return 0;
}