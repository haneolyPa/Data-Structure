#pragma once

typedef void* QUEUE_DATA_TYPE;

typedef struct _queue
{
	int front;
	int rear;
	QUEUE_DATA_TYPE* pData;
	int queueSize;
	bool isFull;
} QUEUE;

typedef QUEUE* QUEUE_PTR;

QUEUE_PTR Create_q(int queueSize);
void delete_q(QUEUE_PTR pQueue);
bool IsFull_q(QUEUE_PTR pQueue);
bool IsEmpty_q(QUEUE_PTR pQueue);
void Add_q(QUEUE_PTR pQueue, QUEUE_DATA_TYPE data);
QUEUE_DATA_TYPE Delete_q(QUEUE_PTR pQueue);
