#include <stdio.h>
#include <stdlib.h>
#include "Circular_Linked_List.h"

// head 가 가르키는 첫번째 노드
// 반환값 : 첫번째 노드의 포인터
LINKED_LIST_NODE_PTR getFirstNode(LINKEDLIST_HEAD_PTR H)
{
	return H->head;
}

bool IsLastNode(LINKED_LIST_NODE_PTR pNode, LINKEDLIST_HEAD_PTR H)
{
	return (pNode->link == getFirstNode(H));
}

LINKEDLIST_HEAD_PTR createCircularLinkedList_h()
{
	LINKEDLIST_HEAD_PTR pHead = (LINKEDLIST_HEAD_PTR)malloc(sizeof(LINKEDLIST_HEAD));
	pHead->head = NULL;
	return pHead;
}

void PrintList(const LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = getFirstNode(H);

	printf("Head -> ");

	while (!IsLastNode(pNode, H)) {
		printf("| %d : Nest | -> ", pNode->data);
		pNode = pNode->link;
	}

	printf("| NULL |\n");
}