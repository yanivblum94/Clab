#ifndef LINKED_LIST
#define LINKED_LIST

#define EXIT_CODE 1

typedef struct
{
	int val;
	struct node* previous;
	struct node* next;

} node;

typedef struct {
	node* head;
	int len;
}listHead;

void add_end(int i, listHead* list);
void add_start(int i, listHead* list);
void add_after(int i, int j, listHead* list, int* exit);
void index(int i, listHead* list);
void del(int i, listHead* list, int* exit);
void print_list(listHead* list);
void freeAllocatedListMemory(listHead* list);
listHead* initList();

#endif 