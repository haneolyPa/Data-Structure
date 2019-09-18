#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LINKEDLIST_HEAD head = NULL;

// 새로운 노드 생성
// 반환값 : 생성된 노드의 포인터
LINKED_LIST_NODE_PTR newNode(int data);

// 노드 삭제
// 반환값 : 삭제 노트에 들어 있는 값
int deleteNode(LINKED_LIST_NODE_PTR prevNode);

// 리스트의 마지막 노드
// 반환값 : 마지막 노드의 포인터
LINKED_LIST_NODE_PTR getLastNode(LINKEDLIST_HEAD_PTR H);

// 마지막 노드의 이전 노드
// 반환값 : 마지막 노드의 이전 노드의 포인터
LINKED_LIST_NODE_PTR getPrevNodeOfLastNode(LINKEDLIST_HEAD_PTR H);

// 특정노드의 이전 노드
// 반환값 : 특정노드의 이전 노드의 포인터
LINKED_LIST_NODE_PTR getPrevNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode);

LINKED_LIST_NODE_PTR newNode(int data)
{
	LINKED_LIST_NODE_PTR newnode = (LINKED_LIST_NODE_PTR)malloc(sizeof(LINKED_LIST_NODE));
	newnode->data = data;
	newnode->link = NULL;
	return newnode;
}

int deleteNode(LINKED_LIST_NODE_PTR prevNode)
{
	int data = prevNode->data;
	free(prevNode);
	return data;
}

LINKED_LIST_NODE_PTR getLastNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR lastNode = *H;

	if (lastNode != NULL)
		while (lastNode->link != NULL)
			lastNode = lastNode->link;

	return lastNode;
}

LINKED_LIST_NODE_PTR getPrevNodeOfLastNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR prevNode = *H;

	if (prevNode != NULL && prevNode->link != NULL)
		while (prevNode->link->link != NULL)
			prevNode = prevNode->link;

	return prevNode;
}

LINKED_LIST_NODE_PTR getPrevNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode)
{
	LINKED_LIST_NODE_PTR prevNode = *H;

	if (prevNode != NULL)
		while (prevNode->link != NULL && prevNode->link != itNode)
			prevNode = prevNode->link;

	return prevNode;
}

LINKED_LIST_NODE_PTR getNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR find_Node = *H;

	if (find_Node != NULL)
		while (find_Node->link != NULL && !(find_Node->data == data))
			find_Node = find_Node->link;

	return find_Node;
}

void addNode(LINKEDLIST_HEAD_PTR H, int data)
{
	LINKED_LIST_NODE_PTR new_Node = newNode(data);

	LINKED_LIST_NODE_PTR lastNode = getLastNode(H);
	if (lastNode == NULL) {
		*H = new_Node;
		return;
	}

	lastNode->link = new_Node;
}

void additNode(LINKED_LIST_NODE_PTR prevNode, int data)
{
	LINKED_LIST_NODE_PTR new_Node = newNode(data);
	new_Node->link = prevNode->link;
	prevNode->link = new_Node;
}

int removeNode(LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR prev_Node = getPrevNodeOfLastNode(H);
	LINKED_LIST_NODE_PTR last_Node = NULL;

	if (prev_Node == NULL) {
		printf("The last node cannot be removed because it is an empty list!!!");
		return -1;
	}

	if (*H == prev_Node) {
		*H = NULL;
		return deleteNode(last_Node);
	}

	last_Node = prev_Node->link;

	prev_Node->link = NULL;
	return deleteNode(last_Node);
}

int removeitNode(LINKEDLIST_HEAD_PTR H, LINKED_LIST_NODE_PTR itNode)
{
	LINKED_LIST_NODE_PTR prev_Node = getPrevNode(H, itNode);

	if (prev_Node == NULL || prev_Node->link == NULL) {
		printf("삭제하려는 노드를 찾을 수 없습니다!!!");
		return -1;
	}

	prev_Node->link = itNode->link;
	return deleteNode(itNode);
}

void PrintList(const LINKEDLIST_HEAD_PTR H)
{
	LINKED_LIST_NODE_PTR pNode = *H;

	printf("Head ->");

	while (pNode != NULL) {
		printf("| %d : Nest | -> ", pNode->data);
		pNode = pNode->link;
	}

	printf("| NULL |\n");
}