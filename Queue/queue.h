#pragma once

typedef struct _queue
{
	int front;
	int rear;
	char* pData;
	int queueSize;
} QUEUE;

typedef QUEUE* QUEUE_PTR;

QUEUE_PTR Create_q(int queueSize);
void delete_q(QUEUE_PTR pQueue);
bool IsFull_q(QUEUE_PTR pQueue);
bool IsEmpty_q(QUEUE_PTR pQueue);
void Add_q(QUEUE_PTR pQueue, char data);
void Delete_q(QUEUE_PTR pQueue);
void PrintQueue(const QUEUE_PTR pQueue);