/*
 * lstack.cpp
 *
 *  Created on: Feb 14, 2016
 *      Author: kiko
 */

#ifndef LSTACK_CPP_
#define LSTACK_CPP_

#include <iostream>
using namespace std;

template<typename T>
struct StackElement {
	T data;
	StackElement* next;
};

template<typename T>
class LinkedStack {
private:
	StackElement<T>* top;

public:
	// ��������� �� ������ ����
	LinkedStack();

	// ����������� �� ��������
	LinkedStack(LinkedStack const&);

	// �������� �� �����������
	LinkedStack& operator=(LinkedStack const&);

	// ���������

	// �������� ���� ���� � ������
	bool empty() const;

	// �������� �� �������� �� ����� �� �����
	T peek() const;

	// ��������

	// ��������� �� �������
	void push(T const&);

	// ���������� �� �������
	T pop();

	// ����������
	~LinkedStack();
};

template<typename T>
LinkedStack<T>::LinkedStack() {
	top = NULL;
}

template<typename T>
bool LinkedStack<T>::empty() const {
	return top == NULL;
}

template<typename T>
T LinkedStack<T>::peek() const {
	if (empty()) {
		cout << "������: ���� �� ���������� � ������ ����!\n";
		return 0;
	}

	return top->data;
}

template<typename T>
void LinkedStack<T>::push(T const& x) {
	StackElement<T>* p = new StackElement<T>;
	p->data = x;
	p->next = top;
	top = p;
}

template<typename T>
T LinkedStack<T>::pop() {
	if (empty()) {
		cout << "������: ���� �� ���������� �� ������ ����!\n";
		return 0;
	}
	// top != NULL

	StackElement<T>* p = top;
	top = top->next;
	T x = p->data;
	delete p;
	return x;
}

template<typename T>
LinkedStack<T>::~LinkedStack() {
	/*
	 * while (!empty())
	 pop();
	 */
	StackElement<T>* toDelete;
	while (top != NULL) {
		toDelete = top;
		top = top->next;
		delete toDelete;
	}
	// top == NULL
}

template<typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls) :
		top(NULL) {
	/*
	 while (!ls.empty()) {
	 push(ls.pop());
	 }
	 */
	/*
	 StackElement* toCopy = ls.top;
	 while(toCopy != NULL) {
	 push(toCopy->data);
	 toCopy = toCopy->next;
	 }
	 */
	*this = ls;
	// this->operator=(ls);
	// operator=(ls);

}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& ls) {
	if (this != &ls) {
		// !!! ~LinkedStack();
		while (!empty())
			pop();

		StackElement<T>* toCopy = ls.top;
		StackElement<T> *copy, *lastCopied = NULL;
		while (toCopy != NULL) {
			copy = new StackElement<T>;

			if (top == NULL)
				top = copy;

			copy->data = toCopy->data;

			if (lastCopied != NULL)
				lastCopied->next = copy;

			// ����������� �� �����������
			lastCopied = copy;
			toCopy = toCopy->next;
		}
		lastCopied->next = NULL;
	}
	return *this;
}

#endif

