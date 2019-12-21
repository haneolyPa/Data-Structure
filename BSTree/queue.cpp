
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "queue.h"


QUEUE_PTR Create_q(int queueSize)
{
	QUEUE_PTR pQueue = (QUEUE_PTR)malloc(sizeof(QUEUE));;

	pQueue->front = -1;
	pQueue->rear = -1;
	pQueue->isFull = false;
	pQueue->queueSize = queueSize;
	pQueue->pData = (void **)malloc(sizeof(QUEUE_DATA_TYPE) * queueSize);
	memset(pQueue->pData, 0, sizeof(sizeof(QUEUE_DATA_TYPE) * queueSize));

	return pQueue;
}

void delete_q(QUEUE_PTR pQueue)
{
	free(pQueue->pData);
	free(pQueue);
}

bool IsFull_q(QUEUE_PTR pQueue)
{
	if ((pQueue->front == -1 && (pQueue->rear == pQueue->queueSize - 1)) ||
		((pQueue->rear == pQueue->front) && pQueue->isFull))
		return true;
	else
		return false;
}

bool IsEmpty_q(QUEUE_PTR pQueue)
{
	if ((pQueue->front == pQueue->rear) && !pQueue->isFull)
		return true;
	else
		return false;
}

void Add_q(QUEUE_PTR pQueue, QUEUE_DATA_TYPE data)
{
	if (IsFull_q(pQueue)) {
		printf("Queue is full!!\n");
		return;
	}

	if (pQueue->rear == pQueue->queueSize - 1) {
		pQueue->rear = -1;
		pQueue->isFull = true;
	}

	pQueue->pData[++pQueue->rear] = data;
	return;
}

QUEUE_DATA_TYPE Delete_q(QUEUE_PTR pQueue)
{
	QUEUE_DATA_TYPE res_Data;
	if (IsEmpty_q(pQueue)) {
		printf("Queue is Empty!!\n");
		return NULL;
	}

	res_Data = pQueue->pData[pQueue->front];

	if (pQueue->front == pQueue->queueSize - 1) {
		pQueue->front = -1;
		pQueue->isFull = false;
	}

	++pQueue->front;
	res_Data = pQueue->pData[pQueue->front];
	pQueue->pData[pQueue->front] = NULL;
	
	return res_Data;
}
