#ifndef LINKED_LIST
#define LINKED_LIST

#define SUCCESS_CODE 0
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

node* add_end(int i, listHead* list);
node* add_start(int i, listHead* list);
node* add_after(int i, int j, listHead* list, int* exit);
void index(int i, listHead* list);
node* del(int i, listHead* list, int* exit);
int print_list(listHead* list);

void freeAllocatedListMemory(listHead* list);
listHead* initList();

#endif 