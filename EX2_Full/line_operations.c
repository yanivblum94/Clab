#include "line_operations.h"

bool is_exp_in_line_minus_x(char* line, char* exp, Grep* grep) {
	char* ptr = line;
	ptr += strlen(exp);
	if ((strncmp(line, exp, strlen(exp)) == 0) && (*ptr == '\n' || *ptr == '\0')) {
		if(grep->is_v)
			return false;
		return true;
	}
	if (grep->is_v)
		return true;
	return false;
}

bool is_exp_in_line(char* line, char* exp, Grep* grep) {
  if(line == NULL || exp == NULL)
    return false;
  if (grep->is_x)
	  return is_exp_in_line_minus_x(line, exp, grep);
	char* search_ptr = line;
	int lim = strlen(line) - strlen(exp);
	int count = 0;
	while ((*search_ptr != '\0') && (count <= lim)) {
		if (strncmp(search_ptr, exp, strlen(exp)) == 0){
			if(grep->is_v)
				return false;
			return true;
         }
		search_ptr++;
		count++;
	}
	if(grep->is_v)
		return true;
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
	if(is_file)
		res = getline(line_buf, &line_buf_len, file);
	else
		res = getline(line_buf, &line_buf_len, stdin);
  //printf("temp = %s\n" ,temp); 
	//printf("line_buf = %s\n", *line_buf);
  //fflush(stdout); 
	return res;
}