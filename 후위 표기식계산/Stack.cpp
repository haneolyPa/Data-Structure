// Stack.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <corecrt_malloc.h>
#include <stdbool.h>

#include "Stack.h"

STACK_PTR CreateS(int stackSize)
{
	STACK_PTR pStack = (STACK_PTR)malloc(sizeof(STACK));

	pStack->top = -1;
	pStack->stackSize = stackSize;
	pStack->pData = (char *)malloc(sizeof(char) * stackSize);

	return pStack;
}

void deleteS(STACK_PTR pStack)
{
	free(pStack->pData);
	free(pStack);
}

bool is_stack_emuty(STACK_PTR pStack)
{
	if (pStack->top == -1)
		return true;
	else
		return false;
}

bool is_stack_full(STACK_PTR pStack)
{
	if (pStack->top == pStack->stackSize - 1)
		return true;
	else
		return false;
}

void Push(STACK_PTR pStack, char data)
{
	if (is_stack_full(pStack))
		return;

	pStack->pData[++pStack->top] = data;
}

char Pop(STACK_PTR pStack)
{
	if (is_stack_emuty(pStack))
		return -1;
	return pStack->pData[pStack->top--];
}

void PrintStack(const STACK_PTR pStack)
{
	int i;
	printf("\ntop -> ");
	for (i = pStack->top; i >= 0; i--) {
		printf("%c   Data[%d]\n", pStack->pData[i], i);
		printf("       ");
	}
}

char GetTopData(STACK_PTR pStack)
{
	return pStack->pData[pStack->top];
}



