#include<bits/stdc++.h>
#include <iostream>
using namespace std;
class double_linedlist {
	struct Node {
		int data{};
		int indx{};
		Node* next{};
		Node* prev{};
		Node(int data, int indx) {
			this->data = data;
			this->indx = indx;
		};
		~Node() {
			delete next;
			delete prev;
		}
	};
	Node* head{};
	Node* tail{};
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
	void insert_back(int data, int indx) {
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
	void insert_front(int data, int indx) {
		++length;
		Node* node = new Node(data, indx);
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
	void insert_sorted(int data, int indx) {
		if (head == nullptr)insert_front(data, indx);
		else if (head == tail) {
			if (head->data > indx) {
				insert_front(data, indx);
			}
			else {
				insert_back(data, indx);
			}
		}
		else {
			Node* node = new Node(data, indx);//create a node
			Node* prev = head;//create a node
			for (Node* cur = head->next; cur != nullptr; cur = cur->next) {
				if (head->data >= indx) {
					insert_front(data, indx);
					return;
				}
				if (cur->data >= indx) {
					prev->next = node;
					node->next = cur;
					++length;
					return;
				}
				prev = prev->next;
			}
			insert_back(data, indx);
		}
		debug_verify_data_integrity();
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
			tail = tail->prev;
			tail->next = nullptr;
		}
		debug_verify_data_integrity();
	}
	void print() {
		for (Node* i = head; i; i = i->next)
			cout << i->data << " ";
		cout << "\n";
		/*for (Node* i = head; i; i = i->next)//print the index
			cout << i->indx << " ";*/
			//cout << "\n";
	}
	void printAll(int size) {
		int INDEX = 0;
		for (Node* i = head; i; i = i->next) {
			while (INDEX < i->indx) {
				cout << "0 ";
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
	bool change(int val, int indx) {
		for (Node* i = head; i; i = i->next) {
			if (i->indx == indx) {
				i->data = val;
				return true;
			}
		}
		return false;
	}
};
class ArrayLinkedList {
	int size = 0;
	double_linedlist dll;
	int indxlist = 0;
	int colist = 0;
public:
	int get_indxlist() {
		return indxlist;
	}
	ArrayLinkedList() {};
	ArrayLinkedList(int size) : size(size) {};
	ArrayLinkedList(int row, int col) :indxlist(row), size(col) {};
	ArrayLinkedList* nextlist{};
	ArrayLinkedList* prevlist{};
	void set_value(int val, int indxc) {
		dll.insert_sorted(val, indxc);
	}
	int get_value(int indx) {
		if (dll.get_node(indx))
			return dll.get_node(indx)->data;
		else
			return INT_MAX;
	}
	void print_array_nonzero() {//non zero
		dll.print();
	}
	void print_array() {//All zero
		dll.printAll(size);
	}
	void add(ArrayLinkedList& arrlst) {
		dll.add(arrlst.dll);
	}
	bool change(int val, int indx) {
		return dll.change(val, indx);
	}
};
class SparseMatrix {
	int col{};
	int row{};
	ArrayLinkedList* headlist{};
	ArrayLinkedList* taillist{};
public:
	SparseMatrix(int r, int c) :row(r), col(c) {};
	bool changeval(int val, int indxr, int indxc) {
		for (ArrayLinkedList* j = headlist; j; j = j->nextlist) {
			if (j->get_indxlist() == indxr && checkexist(j->get_indxlist()) != nullptr) {
				if (j->change(val, indxc) == true) {
					return true;
				}
			}
		}
		return false;
	}
	void set_value(int val, int indxr, int indxc) {
		bool getin = false;
		if (changeval(val, indxr, indxc) == true) {
			return;
		}
		for (ArrayLinkedList* i = headlist; i; i = i->nextlist) {
			if (headlist == nullptr && taillist == nullptr) {
				break;
			}
			else if (i->get_indxlist() == indxr) {
				i->set_value(val, indxc);
				getin = true;
				break;
			}
			else if (i && i->nextlist == nullptr) {
				i->nextlist = new ArrayLinkedList(indxr, col);
				i->nextlist->set_value(val, indxc);
				getin = true;
				break;
			}
		}
		if (headlist == nullptr && taillist == nullptr) {
			headlist = new ArrayLinkedList(indxr, col);
			headlist->set_value(val, indxc);
			taillist = headlist;
		}
		else if (getin == false)
		{
			headlist = new ArrayLinkedList(indxr, col);
			headlist->set_value(val, indxc);
		}
	}
	void print() {
		int counter = 0;
		while (counter < col) {
			ArrayLinkedList* temp = checkexist(counter);
			if (temp != nullptr) {
				temp->print_array();
				counter++;
			}
			else {
				int tmp = col;
				while (tmp--)cout << 0 << " ";
				cout << "\n";
				++counter;
			}
		}
	}
	ArrayLinkedList* checkexist(int indxrow) {
		for (ArrayLinkedList* i = headlist; i; i = i->nextlist) {
			if (i->get_indxlist() == indxrow)return i;
		}
		return nullptr;
	}
	void add(SparseMatrix& y) {
		for (ArrayLinkedList* j = y.headlist; j; j = j->nextlist) {//looping on the y sparseMat
			ArrayLinkedList* temp = checkexist(j->get_indxlist());//check that the same row is exist in current sparseMat
			if (temp != nullptr) {
				temp->add(*j);
			}
			else {
				for (int q = 0; q < row; q++) {
					if (j->get_value(q) != INT_MAX)
						set_value(j->get_value(q), j->get_indxlist(), q);
				}
			}
		}
	}
	void print_nonzero() {
		int counter = 0;
		while (counter < col) {
			ArrayLinkedList* temp = checkexist(counter);
			if (temp != nullptr) {
				temp->print_array_nonzero();
				counter++;
			}
			else {
				++counter;
			}
		}
	}
};
int main() {
	SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	mat.print_nonzero();
	cout << "\n";
	mat.print();
	cout << "\n===\n";
	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9); 

	mat2.print_nonzero();
	mat2.print();
	cout << "\n===\n";
	mat.add(mat2);
	mat.print();
	mat.print_nonzero();
	return 0;
}
