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
	Queue(int size) :rear(0), front(0), size(size),length(0) {
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
		while( temp--) {
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
		for (int i = front, templen = length; templen > 0; i=next(i), --templen) {
			cout << arr[i]<<" ";
			//--templen;
		}
		cout << "\n";
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
int main()
{
	Queue q(5);
	q.enqueue(5);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(9);
	q.dequeue();
	q.print();
	q.enqueue(4);
	q.enqueue(3526);
	q.print();
	q.dequeue();
	q.dequeue();
	q.print();
	q.enqueue(99);
	q.print();
	q.enqueue(55);
	q.print();
	q.print_2ndway();




return 0;
}
