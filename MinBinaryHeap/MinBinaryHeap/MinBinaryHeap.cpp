#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//NOTICE
/*
INSERT >> HEAPIFY UP
DELETE >> HEAPIFY DOWN
*/
class MinHeap {//We can use MaxHeap class based on negative elements stored in MinHeap
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
	void heapify() {	// O(n)//build the tree
		for (int i = size / 2 - 1; i >= 0; --i)
			heapify_down(i);
	}
	void fullheapify() {	// O(n)
		for (int i = size - 1; i >= 0; --i)
			heapify_down(i);
	}
	void heapify_up(int childindx) {//log(n)
		if (childindx == 0 || array[childindx] > array[parent(childindx)])
			return;
		swap(array[childindx], array[parent(childindx)]);
		heapify_up(parent(childindx));
	}
	void heapify_down(int parentindx) {//log(n)
		if (left(parentindx) == -1)//leaf node
			return;

		if (array[parentindx] < min(array[left(parentindx)], array[right(parentindx)]))
			return;

		int smallerindx;
		if (right(parentindx) != -1 && array[left(parentindx)] > array[right(parentindx)]) {
			smallerindx = right(parentindx);
		}
		else {
			smallerindx = left(parentindx);
		}
		if (array[smallerindx] < array[parentindx]) {
			swap(array[parentindx], array[smallerindx]);
			heapify_down(smallerindx);
		}
	}
	bool is_heap(int parent_pos) {	// O(n)
		if (parent_pos == -1)
			return true;

		int left_child = left(parent_pos);
		int right_child = right(parent_pos);

		if (left_child != -1 && array[parent_pos] > array[left_child])
			return false;

		if (right_child != -1 && array[parent_pos] > array[right_child])
			return false;

		return is_heap(left_child) && is_heap(right_child);
		// Tip we can optimize by stopping with the first leaf node
	}
public:
	MinHeap() {
		array = new int[capacity];
		size = 0;

	}
	MinHeap(const vector<int>& v) {
		assert((int)v.size() <= capacity);
		array = new int[capacity] {};
		size = v.size();

		for (int i = 0; i < (int)v.size(); ++i)
			array[i] = v[i];

		heapify();
	}

	~MinHeap() {
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
			heapify_down(0);//we swap the parent and remove it 
		}
	}
	void print_less_than(int val, int parent_indx = 0) {//print values < val in heap
		if (parent_indx == -1 || array[parent_indx] >= val) {
			return;
		}
		cout << array[parent_indx] << " ";
		print_less_than(val, left(parent_indx));
		print_less_than(val, right(parent_indx));

		//OR THAT
		/*if (parent_indx == 0 ) {
			cout<<top()<<" ";
		}
		if (array[left(parent_indx)] < val&& left(parent_indx) !=-1) {
			cout << array[left(parent_indx)] << " ";
			print_less_than(val, left(parent_indx));
		}
		if (array[right(parent_indx)] < val&& right(parent_indx)!=-1) {
			cout << array[right(parent_indx)] << " ";
			print_less_than(val, right(parent_indx) );
		}
		*/
	}
	bool isHeap(int* p, int n) {

		//u want to check the array without making a tree

		int* tempstorage = array;
		int tempsize = size;

		array = p;
		size = n;

		int res = is_heap(0);

		size = tempsize;
		array = tempstorage;

		return res;
	}
	void heap_sort(int* p, int n) {
		if (n <= 1)
			return;
		int* tempstorage = array;
		int tempsize = size;

		array = p;//put the address of p so modifying in array is actually in p
		size = n;// so p modifying directly 
		heapify();//build the heap tree
		//cout << "BEFORE SORT ONLY BUILD\n";
		//for (int i = 0; i < size; ++i)cout << array[i] << " ";
		//cout << '\n';
		//cout << "sorted\n";

		while (size--) {	//O(nlogn)
			swap(array[0], array[size]);
			heapify_down(0);// swap top and recorrect the path it 
		}
		// the same concept below 

		/*while(!isEmpty()) {
			cout<<top()<<" ";
			pop();
		}*/

		// reverse
		for (int i = 0; i < n / 2; ++i)
			swap(array[i], array[n - i - 1]);

		size = tempsize;
		array = tempstorage;
	}
};

void creat_heap_nlogn() {
	MinHeap heap;

	//vector<int> v{ 2, 17, 22, 10, 8, 37,14, 19, 7, 6, 5, 12, 25, 30 };
	vector<int> v{ 2,6,8,14,7,10,19,37,25,30,12,22,17 };

	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

	while (!heap.isEmpty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
	// 2 5 6 7 8 10 12 14 17 19 22 25 30 37
}

void is_heap_array() {
	//vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	vector<int> v{ 2,6,8,14,7,10,19,37,25,30,12,22,17 };
	MinHeap heap(v);

	//int arr[]{ 2, 5, 12, 7,6, 22, 14, 19, 10, 17, 8, 37, 25, 30 };
	int arr[]{ 2,6,8,14,7,10,19,37,25,30,12,22,17 };
	cout << heap.isHeap(arr, 13) << "\n";	// 1
	swap(arr[0], arr[5]);
	cout << heap.isHeap(arr, 13) << "\n";	// 0
}
void sort_heap() {


	const int SZ = 13;
	//int arr[SZ]{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
	int arr[SZ]{ 2,6,8,14,7,10,19,37,25,30,12,22,17 };
	MinHeap heap;

	heap.heap_sort(arr, SZ);

	for (int i = 0; i < SZ; ++i)cout << arr[i] << " ";

	cout << "\n";

}
int main()
{

	creat_heap_nlogn();
	cout << "\n\n\n";
	vector<int> v{ 2, 17, 22, 10, 8, 37,14, 19, 7, 6, 5, 12, 25, 30 };
	MinHeap h(v);
	cout << "\n\n";


	h.print_less_than(10);
	cout << "\n\n";
	is_heap_array();
	cout << "\n\n";
	sort_heap();
	return 0;
}


