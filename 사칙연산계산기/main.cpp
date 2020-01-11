#include "Stack.h"

using namespace std;

#define MAX_BUF_SIZE	256

int main()
{
	char input[MAX_BUF_SIZE] = { '\0', };
	char output[MAX_BUF_SIZE] = { '\0', };

	cout << "계산할 식을 입력해 주세요.(예: 3*8)" << endl;
	cin >> input;

	Infix2Postfix(input, output);
}

void Infix2Postfix(char* const input, char* output)
{
	int inputSize = (int)strlen(input);
	CStack<char>* pStack = CStack<char>::CreateS(MAX_BUF_SIZE);

	for (int i = 0; i < inputSize; i++) {
		if (!isOperator(input[i])) {				// 연산자 인가?
			*output = input[i];
			output++;
		}
		else {
			// 스텍에 있는 연사자 보다 input[i] 가 우선순위가 낮으면
			// 스텍에 있는 연산자를  Pop 합니다.
			while (Oper_Precedence(pStack->getData(), input[i])) {
				*output = pStack->pop();
				output++;
			}
			pStack->push(input[i]);
		}
	}

	while (i < inputSize) {
		if (isOperator(input[i])) {				// 연산자 인가?
			stackTop = GetTopData(stack);

			// 스텍에 있는 연사자 보다 input[i] 가 우선순위가 낮으면
			// 스텍에 있는 연산자를 모두 Pop 합니다.
			if (Oper_Precedence(stackTop, input[i])) {
				while (!is_stack_emuty(stack)) {
					*output = Pop(stack);
					output++;
				}
			}
			Push(stack, input[i]);
		}
		else {
			*output = input[i];
			output++;
		}
		i++;
	}

	// 남은 연산자 출력
	while (!is_stack_emuty(stack)) {
		*output = Pop(stack);
		output++;
	}

	deleteS(stack);
}

bool isOperator(char input)
{
	if (input == '+' || input == '-' || input == '*' || input == '/')
		return true;

	return false;
}


bool Oper_Precedence(char oper1, char oper2)
{
	switch (oper1)
	{
	case '*':
	case '/':
		return true;
	case '+':
	case '-':
		if (oper2 == '+' && oper2 == '-')
			return true;

	default:
		break;
	}

	return false;
}

	



	CStack<char>::DeleteS(pStack);

	return 0;
}
