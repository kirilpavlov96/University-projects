/*
 * squeue.cpp
 *
 *  Created on: Feb 14, 2016
 *      Author: kiko
 */
#include <iostream>
using namespace std;

const int MAX = 100;

template <typename T>
class StaticQueue {
	T a[MAX];
	int front, back;

	bool full() const {
		return front == (back + 2) % MAX;
	}

public:
	StaticQueue() : front(0), back(-1) {}

	// O(1)
	bool empty() const {
		return front == (back + 1) % MAX;
	}

	// O(1)
	void enqueue(T const& x) {
		if (full())
			cerr << "���� �� ��������� � ����� ������!\n";
		else
			a[++back %= MAX] = x;
	}

	// O(1)
	T dequeue() {
		if (empty()) {
			cerr << "���� �� ���������� �� ������ ������!\n";
			return T();
		} else {
			T x = head();
			++front %= MAX;
			return x;
		}

	}

	// O(1)
	T head() const {
		if (empty()) {
			cerr << "���� �� ���������� � ������ ������!\n";
			return T();
		}
		return a[front];
	}
};





