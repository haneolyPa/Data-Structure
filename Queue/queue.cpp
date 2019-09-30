#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "queue.h"

QUEUE_PTR Create_q(int queueSize)
{
	QUEUE_PTR pQueue = (QUEUE_PTR)malloc(sizeof(QUEUE));;

	pQueue->front = -1;
	pQueue->rear = -1;
	pQueue->queueSize = queueSize;
	pQueue->pData = (char *)malloc(sizeof(char) * queueSize);
	memset(pQueue->pData, 0, sizeof(sizeof(char) * queueSize));

	return pQueue;
}

void delete_q(QUEUE_PTR pQueue)
{
	free(pQueue->pData);
	free(pQueue);
}

bool IsFull_q(QUEUE_PTR pQueue)
{
	if (pQueue->rear == (pQueue->queueSize - 1))
		return true;
	else
		return false;
}

bool IsEmpty_q(QUEUE_PTR pQueue)
{
	if (pQueue->front == pQueue->rear)
		return true;
	else
		return false;
}

void Add_q(QUEUE_PTR pQueue, char data)
{
	if (IsFull_q(pQueue)) {
		printf("Queue is full!!\n");
		return;
	}

	pQueue->pData[++pQueue->rear] = data;
	return;
}

void Delete_q(QUEUE_PTR pQueue)
{
	if (IsEmpty_q(pQueue)) {
		printf("Queue is Empty!!\n");
		return ;
	}

	pQueue->pData[++pQueue->front] = 0;
}

void PrintQueue(const QUEUE_PTR pQueue)
{
	int i;
	for (i = -1; i < pQueue->queueSize; i++) {
		if (pQueue->front == i)
			printf("|front->|");
		else
			printf("|       |");

		if (pQueue->rear == i)
			printf("|rear-> |");
		else
			printf("|       |");

		if (i != -1)
			printf("|   %c   |\n", pQueue->pData[i]);
		else
			printf("\n");
	}

	printf("\n");
}
