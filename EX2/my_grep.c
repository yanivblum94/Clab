#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void validate_args(int args) {
	if (args != 3) {
		printf("there are %d arguments but it shuold be 3", args);
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

int main(int argc, char* argv[]) {
	FILE* input_file = NULL;
	char* line_buf = NULL;
	size_t line_buf_len = 0;
	int line_len;

	validate_args(argc);

	input_file = fopen(argv[2], "r");
	if (input_file == NULL) {
		printf("error in open file");
		return -1;
	}

	line_len = getline(&line_buf, &line_buf_len, input_file);
	while (line_len != -1) {
		if (exp_in_line(line_buf, argv[1])) {
			printf("%s", line_buf);
		}
		line_len = getline(&line_buf, &line_buf_len, input_file);
	}
	free(line_buf);
	fclose(input_file);
	return 0;
}