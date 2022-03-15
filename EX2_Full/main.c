#include "grep_functionality.h"

int main(int argc, char* argv[]) {
	struct Grep *grep = malloc(sizeof(struct Grep_struct));
	init_grep(argc, argv, grep);
}