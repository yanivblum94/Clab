#include <stdio.h>
#include "linked_list.h"

#define VAL_NOT_FOUND_CODE -1
#define EMPTY_LIST_INDICATOR 1
#define MAX_INT_STRING_SIZE 12
#define SPACING_STRING_SIZE 3

node* allocateNode(int i, node* prevNode, node* nextNode)
{
	node* newNode = malloc(sizeof(node));

	newNode->val = i;
	newNode->previous = prevNode;
	newNode->next = nextNode;

	if (prevNode != NULL) prevNode->next = newNode;
	if (nextNode != NULL) nextNode->previous = newNode;

	return newNode;
}

node* findItemByIndex(int i, listHead* list)
{
	int idx = 0;

	node* res = list->head;

	while (idx != i)
	{
		res = res->next;
		idx++;
	}
	return res;
}


int findValIndex(int i, listHead* list)
{
	int res = VAL_NOT_FOUND_CODE;

	node* temp = list->head;

	while (temp != NULL)
	{
		res++;
		if (temp->val == i) return res;
		temp = temp->next;
	}
	return VAL_NOT_FOUND_CODE;
}

void add_end(int i, listHead* list)
{
	if (list->len == 0) {
		add_start(i, list);
		return;
	}
	node* lastItem = findItemByIndex((list->len - 1), list);
	list->len++;
	allocateNode(i, lastItem, NULL);
}


void add_start(int i, listHead* list)
{
	node* res;
	if (list->len == 0) {
		res = allocateNode(i, NULL, NULL);
		list->len++;
		list->head = res;
		return;
	}
	res = allocateNode(i, NULL, list->head);
	list->head = res;
	list->len++;
}


void add_after(int i, int j, listHead* list, int* exit)
{
	int jIndex = findValIndex(j, list);
	if (jIndex == VAL_NOT_FOUND_CODE)
	{
		printf("ERROR: index 'j' was not found.\n");
		*exit = EXIT_CODE;
		return;
	}
	node* jNode = findItemByIndex(jIndex, list);
	list->len++;
	allocateNode(i, jNode, jNode->next);
}


void index(int i, listHead* list)
{
	printf("%d\n", findValIndex(i, list));
}



void del(int i, listHead* list, int* exit)
{
	node* toDel, *delPrev, *delNext;
	if (i >= list->len)
	{
		printf("ERROR: index is too large.\n");
		*exit = EXIT_CODE;
		return;
	}

	if(i == 0){//we delete the first node
		toDel = list->head;
		list->head = toDel->next;
		if(list->head != NULL)
			list->head->previous = NULL;
		free(toDel);
		list->len--;
		return;
	}

	toDel = findItemByIndex(i, list);
	delPrev = toDel->previous;
	delNext = toDel->next;

	if (delNext == NULL) {//we delete the last node
		delPrev->next = NULL;
	}
	else {
		delPrev->next = delNext;
		delNext->previous = delPrev;
	}
	free(toDel);
	list->len--;

}


void print_list(listHead* list)
{
	char* listString, intString[MAX_INT_STRING_SIZE];
	listString = (char*) malloc((list->len * MAX_INT_STRING_SIZE + SPACING_STRING_SIZE) * sizeof(char));
	int i = 0, j;
	listString[i++] = '[';
	node* temp = list->head;
	while (temp != NULL)
	{
		sprintf(intString, "%d", temp->val);
		j = 0;
		while (intString[j] != '\0')
		{
			listString[i++] = intString[j++];
		}
		listString[i++] = ',';
		listString[i++] = ' ';
		temp = temp->next;
	}
	if (i == EMPTY_LIST_INDICATOR)
	{
		listString[i++] = ']';
		listString[i] = '\0';
	}
	else
	{
		listString[--i] = '\0';
		listString[--i] = ']';
	}

	printf("%s\n", listString);
	free(listString);
}




void freeAllocatedListMemory(listHead* list)
{
	node* temp = list->head;

	while (temp != NULL)
	{
		node* next = temp->next;
		free(temp);
		temp = next;
	}
}

listHead* initList() {
	listHead* list = (listHead*)malloc(sizeof(listHead*));
	list->head = NULL;
	list->len = 0;
	return list;
}