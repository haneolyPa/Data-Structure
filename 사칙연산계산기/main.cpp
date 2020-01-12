#include "Stack.h"

using namespace std;

// 중위표기법을 후위표기법으로 변경하는 함수
void Infix2Postfix(char* const input, char* output);
bool Infix2Postfix_bracket(char* const input, char* output);

// 연사자인자 판단 함수
// 'input' 이 연산자('+', '-', '*', '/')이면 true 이고, 아니면 false
bool isOperator(char input);

// 연사자 우선 판단 함수
// oper1 이 '*' 이고, oper2 가 '*', '/', '+', '-' 이면 true,
// oper1 이 '/' 이고, oper2 가 '*', '/', '+', '-' 이면 true,
// oper1 이 '+' 이고, oper2 가 '+', '-' 이면 true,
// oper1 이 '-' 이고, oper2 가 '+', '-' 이면 true,
// 이 외에는 false
bool Oper_Precedence(char oper1, char oper2);

// 후위 표기법을 계산하는 함수
int evalPostfix(char *exp);

#define MAX_BUF_SIZE	256
#define NUM2CHAR(X)		(X) + '0'
#define CHAR2NUM(X)		(X) - '0'

int main()
{
	char input[MAX_BUF_SIZE] = { '\0', };
	char output[MAX_BUF_SIZE] = { '\0', };

	cout << "계산할 식을 입력해 주세요.(예: 3*8)" << endl;
	cin >> input;

	Infix2Postfix(input, output);

	cout << endl << "중위 표기법으로 변경된 수식" << endl;
	cout << output << endl;

	cout << "계산 결과는 : " << endl;
	cout << evalPostfix(output) << endl;

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


int evalPostfix(char *exp)
{
	int length = (int)strlen(exp);
	CStack<char>* pStack = CStack<char>::CreateS(MAX_BUF_SIZE);

	for (int i = 0; i < length; i++) {
		if (!isOperator(exp[i])) {
			pStack->push(exp[i]);
		}
		else {
			int num1 = CHAR2NUM(pStack->pop());
			int num2 = CHAR2NUM(pStack->pop());
			switch (exp[i])
			{
			case '+': pStack->push(NUM2CHAR(num2 + num1)); break;
			case '-': pStack->push(NUM2CHAR(num2 - num1)); break;
			case '*': pStack->push(NUM2CHAR(num2 * num1)); break;
			case '/': pStack->push(NUM2CHAR(num2 / num1)); break;
			}
		}
	}

	int res = CHAR2NUM(pStack->pop());

	CStack<char>::DeleteS(pStack);

	return res;
}

bool isLeftBracket(char input)
{
	return input == '(' ? true : false;
}

bool isRightBracket(char input)
{
	return input == ')' ? true : false;
}

void copy_buf(char* input, char* output)
{
	int length = (int)strlen(output);
	for (int i = 0; i < length; i++) {
		input[i] = output[i];
	}
}

bool Infix2Postfix_bracket(char* const input, char* output)
{
	static int call_num = 0;			// 괄호 카운트
	int length = (int)strlen(input);
	CStack<char>* pStack = CStack<char>::CreateS(MAX_BUF_SIZE);

	for (int i = 0; i < length; i++) {
		if (isLeftBracket(input[i])) {
			char output_temp[MAX_BUF_SIZE] = { 0, };
			call_num++;
			Infix2Postfix_bracket(&input[++i], output_temp);
			// output_temp 를 output 에 복사
			copy_buf(output, output_temp);
			i += (int)(strlen(output_temp));
			output += strlen(output_temp);
		}
		else if (isRightBracket(input[i])) {
			call_num--;
			// 남은 연산자 출력
			while (!pStack->empty()) {
				*output = pStack->pop();
				output++;
			}

			CStack<char>::DeleteS(pStack);
			return true;
		}
		else {
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
	}

	// 남은 연산자 출력
	while (!pStack->empty()) {
		*output = pStack->pop();
		output++;
	}

	CStack<char>::DeleteS(pStack);
	return (call_num == 0) ? true : false;
}