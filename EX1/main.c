#include <stdio.h>

#include "linked_list.h"
#define ADD_END_STR "add_end"
#define ADD_START_STR "add_start"
#define ADD_AFTER_STR "add_after"
#define INDEX_STR "index"
#define DEL_STR "del"
#define PRINT_STR "print"
#define EXIT_STR "exit"
#define CONTINUE_CODE 0
#define MAX_LINE_LEN 100

void commandParser(char* userInput, int* exit, listHead* list)
{
	int i, j;

	if (strstr(userInput, ADD_END_STR) != NULL)
	{
		sscanf(userInput, "add_end %d", &i);
		add_end(i, list);
	}
	else if (strstr(userInput, ADD_START_STR) != NULL)
	{
		sscanf(userInput, "add_start %d", &i);
		add_start(i, list);
	}
	else if (strstr(userInput, ADD_AFTER_STR) != NULL)
	{
		sscanf(userInput, "add_after %d %d", &i, &j);
		add_after(i, j, list, exit);
	}
	else if (strstr(userInput, INDEX_STR) != NULL)
	{
		sscanf(userInput, "index %d", &i);
		index(i, list);
	}
	else if (strstr(userInput, DEL_STR) != NULL)
	{
		sscanf(userInput, "del %d", &i);
		del(i, list, exit);
	}

	else if (strstr(userInput, EXIT_STR) != NULL)
		*exit = EXIT_CODE;

	else if (strstr(userInput, PRINT_STR) != NULL)
		print_list(list);

}

void stringToLowercase(char* str)
{
	int i;
	for (i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

void commandInputLoop(listHead* list)
{
	char userInput[MAX_LINE_LEN] = "";
	int exit = CONTINUE_CODE;

	while (exit == CONTINUE_CODE)
	{
		gets(userInput);
		stringToLowercase(userInput);
		commandParser(userInput, &exit, list);
	}
}

int main(){
	listHead* list = initList();
	commandInputLoop(list);
	freeAllocatedListMemory(list);
}