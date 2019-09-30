#include <stdio.h>
#include <string.h>

#include "Stack.h"

#define INPUT_SIZE		256

#define NUM2CHAR(X)		(X) + '0'
#define CHAR2NUM(X)		(X) - '0'

int evalPostfix(char *exp)
{
	int oper1, oper2, i = 0;
	int length = (int)strlen(exp);
	char symbol;
	int res;

	STACK_PTR stack = CreateS(length);
	
	for (i = 0; i < length; i++) {
		symbol = exp[i];
		if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/') {
			Push(stack, symbol);
		}
		else {
			oper1 = CHAR2NUM(Pop(stack));
			oper2 = CHAR2NUM(Pop(stack));
			switch (symbol)
			{
			case '+': Push(stack, NUM2CHAR(oper1 + oper2)); break;
			case '-': Push(stack, NUM2CHAR(oper1 - oper2)); break;
			case '*': Push(stack, NUM2CHAR(oper1 * oper2)); break;
			case '/': Push(stack, NUM2CHAR(oper1 / oper2)); break;
			}
		}
	}

	res = CHAR2NUM(Pop(stack));
	
	deleteS(stack);

	return res;
}

int main()
{
	/*char input[INPUT_SIZE] = { '\0', };
	scanf("%s", input);*/

	char input[INPUT_SIZE] = "369*+";
	printf("%s", input);

	printf("= %d", evalPostfix(input));

	return 0;
}
