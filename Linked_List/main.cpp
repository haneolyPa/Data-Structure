#include <stdio.h>
#include "LinkedList.h"

int main()
{
	PrintList(&head);

	addNode(&head, 100);
	printf("\n");
	printf("addNode(&head, 100);\n");
	PrintList(&head);

	addNode(&head, 200);
	printf("\n");
	printf("addNode(&head, 200);\n");
	PrintList(&head);

	addNode(&head, 300);
	printf("\n");
	printf("addNode(&head, 300);\n");
	PrintList(&head);

	addNode(&head, 400);
	printf("\n");
	printf("addNode(&head, 400);\n");
	PrintList(&head);

	addNode(&head, 500);
	printf("\n");
	printf("addNode(&head, 500);\n");
	PrintList(&head);

	removeNode(&head);
	printf("\n");
	printf("removeNode(&head);\n");
	PrintList(&head);

	additNode(getNode(&head, 100), 150);
	printf("\n");
	printf("additNode(getNode(&head, 100), 150);\n");
	PrintList(&head);

	removeitNode(&head, getNode(&head, 300));
	printf("\n");
	printf("removeitNode(&head, getNode(&head, 300));\n");
	PrintList(&head);

	additNode(getNode(&head, 200), 250);
	printf("\n");
	printf("additNode(getNode(&head, 200), 250);\n");
	PrintList(&head);

	return 0;
}