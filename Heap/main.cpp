#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define HEAP_MAX_LAVEL	3	// (높이 = 5)

#define HEAP_MAXSIZE ((2 << HEAP_MAX_LAVEL) - 1)

typedef enum _heap_type {
	MIN_HEAP,
	MAX_HEAP
} HEAP_TYPE;

typedef struct _heap {
	int data[HEAP_MAXSIZE];
	int input_pos;
	HEAP_TYPE type;
} HEAP;

typedef HEAP * HEAP_PTR;

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

HEAP_PTR createHeap(HEAP_TYPE heapType)
{
	HEAP_PTR pHeap = (HEAP_PTR)malloc(sizeof(HEAP));
	pHeap->type = heapType;
	pHeap->input_pos = 0;
	memset(pHeap->data, 0, sizeof(int) * HEAP_MAXSIZE);
	return pHeap;
}

// 전위 순회
void printHeap(HEAP_PTR heap)
{
	printf("          %d\n", heap->data[0]);
	printf("    %d           %d\n", heap->data[1], heap->data[2]);
	printf(" %d      %d       %d       %d\n", heap->data[3], heap->data[4], heap->data[5], heap->data[6]);
	printf("%d %d  %d %d  %d %d  %d %d\n", heap->data[7], heap->data[8], heap->data[9], heap->data[10], 
										   heap->data[11], heap->data[12], heap->data[13], heap->data[14]);
}

// 최소 힙 정렬
void hsort_min_up(HEAP_PTR heap, int pos)
{
	int temp;
	if (pos == 0)
		return;

	temp = ((pos + 1) / 2) - 1;

	if (heap->data[pos] > heap->data[temp])
		return;
		
	swap(&heap->data[pos], &heap->data[temp]);
	hsort_min_up(heap, temp);
}

void hsort_min_down(HEAP_PTR heap, int pos)
{
	int temp = (pos * 2) + 2;
	if (temp >= HEAP_MAXSIZE)
		return;

	if (heap->data[pos] > heap->data[temp] && heap->data[temp] != 0) {
		swap(&heap->data[pos], &heap->data[temp]);
		hsort_min_down(heap, temp);
	}

	if (heap->data[pos] > heap->data[temp - 1] && heap->data[temp-1] != 0) {
		swap(&heap->data[pos], &heap->data[temp - 1]);
		hsort_min_down(heap, temp-1);
	}
		
}

// 힙 정렬
void hsort_up(HEAP_PTR heap)
{
	if (heap->type == MIN_HEAP )
		hsort_min_up(heap, heap->input_pos - 1);
	/*else
		hsort_max(heap);*/
}

void hsort_down(HEAP_PTR heap)
{
	if (heap->type == MIN_HEAP)
		hsort_min_down(heap, 0);
}

void addNode_heap(HEAP_PTR heap, int data)
{
	if (heap->input_pos >= HEAP_MAXSIZE) {
		printf("힙이 가득 차서 더 이상 추가 할 수 없습니다.\n");
		return;
	}

	heap->data[heap->input_pos++] = data;
	hsort_up(heap);
}

void delNode_heap(HEAP_PTR heap)
{
	if (heap->input_pos == 0) {
		printf("빈 힙이어서 데이터를 삭제 할 수 없습니다.\n");
		return;
	}

	swap(&heap->data[0], &heap->data[heap->input_pos - 1]);

	heap->data[--heap->input_pos] = 0;

	hsort_down(heap);
}

int main()
{
	HEAP_PTR heap = createHeap(MIN_HEAP);
	printHeap(heap);

	addNode_heap(heap, 10);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 30);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 40);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 100);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 130);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 44);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 19);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 66);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 566);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 56);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 93);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 89);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 178);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 278);
	printHeap(heap);
	printf("\n");

	addNode_heap(heap, 32);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");
	
	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");
	
	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	delNode_heap(heap);
	printHeap(heap);
	printf("\n");

	return 0;
}