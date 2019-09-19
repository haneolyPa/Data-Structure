#include <stdio.h>
#include "Circular_Linked_List.h"


int main()
{
	LINKEDLIST_HEAD_PTR head = createCircularLinkedList_h();
	PrintList(head);

	removeNode(head);
	printf("\n");
	printf("removeNode(head);\n");
	PrintList(head);

	addFirstNode(head, 100);
	printf("\n");
	printf("addFirstNode(head, 100);\n");
	PrintList(head);

	removeNode(head);
	printf("\n");
	printf("removeNode(head);\n");
	PrintList(head);

	addFirstNode(head, 100);
	printf("\n");
	printf("addFirstNode(head, 100);\n");
	PrintList(head);

	addFirstNode(head, 50);
	printf("\n");
	printf("addFirstNode(head, 50);\n");
	PrintList(head);

	removeFirstNode(head);
	printf("\n");
	printf("removeFirstNode(head);\n");
	PrintList(head);

	removeFirstNode(head);
	printf("\n");
	printf("removeFirstNode(head);\n");
	PrintList(head);

	addFirstNode(head, 100);
	printf("\n");
	printf("addFirstNode(head, 100);\n");
	PrintList(head);

	addFirstNode(head, 50);
	printf("\n");
	printf("addFirstNode(head, 50);\n");
	PrintList(head);

	addNode(head, 200);
	printf("\n");
	printf("addNode(head, 200);\n");
	PrintList(head);

	addNode(head, 300);
	printf("\n");
	printf("addNode(head, 300);\n");
	PrintList(head);

	addNode(head, 400);
	printf("\n");
	printf("addNode(head, 400);\n");
	PrintList(head);

	removeFirstNode(head);
	printf("\n");
	printf("removeFirstNode(head);\n");
	PrintList(head);

	removeNode(head);
	printf("\n");
	printf("removeNode(head);\n");
	PrintList(head);

	RemoveList(head);

	return 0;
}