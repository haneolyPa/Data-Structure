#pragma once

typedef struct _stack
{
	int top;
	int stackSize;
	char* pData;
} STACK;

typedef STACK* STACK_PTR;

STACK CreateS(int stackSize);				// 스택을 만드는 함수
bool is_stack_emuty(STACK_PTR pStack);		// 빈 스택 인가?
bool is_stack_full(STACK_PTR pStack);		// 가득찬 스택 인가?
void Push(STACK_PTR pStack, char data);		
char Pop(STACK_PTR pStack);
void PrintStack(STACK_PTR const pStack);	// 스택 출력 함수

