#include<bits/stdc++.h>
#include <iostream>
using namespace std;

class Queue {
private:
	
	struct Node {
		int data{};
		Node* next{};
		Node* node{};
		Node(int data) :data(data) {
			//node = new Node(data);
		};
		
	};
	Node* front;
	Node *rear;
	int length;//added elements
	
public:
	
	int isEmpty() {
		return front ==nullptr;
	}
	
	Node* prev() {
		for (Node* i = front; i; i = i->next) {
			if (i->next == rear) {
				Node* del = rear;
				delete del;
				rear = i;
				rear->next = nullptr;
				return rear;
			}
		}
	}
	void enqueue(int num) {
		Node* node = new Node(num);
		if (front == nullptr) {
			front = rear=node;
			rear->next = nullptr;
		}
		else {
			rear->next = node;
			rear = node;
			rear->next = nullptr;
		}
		length++;
	}
	int dequeue() {//remove from the front so the top shifted to the right (+1)
		assert(!isEmpty());
		int val = front->data;
		length--;
		Node *temp = front->next;
		delete front;
		front = temp;
		return val;
	}
	
	void print() {
		cout << "\nFront = " << front->data << "\n";
		if (length == 0) {
			cout << "Queue is Empty!\n";
			return;
		}
		
		for (Node* i = front; i; i = i->next) {
			cout << i->data << " ";
		}
		cout << "\n";
	}
	~Queue() {
		for (Node* i = front; i; ) {
			i = front->next;
			delete front;
			 front=i;
		}
	}
};
class LinkedList {
    struct Node {
        int data;
        Node* next = nullptr;
        Node* head = nullptr;
    public:
        Node(int data) :data(data) {}
        ~Node() {
            //  delete this;
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;
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
    //2 deletes prevent copy and assign to avoid this mistake
    LinkedList() {}
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
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

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
            assert(!tail->next);
        }
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);	// Consider infinite cycle?
        assert(length == len);
        assert(length == (int)debug_data.size());
    }
    ////////////////////////////////////////////////////////////

    void print_loop() {
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            cout << cur->data << " ";
        }
        cout << "\n";
    }
    int size() {
        return length;
    }
    void delete_node(Node* node) {
        debug_remove_node(node);
        --length;
        delete node;
    }
    void add_node(Node* node) {
        debug_add_node(node);
        ++length;
    }
    void insert_end(int num) {
        Node* item = new Node(num);//create the node
        debug_add_node(item);
        if (head == nullptr && tail == nullptr) {
            head = tail = item;
        }
        else {
            tail->next = item; //link the new node with the old one (tail)(PUT THE ADDRESS FIRST)
            tail = item;  //move the tail to the last (new) node
        }
        ++length;
        debug_verify_data_integrity();
    }
    void insert_front(int num) {// O(1) time - O(1) memory
        Node* node = new Node(num);//create a node
        debug_add_node(node);
        if (head == nullptr && tail == nullptr) {
            head = tail = node;
        }
        else {
            node->next = head;        //store the address of the head in the node to make it before it
            head = node;            //shift the head to the new node
        }
        ++length;
        debug_verify_data_integrity();
    }

    int delete_front() {
        // Node* node = head;
        if (head == nullptr) { //length==0
            cout << "size = 0\n";
            return INT_MIN;
        }
        Node* node2 = head->next;
        int returned = head->data;
        debug_remove_node(head);
        delete head;
        head = node2;
        --length;
        if (head == nullptr)tail = nullptr;
        debug_verify_data_integrity();
        return returned;
    }
    int delete_back() {
        // Node* node = head;
        if (head == nullptr || tail->next == nullptr) { //length==0
      //  if (length <= 1) {
          int del=  delete_front();
            return del;
        }
        Node* node = get_nth(length - 2);
        int returned = tail->data;
        debug_remove_node(tail);
        delete tail;
        tail = node;
        tail->next = nullptr;
        --length;
        debug_verify_data_integrity();
        return returned;
    }
    void delete_nth(int indx) {
        if (indx == 0) {
            delete_front();
            return;
        }
        else if (indx >= length) {
            cout << "Out Of Range\n";
            return;
        }
        //--indx;//get the prev element
        Node* prev = get_nth(indx - 1);
        Node* cur = prev->next;
        prev->next = cur->next;
        if (cur == tail)tail = prev;//IMPORTANT
        debug_remove_node(cur);
        delete cur;
        --length;

        debug_verify_data_integrity();
    }
    void delete_with_key(int num) {
        int c = 0;
        for (Node* cur = head; cur != nullptr; cur = cur->next, c++) {
            if (num == cur->data) {
                delete_nth(c);
                return;
            }
        }
    }
    void delete_node(Node* prev, Node* cur) {//Overloading
        prev->next = cur->next;
        debug_remove_node(cur);
        delete cur;
        --length;
    }

    int find(Node* head, int num) {
        while (head != nullptr) {
            if (head->data == num) {
                return head->data;
            }
            head = head->next;
        }
        return -1;
    }
    Node* get_nth(int indx) {
        int c = 0;
        for (Node* i = head; i != nullptr; i = i->next) {
            if (indx == c) {
                return i;
                //return i->data;
            }
            ++c;
        }
        return nullptr;
    }
    Node* get_nth_back(int indx) {
        int c = length - 1;
        for (Node* i = head; i != nullptr; i = i->next) {
            if (indx == c) {
                //  return i->data;
                return i;
            }
            --c;
        }
        return nullptr;
    }
    int search(int num) {
        int c = 0;
        for (Node* i = head; i != nullptr; i = i->next) {
            if (num == (i->data)) {
                return c;
            }
            ++c;
        }
        return -1;
    }

    void swap_each_pair() {
        for (Node* i = head; i != nullptr; i = i->next) {
            if (i->next != nullptr) {
                swap(i->data, i->next->data);

                i = i->next;
            }
        }
    }
    ~LinkedList() {
        while (head != nullptr) {
            Node* current = head->next;
            delete head;//delete the node it points to
                        //so why the reason of deleting the head 
                        // after store it in another point of its next node
                        // then shift the head to the next of it which is Current (ptr)
            head = current;
        }
    }
};

class Queue2 {
    LinkedList list;
public:

    int isEmpty() {
        return list.size() ==0;
    }

    
    void enqueue(int num) {
        list.insert_end(num);
    }
    void dequeue() {//remove from the front so the top shifted to the right (+1)
         cout<<list.delete_back()<<"\n";
    }

    void print() {
        list.print_loop();
    }
   
};
int main()
{
	Queue q;
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
    cout << "-------------\n\n";
    Queue2 q2;
    q2.enqueue(5);
    q2.enqueue(7);
    q2.enqueue(8);
    q2.enqueue(9);
    q2.dequeue();
    q2.print();
    q2.enqueue(4);
    q2.enqueue(3526);
    q2.print();
    q2.dequeue();
    q2.dequeue();
    q2.print();
    q2.enqueue(99);
    q2.print();
    q2.enqueue(55);
    q2.print();
	return 0;
}
