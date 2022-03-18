#include "line_operations.h"

bool is_exp_in_line(char* line, char* exp) {
	if (line == NULL || exp == NULL)
		return false;
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

void to_lower(char* str) {
	int i;
	for (i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

ssize_t read_line(char** line_buf, FILE* file, bool is_file) {
	size_t line_buf_len = 0;
	ssize_t res = 0;
	*line_buf = NULL;
	if (is_file)
		res = getline(line_buf, &line_buf_len, file);
	else
		res = getline(line_buf, &line_buf_len, stdin);
	//printf("temp = %s\n" ,temp); 
	  //printf("line_buf = %s\n", *line_buf);
	//fflush(stdout); 
	return res;
}