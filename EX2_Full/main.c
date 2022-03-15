#include "grep_functionality.h"

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
	char* file_name;
	struct Grep *grep = malloc(sizeof(struct Grep_struct));
	init_grep(argc, argv, grep);
	is_file = contains_file_name(argc, argv);
}