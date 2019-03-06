# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct {
	int height;
	int width;
}Rect;

typedef struct list {
	Rect *r;
	struct list *next;
}List;

List *initList();
int insertList(List **);
void printList(List *);
List* freeList(List *);

int main() {

	srand(time(NULL));

	List* list = initList();
	int check = 0;
	for (int i = 0; i < 10; i++) {
		check = insertList(&list);
		if (check == -1) {
			printf("Insufficient memory\n");
			return -1;
		}
	}
	printList(list);

	list = freeList(list);

	// please explain why the code had segmentation fault before here
	/*
	when in insertList you try to set newNode->r->height and width before you have 
	properly malloced a Rect struct to be used
	*/

	return 0;
}

List *initList() {
	return NULL;
}

int insertList(List **head) {
	List *newNode = (List*)malloc(sizeof(List));

	if (newNode == NULL) {
		return -1;
	}

    //need so that there is no seg fault
	Rect *newRect = (Rect *)malloc(sizeof(Rect));
	newNode->r = newRect;

	newNode->r->height = rand() % 10 + 1;
	newNode->r->width = rand() % 10 + 1;

	newNode->next = *head;
	*head = newNode;

	return 1;
}

void printList(List *head) {
	printf("Areas are:");
	List * temp = head;
	while (temp) {
		printf(" %d,", (temp->r->height)*(temp->r->width));
		temp = temp->next;
	}
	printf("\n");
}

List* freeList(List *head) {
	List* temp = head;
	while (head) {
		temp = head->next;
		free(head->r);
		free(head);
		head = temp;
	}
	return NULL;
}
