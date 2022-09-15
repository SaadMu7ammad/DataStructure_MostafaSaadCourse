#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class Queue {
private:
	int front;
	int rear;
	int size;
	int length;//added elements
	int* arr;
public:
	int isFull() {
		return length == size;
	}
	int isEmpty() {
		return length == 0;
	}
	Queue(int size) :rear(0), front(0), size(size), length(0) {
		arr = new int[size];
	}
	void enqueue(int num) {//add from the rear(the right direction) so the rear shifted to the right (+1)
		assert(!isFull());
		arr[rear] = num;
		rear = next(rear);
		length++;
	}
	int dequeue() {//remove from the front(the left direction) so the top shifted to the right (+1)
		assert(!isEmpty());
		int val = arr[front];
		front = next(front);
		length--;
		return val;
	}
	void print() {
		if (length == 0) {
			cout << "Queue is Empty!\n";
			return;
		}
		if (length == size) {
			cout << "Queue is Full!\n";
		}
		int temp = length;
		int temptop = front;
		int i = front % size;
		while (temp--) {
			cout << arr[i] << " ";
			++temptop;
			i = (temptop) % size;
		}
		cout << "\n";
	}
	void print_2ndway() {
		cout << "\nFront = " << arr[front] << "\tRear =" << arr[rear] << "\n";
		if (length == 0) {
			cout << "Queue is Empty!\n";
			return;
		}
		if (length == size) {
			cout << "Queue is Full!\n";
		}
		//int templen = length;
		for (int i = front, templen = length; templen > 0; i = next(i), --templen) {
			cout << arr[i] << " ";
			//--templen;
		}
		cout << "\n";
	}
	int front_val() {
		assert(!isEmpty());
		return arr[front];
	}
	int next(int indx) {
		//return arr[(indx + 1) % size]; //nice way but the if more effecient
		++indx;
		if (indx == size)indx = 0;
		return indx;
	}
	~Queue() {
		delete[]arr;
	}
};
class Stack {
private:
	Queue q;
	int added_elements{};
	void mimic_stack() {
		int temp = added_elements;
		while (temp--) {
			int num=q.dequeue();
			q.enqueue(num);
		}
	}
public:
	Stack(int size) :
		q(size) {
	}

	void push(int num) {
		
		q.enqueue(num);
		mimic_stack();
		++added_elements;
	}
	int pop() {
		mimic_stack();
		int del= q.dequeue();
		--added_elements;
		mimic_stack();
		return del;
	}
	int peek() {
		return q.front_val();
		
	}
	int isFull() {
		return q.isFull();
	}
	void print() {
		q.print();
	}
};
int main()
{
	/*
	The relation between the stack and queue 
	Stack 1 2 3 4 5
				  ^
				 Top

	Queue 1 2 3 4 5
		  ^		  ^
		Front    Rear

	NOW THE DIFF THE PTR FRONT AND TOP IST REVERSE!
	SO....
	IF I WANT TO ADD 6 IN BOTH W'LL BE 

	Stack 1 2 3 4 5 6
				    ^
				   Top

	Queue 1 2 3 4 5 6
		  ^		    ^
		Front      Rear

	
	BUT IF I WANT TOUS STACK AS A QUEUE
	WILL ADD THE 6 IN THE QUEUE
	THE DELETE FROM FRONT(DEQUEU) AND ADD IT AGAIN AT END(ENQUEUE)
	Queue 1 2 3 4 5 6
		  ^		    ^
		Front      Rear

		del 1   >> 2 3 4 5 6
		add 1 at end (enqueu)   >> 2 3 4 5 6 1

		del 2   >>  3 4 5 6
		add 2 at end (enqueu)   >> 3 4 5 6 1 2

		del 3   >>  4 5 6
		add 3 at end (enqueu)   >>  4 5 6 1 2 3

		del 4   >>   5 6
		add 4 at end (enqueu)   >> 5 6 1 2 3 4

		del 5   >>  6
		add 5 at end (enqueu)   >> 6 1 2 3 4 5
								   ^         ^
								 front      rear

	 NOW 6 BECOME AT THE FRONT AND ALSO AT THE TOP IF WE USE STACK DIRECT


	*/
	Stack st(10);
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	st.print();
	cout<<st.peek()<<"\n";
	st.pop();
	st.print();
	cout << st.peek() << "\n";
	st.push(6);
	st.push(9);
	st.print();
	cout << st.peek() << "\n";
	st.pop();
	cout << st.peek() << "\n";
	st.print();


	return 0;
}
