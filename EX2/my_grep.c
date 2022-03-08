#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void validate_args(int args) {
	if (args != 3) {
		fprintf(stderr, "there are %d arguments but it shuold be 3", args);
		exit(-1);
	}
	return;
}

bool exp_in_line(char* line, char* exp) {
	char* search_ptr = line;
	int lim = strlen(line) - strlen(exp);
	int count = 0;

	while ((*search_ptr != '\0') && (count <= lim)) {
		if (strncmp(search_ptr, exp, strlen(exp)) == 0)
			return true;
		search_ptr++;
		count++;
	}
	return false;
}

int main(int argc, char* argv) {
	FILE* input_file = NULL;
	char* line_buf = NULL;
	char* file_name, exp;
	size_t line_buf_len = 0;
	int line_len;

	validate_args(argc);
	file_name = argv[2];
	exp = argv[3];

	input_file = fopen(file_name, "r");
	if (input_file == NULL) {
		fprintf(stderr, "error in open file");
		return -1;
	}

	line_len = getline(&line_buf, &line_buf_len, input_file);
	while (line_len != -1) {
		if (exp_in_line(line_buf, exp)) {
			fprintf(stdout, "%s", line_buf);
		}
		line_len = getline(&line_buf, &line_buf_len, input_file);
	}

	free(line_buf); free(exp); free(file_name);
	fclose(input_file);
	return 0;
}