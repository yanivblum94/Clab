#include "line_operations.h"
#include <stdlib.h>
#include <string.h>

#define NO_MATCH_CODE -1
#define MATCH_CODE 1
#define CURR_IDX 0
#define NEXT_IDX 1
#define THIRD_IDX 3
#define FIFTH_INX 5

#define NULL_ASCII 0
#define ROUND_BRACKETS_OPEN_ASCII 40
#define ROUND_BRACKETS_CLOSE_ASCII 41
#define DOT_ASCII 46
#define SQUARE_BRACKETS_OPEN_ASCII 91
#define BACKSLASH_ASCII 92
#define SQUARE_BRACKETS_CLOSE_ASCII 93
#define VERTICAL_LINE_ASCII 124

bool is_char_in_ascii_range(int c, int initialChar, int endChar)
{
  if ((c >= initialChar) && (c <= endChar)) {
    return true;
  }
  return false;
}

int find_char_idx(const char* str, char c)
{
  int i = 0;

  while (str[i] != c) {
    i++;
  }

  return i;
}

int get_match(char* line, char* regExp, bool expectSpecialChar, bool is_x)
{

  int lineLength = strlen(line), regExpLength = strlen(regExp), orM = NO_MATCH_CODE;
  if (regExpLength == 0) {
    if (is_x) {
      if (*line == '\n' || *line == '\0') {
        return MATCH_CODE;
      } else {
        return NO_MATCH_CODE;
      }
    }
    return MATCH_CODE;
  } else if (lineLength == 0) {
    return NO_MATCH_CODE;
  }
  if ((regExp[CURR_IDX] == BACKSLASH_ASCII) && (expectSpecialChar == false)) {
    return get_match(line, &regExp[NEXT_IDX], true, is_x);
  }
  if ((regExp[CURR_IDX] == SQUARE_BRACKETS_OPEN_ASCII) && (expectSpecialChar == false)) {
    if (is_char_in_ascii_range(line[CURR_IDX], regExp[NEXT_IDX], regExp[THIRD_IDX])) {
      return get_match(&line[NEXT_IDX], &regExp[FIFTH_INX], false, is_x);
    } else {
      return NO_MATCH_CODE;
    }
  }
  if ((regExp[CURR_IDX] == VERTICAL_LINE_ASCII) && (expectSpecialChar == false)) {
    return get_match(line, &regExp[find_char_idx(regExp, ROUND_BRACKETS_CLOSE_ASCII) + NEXT_IDX], false, is_x);
  }
  if ((regExp[CURR_IDX] == ROUND_BRACKETS_OPEN_ASCII) && (expectSpecialChar == false)) {
    orM = get_match(&line[CURR_IDX], &regExp[find_char_idx(regExp, VERTICAL_LINE_ASCII)] + NEXT_IDX, false, is_x);
    if (orM == MATCH_CODE) {
      return MATCH_CODE;
    }
    return get_match(line, &regExp[NEXT_IDX], false, is_x);
  }
  if ((regExp[CURR_IDX] == ROUND_BRACKETS_CLOSE_ASCII) && (expectSpecialChar == false)) {
    return get_match(line, &regExp[NEXT_IDX], false, is_x);
  }
  if ((regExp[CURR_IDX] == DOT_ASCII) && (expectSpecialChar == false)) {
    return get_match(&line[NEXT_IDX], &regExp[NEXT_IDX], false, is_x);
  }
  if (line[CURR_IDX] == regExp[CURR_IDX]) {
    return get_match(&line[NEXT_IDX], &regExp[NEXT_IDX], false, is_x);
  }
}

bool is_exp_in_line(char* line, char* exp, Grep* grep)
{
  int lineLength = strlen(line), i;

  if (line == NULL || exp == NULL) {
    return false;
  }

  for (i = 0; i < lineLength; i++) {
    if (get_match(&line[i], exp, false, grep->is_x) == MATCH_CODE) {
      return true;
    }
    if (grep->is_x) {
      break;
    }
  }

  return false;
}

void to_lower(char* str)
{
  int i;
  for (i = 0; i < strlen(str); i++) {
    str[i] = tolower(str[i]);
  }
}

ssize_t read_line(char** line_buf, FILE* file, bool is_file)
{
  size_t line_buf_len = 0;
  ssize_t res = 0;
  *line_buf = NULL;
  if (is_file) {
    res = getline(line_buf, &line_buf_len, file);
  } else {
    res = getline(line_buf, &line_buf_len, stdin);
  }
  return res;
}