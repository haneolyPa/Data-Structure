#pragma once

#include <iostream>

template<class T>
class CStack
{
public:
	explicit CStack(int stackSize) : m_top(-1), m_stackSize(stackSize), m_pData(new T[stackSize]) {
	}

	~CStack() {
		delete[] m_pData;
	}

public:
	static CStack* CreateS(int stackSize) {			// 스택을 만드는 함수
		return new CStack(stackSize);
	}

	static void DeleteS(CStack* pStack) {
		delete pStack;
		pStack = NULL;
	}

public:
	bool isFull() {
		return ((m_top + 1) == m_stackSize);
	}

	bool empty() {
		return (m_top < 0);
	}

	void push(T data) {
		if (isFull()) {
			_showErrorMessage_push();
			return;
		}

		m_pData[++m_top] = data;
	}

	T pop() {
		if (empty()) {
			_showErrorMessage_push();
			return NULL;
		}
		return m_pData[m_top--];
	}

	int getSize() {
		return m_top + 1;
	}

	void show() {
		std::cout << "┌───┐" << std::endl;
		for (int i = m_top; i >= 0; i--) {
			std::cout << "  " << m_pData[i] << std::endl;
		}
		std::cout << "└───┘" << std::endl;
	}

private:
	void _showErrorMessage_push() {

	}

	void _showErrorMessage_pop() {
	}

private:
	int m_top;
	int m_stackSize;
	T* m_pData;
};

