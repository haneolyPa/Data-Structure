#pragma once

typedef struct _linked_list_node {
	int data;
	struct _linked_list_node * link;
} LINKED_LIST_NODE;

typedef LINKED_LIST_NODE* LINKED_LIST_NODE_PTR;

typedef struct _linkedList_h {
	LINKED_LIST_NODE_PTR head;
}LINKEDLIST_HEAD;

typedef LINKEDLIST_HEAD* LINKEDLIST_HEAD_PTR;

// 원형 리스트 head 를 만듦
LINKEDLIST_HEAD_PTR createCircularLinkedList_h();

// 리스트 출력
void PrintList(const LINKEDLIST_HEAD_PTR H);

// 첫번째 노드에 노드 추가
void addFirstNode(LINKEDLIST_HEAD_PTR H, int data);

// 리스트 마지막에 노트 추가
void addNode(LINKEDLIST_HEAD_PTR H, int data);

// 리스트 마지막에 노트 삭제
// 반환값 : 삭제 노트에 들어 있는 값
void removeFirstNode(LINKEDLIST_HEAD_PTR H);

// 리스트 마지막에 노트 삭제
// 반환값 : 삭제 노트에 들어 있는 값
int removeNode(LINKEDLIST_HEAD_PTR H);

// 리스트 삭제
void RemoveList(LINKEDLIST_HEAD_PTR H);
