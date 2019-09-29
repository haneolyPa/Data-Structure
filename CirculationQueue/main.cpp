#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

typedef struct _queue
{
	int front;
	int rear;
	char* pData;
	int queueSize;
	bool isFull;
} QUEUE;

typedef QUEUE* QUEUE_PTR;

QUEUE Create_q(int queueSize);
bool IsFull_q(QUEUE_PTR pQueue);
bool IsEmpty_q(QUEUE_PTR pQueue);
void Add_q(QUEUE_PTR pQueue, char data);
void Delete_q(QUEUE_PTR pQueue);
void PrintQueue(const QUEUE_PTR pQueue);

QUEUE Create_q(int queueSize)
{
	QUEUE queue;

	queue.front = -1;
	queue.rear = -1;
	queue.queueSize = queueSize;
	queue.pData = (char *)malloc(sizeof(char) * queueSize);
	memset(queue.pData, 0, sizeof(sizeof(char) * queueSize));

	queue.isFull = false;

	return queue;
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

void Add_q(QUEUE_PTR pQueue, char data)
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

void Delete_q(QUEUE_PTR pQueue)
{
	if (IsEmpty_q(pQueue)) {
		printf("Queue is Empty!!\n");
		return ;
	}

	if (pQueue->front == pQueue->queueSize - 1) {
		pQueue->front = -1;
		pQueue->isFull = false;
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


int main()
{
	QUEUE queue = Create_q(4);
	PrintQueue(&queue);

	Add_q(&queue, 'A');
	PrintQueue(&queue);

	Add_q(&queue, 'B');
	PrintQueue(&queue);

	Add_q(&queue, 'C');
	PrintQueue(&queue);

	Add_q(&queue, 'D');
	PrintQueue(&queue);

	Add_q(&queue, 'E');
	PrintQueue(&queue);

	Add_q(&queue, 'F');
	PrintQueue(&queue);

	Add_q(&queue, 'G');
	PrintQueue(&queue);

	Add_q(&queue, 'I');
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Add_q(&queue, 'E');
	PrintQueue(&queue);

	Add_q(&queue, 'F');
	PrintQueue(&queue);

	Add_q(&queue, 'G');
	PrintQueue(&queue);

	Add_q(&queue, 'I');
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	Delete_q(&queue);
	PrintQueue(&queue);

	return 0;
}