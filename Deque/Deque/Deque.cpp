#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class Deque {
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
	Deque(int size) :rear(0), front(0), size(size), length(0) {
		arr = new int[size];
	}
	void enqueue_rear(int num) {//add from the rear(the right direction) so the rear shifted to the right (+1)
		assert(!isFull());
		arr[rear] = num;
		rear = next(rear);
		length++;
	}
	void enqueue_front(int num) {//add from the rear(the right direction) so the rear shifted to the right (+1)
		assert(!isFull());
		front = prev(front);
		arr[front] = num;
		length++;
	}
	int dequeue_front() {//remove from the front(the left direction) so the top shifted to the right (+1)
		assert(!isEmpty());
		int val = arr[front];
		front = next(front);
		length--;
		return val;
	}
	int dequeue_rear() {//remove from the front(the left direction) so the top shifted to the right (+1)
		assert(!isEmpty());
		rear = prev(rear);
		int val = arr[rear];
	
		//rear = prev(rear);
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
		cout << "\nFront = " << arr[front]  <<" \t Rear = " <<arr[prev(rear)]<< "\n";
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
	int next(int indx) {
		//return arr[(indx + 1) % size]; //nice way but the if more effecient
		++indx;
		if (indx == size)indx = 0;
		return indx;
	}
	int prev(int indx) {
		if (indx == 0) {
			indx = size - 1;
			return indx;
		}
		--indx;
		return indx;
	}
	~Deque() {
		delete[]arr;
	}
};
int main()
{
	Deque dq(6);

	dq.enqueue_front(3);
	dq.print();
	dq.enqueue_front(2);
	dq.enqueue_rear(4);
	dq.enqueue_front(1);
	dq.enqueue_front(5);
	dq.enqueue_front(6);
	dq.print();	
	cout << dq.dequeue_rear() << "\n";	
	dq.print();	
	cout << dq.dequeue_front() << "\n";
	dq.print();	
	cout << dq.dequeue_rear() << "\n";
	cout << dq.dequeue_front() << "\n";	

	while (!dq.isEmpty())
		dq.dequeue_rear();
	dq.print();	//
	for (int i = 0; i < 6; ++i)
		dq.enqueue_rear(i + 10);
	dq.print();	//


	return 0;
}
