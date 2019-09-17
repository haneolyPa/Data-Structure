#pragma once

typedef struct _queue
{
	int front;
	int rear;
	char* pData;
	int queueSize;
} QUEUE;

typedef QUEUE* QUEUE_PTR;

QUEUE Create_q(int queueSize);
bool IsFull_q(QUEUE_PTR pQueue);
bool IsEmpty_q(QUEUE_PTR pQueue);
void Add_q(QUEUE_PTR pQueue, char data);
char Delete_q(QUEUE_PTR pQueue);
void PrintQueue(QUEUE_PTR const pQueue);