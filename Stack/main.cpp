#include "Stack.h"
#include "CStack.h"

int main()
{
	/*STACK_PTR stack = CreateS(3);
	Push(stack, 'S');
	PrintStack(stack);
	Push(stack, 'T');
	PrintStack(stack);
	Pop(stack);
	PrintStack(stack);
	Push(stack, 'R');
	PrintStack(stack);
	Push(stack, 'P');
	PrintStack(stack);
	Push(stack, 'Q');
	PrintStack(stack);
	Pop(stack);
	PrintStack(stack);

	deleteS(stack);*/

	CStack<char>* pStack = CStack<char>::CreateS(3);

	pStack->push('S');
	pStack->show();
	pStack->push('T');
	pStack->show();
	pStack->pop();
	pStack->show();
	pStack->push('R');
	pStack->show();
	pStack->push('P');
	pStack->show();
	pStack->push('Q');
	pStack->show();
	pStack->pop();
	pStack->show();

	CStack<char>::DeleteS(pStack);

	return 0;
}
