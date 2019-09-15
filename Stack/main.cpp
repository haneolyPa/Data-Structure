#include "Stack.h"

int main()
{
	STACK stack = CreateS(3);
	Push(&stack, 'S');
	PrintStack(&stack);
	Push(&stack, 'T');
	PrintStack(&stack);
	Pop(&stack);
	PrintStack(&stack);
	Push(&stack, 'R');
	PrintStack(&stack);
	Push(&stack, 'P');
	PrintStack(&stack);
	Push(&stack, 'Q');
	PrintStack(&stack);
	Pop(&stack);
	PrintStack(&stack);

	return 0;
}
