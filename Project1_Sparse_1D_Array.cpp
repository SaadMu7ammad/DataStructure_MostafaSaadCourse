#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class double_linedlist {
	struct Node {
		int data{};
		int indx{};
		Node* next{};
		Node* prev{};
		Node(int data,int indx)  {
			this->data = data;
			this->indx = indx;
		};
		~Node() {
			delete next;
			delete prev;
		}
	};
	Node* head{};
	Node*tail{};
	int length = 0;
	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		}
		else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length - 1)	// make sure we end at tail
				assert(cur == tail);
		}
		assert(length == len);
		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length - 1)	// make sure we end at head
				assert(cur == head);
		}
	}
public:
	double_linedlist() {};
	double_linedlist(const double_linedlist&) = delete;
	double_linedlist& operator=(const double_linedlist& another) = delete;
	Node* get_node(int indx) {
		for (Node* i = head; i; i = i->next) {
			if (i->indx == indx) {
				return i;
			}
		}
		return nullptr;
	}
	void insert_back(int data,int indx) {
		++length;
		Node* node = new Node(data, indx);
		if (head == nullptr) {
			head = tail = node;
		}
		else {
			tail->next = node;
			node->prev = tail;
			tail = node;
			tail->next = nullptr;
		}
		debug_verify_data_integrity();
	}
	void insert_front(int data,int indx) {
		++length;
		Node* node = new Node(data,indx);
		if (head == nullptr) {
			head = tail = node;
		}
		else {
			head->prev = node;
			node->next = head;
			head = node;
		}
		debug_verify_data_integrity();
	}
	void insert_sorted(int data,int indx) {
		Node* node = new Node(data,indx);
		node->indx = indx;
		if (head == nullptr) {
			++length;
			head = tail = node;
		}
		else if (head == tail) {
			//if (head->data > data) {
				if (head->indx > indx) {
				insert_front(data,indx);
			}
			else {
				insert_back(data, indx);
			}
		}
		//else if (tail->data <= data) {
		else if (tail->indx <= indx) {
			insert_back(data, indx);
		}
		else {
			for (Node* i = head; i; i = i->next){
				//if (i->data >= data) {
					if (i->indx >= indx) {
					//the prev and next linking
					i->prev->next = node;
					node->prev = i->prev;
					node->next = i;
					i->prev = node;
					++length;
					debug_verify_data_integrity();
					break;
				    }
			}
		}
		
	}
	void pop_front() {
		if (head == nullptr) {
			return;
		}
		else if (head == tail) {
			--length;
			head = tail = nullptr;
		}
		else {
			--length;
			head = head->next;
			head->prev = nullptr;
		}
		debug_verify_data_integrity();
	}
	void pop_back() {
		if (head == nullptr) {
			return;
		}
		else if (head == tail) {
			--length;
			head = tail = nullptr;
		}
		else {
			--length;
			tail=tail->prev ;
			tail->next = nullptr;
		}
		debug_verify_data_integrity();
	}
	void print() {
		for (Node* i = head; i; i = i->next)
			cout << i->data << " ";
		cout << "\n";
		for (Node* i = head; i; i = i->next)
			cout << i->indx << " ";
		cout << "\n";
	}
	void printAll(int size) {
		int INDEX = 0;
		for (Node* i = head; i; i = i->next) {
			while (INDEX < i->indx) {
				cout<< "0 ";
				INDEX++;
			}
			cout << i->data << " ";
			++INDEX;
		}
		while (INDEX < size) {
			cout << "0 ";
			INDEX++;
		}
		cout << "\n";
	}
	void add(double_linedlist& arlist) {
		for (Node* i = head; i; i = i->next) {
			if (arlist.get_node(i->indx)) {
				i->data += arlist.get_node(i->indx)->data;
			}
		}
		for (Node* j = arlist.head; j; j = j->next) {
			if (get_node(j->indx) == nullptr) {
				insert_sorted(j->data, j->indx);
			}
		}
	}
};
class ArrayLinkedList {
	int size = 0;
	double_linedlist dll;
public:
	ArrayLinkedList(int size) :size(size) {};
	void set_value(int val, int indx) {
		dll.insert_sorted(val,indx);
	}
	int get_value( int indx) {
		if (dll.get_node(indx))
			return dll.get_node(indx)->data;
		else
			return 0;
	}
	void print_array_nonzero() {//non zero
		dll.print();
	}
	void print_array() {//All zero
		dll.printAll(size);
	}
	void add(ArrayLinkedList &arrlst) {
		dll.add(arrlst.dll);
	}
};
int main(){
	ArrayLinkedList arr(10);
	arr.set_value(50, 5);
	arr.set_value(20, 2);
	arr.set_value(70, 7);
	arr.set_value(40, 4);
	arr.print_array();
	arr.print_array_nonzero();//non zero
	cout << arr.get_value(7) << "\n";
	ArrayLinkedList arr2(10);
	arr2.set_value(1, 4);
	arr2.set_value(3, 7);
	arr2.set_value(4, 6);
	arr.add(arr2);
	arr.print_array();
	return 0;
}

