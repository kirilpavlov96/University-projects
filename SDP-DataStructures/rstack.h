/*
 * rstack.h
 *
 *  Created on: 26.03.2015 г.
 *      Author: trifon
 */

#ifndef RSTACK_H_
#define RSTACK_H_

#include "abstract_stack.h"

class ResizingStack : public AbstractStack<int> {
private:
	int* a;
	int top;
	int capacity;

	bool full() const;

	void resize();

	void copy(ResizingStack const&);
	void erase();

public:

	ResizingStack();

	ResizingStack(ResizingStack const&);

	ResizingStack& operator=(ResizingStack const&);

	bool empty() const;

	int peek() const;

	void push(int const&);

	int pop();

	~ResizingStack();

};



#endif /* RSTACK_H_ */
