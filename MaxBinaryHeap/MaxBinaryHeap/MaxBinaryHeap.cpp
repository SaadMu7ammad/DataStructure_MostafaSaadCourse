#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class MaxHeap {//We can use MaxHeap class based on negative elements stored in MinHeap
private:
	int* array{};
	int capacity{ 1000 };
	int size{};

	int left(int nodepos) {

		int pos = (2 * nodepos) + 1;
		return pos >= size ? -1 : pos;
	}
	int right(int nodepos) {

		int pos = (2 * nodepos) + 2;
		return pos >= size ? -1 : pos;
	}
	int parent(int nodepos) {

		int pos = floor((nodepos - 1) / 2);
		return pos >= size || nodepos == 0 ? -1 : pos;
	}
	void heapify() {	// O(n)
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}
	void heapify_up(int childindx) {//log(n)
		if (childindx == 0 || array[childindx] < array[parent(childindx)])
			return;
		swap(array[childindx], array[parent(childindx)]);
		heapify_up(parent(childindx));
	}
	void heapify_down(int parentindx) {//log(n)
		if (left(parentindx) == -1)//leaf node
			return;

		if (array[parentindx] >max(array[left(parentindx)], array[right(parentindx)]))
			return;

		int biggerindx;
		if (right(parentindx) != -1 && array[left(parentindx)] > array[right(parentindx)]) {
			biggerindx = left(parentindx);
		}
		else {
			biggerindx = right(parentindx);
		}
		if (array[biggerindx] > array[parentindx]) {
			swap(array[parentindx], array[biggerindx]);
			heapify_down(biggerindx);
		}
	}
public:
	MaxHeap() {
		array = new int[capacity];
		size = 0;

	}
	MaxHeap(const vector<int>& v) {
		assert((int)v.size() <= capacity);
		array = new int[capacity] {};
		size = v.size();

		for (int i = 0; i < (int)v.size(); ++i)
			array[i] = v[i];

		heapify();
	}

	~MaxHeap() {
		delete[]array;
		array = nullptr;
	}


	bool isEmpty() {
		return size > 0 ? false : true;
	}
	int top() {
		if (!isEmpty())
			return array[0];
	}

	void push(int num) {
		if (size < capacity) {
			array[size++] = num;
			heapify_up(size - 1);
		}
	}
	void pop() {//log(n)
		if (!isEmpty()) {
			array[0] = array[--size];
			heapify_down(0);
		}
	}
};

void creat_heap_nlogn() {
	MaxHeap heap;

	vector<int> v{ 2, 17, 22, 10, 8, 37,
		14, 19, 7, 6, 5, 12, 25, 30 };

	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

	while (!heap.isEmpty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
	// 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}
void creat_heap_n() {
	vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	MaxHeap heap(v);

	//h.print();
	while (!heap.isEmpty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
}

int main()
{

	creat_heap_nlogn();
	cout << "\n\n\n\n";
	creat_heap_n();
	return 0;
}


