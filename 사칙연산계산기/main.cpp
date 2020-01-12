#include "Stack.h"

using namespace std;

void Infix2Postfix(char* const input, char* output);
bool isOperator(char input);
bool Oper_Precedence(char oper1, char oper2);

#define MAX_BUF_SIZE	256

int main()
{
	char input[MAX_BUF_SIZE] = { '\0', };
	char output[MAX_BUF_SIZE] = { '\0', };

	cout << "계산할 식을 입력해 주세요.(예: 3*8)" << endl;
	cin >> input;

	Infix2Postfix(input, output);

	cout << output;

	return 0;
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

	// 남은 연산자 출력
	while (!pStack->empty()) {
		*output = pStack->pop();
		output++;
	}

	CStack<char>::DeleteS(pStack);
}

bool isOperator(char input)
{
	return (input == '+' || input == '-' || input == '*' || input == '/') ? true : false;
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
		if (oper2 == '+' || oper2 == '-')
			return true;

	default:
		break;
	}

	return false;
}