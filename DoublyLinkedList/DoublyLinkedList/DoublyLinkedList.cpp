#include<iostream>
#include<Bits/stdc++.h>
#include<algorithm>
using namespace std;
struct Node {
    int data{ };
    Node* next{ };
    Node* prev{ };	 // Previous node!(for >> Doubly LinkedList)
    Node(int data) : data(data) {}
    void set(Node* next, Node* prev) {
        this->next = next;
        this->prev = prev;
    }
    ~Node() {
      //  cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};
class LinkedList {
private:
	Node* head{ };
	Node* tail{ };
	int length = 0;
	// let's maintain how many nodes
	vector<Node*> debug_data;	// add/remove nodes you use
	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}
public:
	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList& another) = delete;

	void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}
	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}

		if (node->prev == nullptr)
			cout << "X\t";
		else
			cout << node->prev->data << "\t";

		cout << " <= [" << node->data << "]\t => \t";

		if (node->next == nullptr)
			cout << "X\t";
		else
			cout << node->next->data << "\t";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}

	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

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
		assert(length == (int)debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length - 1)	// make sure we end at head
				assert(cur == head);
		}
		//cout << "\n";
	}
	////////////////////////////////////////////////////////////
	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}
	void print_reversed() {
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << "\n";
	}
	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}
	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}
	////////////////////////////////////////////////////////////
	void insert_end(int num) {
		Node* node = new Node(num);
		add_node(node);
		if (head == nullptr) {
			head = tail = node;
		}
		else {
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
		debug_verify_data_integrity();
	}
	void insert_front(int num) {
		Node* node = new Node(num);
		add_node(node);
		if (head == nullptr) {
			head = tail = node;
		}
		else {
			node->next = head;
			head->prev = node;
			head = node;
		}
		debug_verify_data_integrity();
	}
	void insert_sorted(int num) {
		Node* node = new Node(num);
		if (length == 0||head == nullptr||head->data>=num) {
			insert_front(num);
		}
		else if (tail->data<=num) {
			insert_end(num);
		}
		else {
			for (Node* i = head; i != nullptr; i = i->next) {
				if (i->data >= num ) {//insert before i node
					i->prev->next = node;
					node->prev = i->prev;
					i->prev = node;
					node->next = i;
					add_node(node);
					debug_verify_data_integrity();
					return;
				}
			}
		}
	}
	void delete_front() {
		if (head == nullptr) {
			return ;
		}
		else if (head == tail) {
			delete_node(head);
			head = tail = nullptr;
		}
		else {
			Node* second = head->next;
			delete_node(head);
			
			head = second; 
			head->prev = nullptr;
		}
		debug_verify_data_integrity();
	}
	void delete_end() {
		if (head == nullptr) {
			return;
		}
		else if (head == tail) {
			delete_node(head);
			head = tail = nullptr;
		}
		else {
			Node* before = tail->prev;
			delete_node(tail);
			tail=before;
			tail->next = nullptr;
		}
		debug_verify_data_integrity();
	}
	Node* delete_and_link(int num) { //return the prev node of the deleted node 
		
			for (Node* i = head; i; i = i->next) {
				if (head->data == num) {
					delete_front();
					return head;
				}
				else if (tail->data == num) {
					delete_end();
					return tail;
				}
				else if (i->data == num)
				{
					Node* before = i->prev;
					before->next = i->next;
					i->next->prev = before;
					delete_node(i);
					return before;
				}
			}
		debug_verify_data_integrity();
	}
	void delete_and_linkvoid(int num) { //No return 
		for (Node* i = head; i; i = i->next) {
			if (head->data == num) {
				delete_front();
				break ;
			}
			else if (tail->data == num) {
				delete_end();
				break;
			}
			else if (i->data == num)
			{
				Node* before = i->prev;
				before->next = i->next;
				i->next->prev = before;
				delete_node(i);
				break;
			}
		}
		debug_verify_data_integrity();
	}
	void delete_allnum(int num) {
		for (Node* i = head; i; i = i->next) {
			if (i->data == num) {
				i=delete_and_link(num);
			}
		}
	}
	void delete_odd_indxs() {
		if (length <= 1) {
			debug_verify_data_integrity();
			return;
		}
		for (Node* i = head; i&&i->next;  ) {
				 delete_and_linkvoid(i->next->data);
				 i = i->next;
		}
		debug_verify_data_integrity();
	}
	void delete_even_indxs() {
		insert_front(INT_MIN);
		if (length <= 1) {
			debug_verify_data_integrity();
			return;
		}
		for (Node* i = head; i && i->next; ) {
			delete_and_linkvoid(i->next->data);
			i = i->next;
		}
		delete_front();
		debug_verify_data_integrity();
	}
	void is_palindrome() {
		if (head == nullptr)return;
		if (head == tail) {
			cout << "a palindrome\n";
			return;
		}
		Node* _head = head;
		Node* _tail= tail;

		while (_head->data == _tail->data) {
			_head = _head->next;
			_tail = _tail->prev;
			if (_head == _tail) {
				cout << "a palindrome\n";
				return;
			}
		}
		cout << "Not a palindrome\n";
		return;
	}
};
int main()
{
	LinkedList dlist;
	dlist.insert_end(5);
	dlist.insert_end(7);
	dlist.print();
	dlist.insert_end(12);
	dlist.print();
	dlist.print_reversed();
	dlist.insert_front(66);
	dlist.insert_front(3);
	dlist.insert_front(4);
	dlist.print();
	dlist.print_reversed();
	dlist.print();
	dlist.delete_front();
	dlist.print();
	dlist.insert_front(66);
	dlist.insert_end(66);
	dlist.insert_end(55);
	dlist.insert_end(7);
	dlist.insert_front(66);
	dlist.insert_front(4);
	dlist.print();
	//dlist.delete_and_link(5);
	//dlist.print();
	//dlist.print_reversed();
	//dlist.delete_and_link(7);
	//dlist.print();
	//dlist.print_reversed();
	/*dlist.delete_and_link(12);
	dlist.print();
	dlist.print_reversed();
	dlist.delete_and_link(1324);
	dlist.print();
	dlist.print_reversed();
	dlist.delete_and_link(66);
	dlist.print();
	dlist.print_reversed();*/

	//dlist.delete_front();
	//dlist.delete_front();
	//dlist.delete_front();
	//dlist.delete_front();
	/*dlist.delete_end();
	dlist.delete_end();
	dlist.delete_end();*/
	/*dlist.print();
	dlist.print_reversed();*/

	/*dlist.delete_allnum(4);
	dlist.print();
	dlist.print_reversed();
	dlist.delete_allnum(66);
	dlist.print();
	dlist.print_reversed();*/
	    cout << "-----------------------\n";
		LinkedList dlist1;
		//dlist1.insert_sorted(10);
		dlist1.insert_sorted(4);
		dlist1.insert_sorted(4);
		dlist1.insert_sorted(4);
		dlist1.print();
		dlist1.insert_sorted(12);
		dlist1.insert_sorted(3);
		dlist1.print();
		dlist1.print_reversed();
		dlist1.insert_sorted(1);
		dlist1.insert_sorted(-1);
		dlist1.print();
		dlist1.print_reversed();
	    dlist1.insert_sorted(2);
		dlist1.print();
		//dlist1.print_reversed();
		dlist1.delete_allnum(4);
		dlist1.print();
		
		//dlist1.delete_odd_indxs();
		dlist1.delete_even_indxs();
		dlist1.print();
		
		//dlist1.print_reversed();
		cout << "-----------------------\n";
		LinkedList dlist2;
		dlist2.is_palindrome();
		dlist2.insert_front(1);
		dlist2.insert_end(3);
		dlist2.insert_end(3);
		dlist2.insert_end(1);
		dlist2.print();
		dlist2.is_palindrome();
		dlist2.insert_end(1);
		dlist2.print();
		dlist2.is_palindrome();

}
