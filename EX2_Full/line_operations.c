#include "line_operations.h"

bool is_exp_in_line_minus_x(char* line, char* exp) {
	char* ptr = line;
	ptr += strlen(exp);
	if ((strncmp(line, exp, strlen(exp)) == 0) && (*ptr == '\n' || *ptr == '\0')) 
		return true;
	return false;
}

bool is_char_in_ascii_range(int c, int initialChar, int endChar)
{
	if ((c >= initialChar) && (c <= endChar))
		return true;
	return false;
}


int find_char_idx(char* str, char c)
{
	int i = 0;

	while (str[i] != c) i++;

	return i;
}


int is_reg_exp_match(char* line, char* regExp, bool expectSpecialChar)
{

	int lineLength = strlen(line), regExpLength = strlen(regExp), orMatch = NO_MATCH_CODE;

	if (regExpLength == 0)
		return MATCH_CODE;
	else if (lineLength == 0)
		return NO_MATCH_CODE;

	if ((regExp[CURR_IDX] == BACKSLASH_ASCII) && (expectSpecialChar == false))
		return is_reg_exp_match(line, &regExp[NEXT_IDX], true);

	if ((regExp[CURR_IDX] == SQUARE_BRACKETS_OPEN_ASCII) && (expectSpecialChar == false))
	{
		if (is_char_in_ascii_range(line[CURR_IDX], regExp[NEXT_IDX], regExp[THIRD_IDX]))
			return is_reg_exp_match(&line[NEXT_IDX], &regExp[FIFTH_INX], false);
		else
			return NO_MATCH_CODE;
	}

	if ((regExp[CURR_IDX] == VERTICAL_LINE_ASCII) && (expectSpecialChar == false))
		return is_reg_exp_match(line, &regExp[find_char_idx(regExp, ROUND_BRACKETS_CLOSE_ASCII) + NEXT_IDX], false);

	if ((regExp[CURR_IDX] == ROUND_BRACKETS_OPEN_ASCII) && (expectSpecialChar == false))
	{
		orMatch = is_reg_exp_match(&line[CURR_IDX], &regExp[find_char_idx(regExp, VERTICAL_LINE_ASCII)] + NEXT_IDX, false);
		if (orMatch == MATCH_CODE)
			return MATCH_CODE;
		return is_reg_exp_match(line, &regExp[NEXT_IDX], false);
	}
	
	if ((regExp[CURR_IDX] == ROUND_BRACKETS_CLOSE_ASCII) && (expectSpecialChar == false))
		return is_reg_exp_match(line, &regExp[NEXT_IDX], false);

	if ((regExp[CURR_IDX] == DOT_ASCII) && (expectSpecialChar == false))
		return is_reg_exp_match(&line[NEXT_IDX], &regExp[NEXT_IDX], false);

	if (line[CURR_IDX] == regExp[CURR_IDX])
		return is_reg_exp_match(&line[NEXT_IDX], &regExp[NEXT_IDX], false);

}

bool is_exp_in_line_minus_E(char* line, char* regExp)
{
	int lineLength = strlen(line), i;

	for (i = 0; i < lineLength; i++)
		if (is_reg_exp_match(&line[i], regExp, false) == MATCH_CODE) 
			return true;

	return false;
}

bool is_exp_in_line(char* line, char* exp, Grep* grep) {
  if(line == NULL || exp == NULL)
    return false;
  if (grep->is_x)
	  return is_exp_in_line_minus_x(line, exp);
  if (grep->is_E)
	  return is_exp_in_line_minus_E(line, exp);
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
	if(is_file)
		res = getline(line_buf, &line_buf_len, file);
	else
		res = getline(line_buf, &line_buf_len, stdin);
	return res;
}