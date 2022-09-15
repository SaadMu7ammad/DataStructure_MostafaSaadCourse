#include <iostream>
#include <Bits/stdc++.h>
using namespace std;
//typedef char type;
typedef int type;

class Stack {
private:
	int size{ };
	int top{ };
	int* array{ };
public:
	Stack(int size) :
		size(size), top(-1) {
		array = new int[size];
	}
	
	~Stack() {
		delete[] array;
	}

	void push(int x) {
		assert(!isFull());
		array[++top] = x;
	}

	int pop() {
		assert(!isEmpty());
		return array[top--];
	}

	int peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void print() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};
class Queue {
private:
	int added_elements{};
	int size;
	Stack s1;
	Stack s2;
    
	void move(Stack & from, Stack & to) {		// O(n)
		while (!from.isEmpty())
			to.push(from.pop());
	}
    
public:
	int isEmpty() {
        return added_elements ==0;
    }
    int isFull() {
        return added_elements == size;
    }
	Queue(int size) :
		size(size), s1(size), s2(size) {
	}
	
		void enqueue(int value) {	// O(n)
			assert(!isFull());
			move(s1, s2);
			s1.push(value);
			move(s2, s1);
			added_elements++;
		}

	
	int dequeue() {// O(1)
		assert(!isEmpty());
		int value = s1.pop();
		--added_elements;
		return value;
	}
	void print() {
		s1.print();
	}
	
	
};

int main()
{
    Queue q(6);
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
    q.print();
	q.dequeue();
	q.dequeue();
	q.print();
	q.enqueue(7);
	q.enqueue(9);
	q.print();

}