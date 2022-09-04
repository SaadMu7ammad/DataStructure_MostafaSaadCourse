#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define ll long long
#define loop(start, n) for (ll i = start; i < n; i++)
#define loop2(start, n) for (ll j = start; j < n; j++)
#define loop3(start, n) for (ll k = start; k < n; k++)
//#define endl "\n"
void sonic()
{
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
struct Node {
    int data;
    Node* next = nullptr;
    Node* head=nullptr;
public:
    Node(int data) :data(data) {}
    ~Node() {
      //  delete this;
    }
};

class LinkedList{
    Node*head=nullptr;
    Node*tail = nullptr;
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
    LinkedList(){}
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
        void print() {
            Node* temphead = head;
            if (head == nullptr)cout << "list is empty";
            while (temphead != nullptr) {
                cout << temphead->data<<" ";
                temphead=temphead->next;
            }
            cout << "\n";
        }
        void print_loop() {
            for (Node*cur=head; cur != nullptr;cur=cur->next) {
                cout << cur->data << " ";
            }
            cout << "\n";
        }
        void print_recursion_reversed(Node*head) {
            if (head == nullptr) {
                cout << "\n";
                return;
            }
              print_recursion_reversed( head->next); 
              cout << head->data << " ";
        }
        void print_recursion(Node* head) {
            if (head == nullptr) {
                cout << "\n";
                return;
            }
            cout << head->data << " ";
            print_recursion(head->next);
        }
        void reverse() {
            if (length <= 1)
                return;
            tail = head;
            Node* prev = head;//prev stroring the head
            head = head->next;//shift the head one
            while (head != nullptr) {
                Node* next = head->next;//next storing the next after head
                head->next = prev;//then make the head point to the the previous head (that is the reverse)
               prev=head;//update the prev to make it step to right 
                head =next;//make head now step to the right by equal it to the next which is further steo to the right
                //summary prev and next just like 2pointers move simultanously with difference between 1 step only 
                // the prev is left and the next is the right  
                
                // prev   next
                //  ^      ^
            }
            head = prev;
            tail->next = nullptr;
            debug_verify_data_integrity();
        }
        ////////////////////////////////////////////////////////////
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
        void insert_sorted(int num) {// O(1) time - O(1) memory
        if (head == nullptr)insert_front(num);

        else if (head == tail) {
            if (head->data >= num) {
                insert_front(num);
            }
            else {
                insert_end(num);
            }

        }
        else {
            Node* node = new Node(num);//create a node
            Node* prev = head;//create a node
            for (Node* cur = head->next; cur != nullptr; cur = cur->next) {
                if (head->data >= num) {
                    insert_front(num);
                    return;
                }
                if (cur->data >= num) {
                        prev->next = node;
                        node->next = cur;
                        debug_add_node(node);
                        ++length;
                        return;
                }
               // if(prev->next!=nullptr)
                prev = prev->next; 
            }
            insert_end(num);
        }
        debug_verify_data_integrity();
        }
        void delete_front() {
           // Node* node = head;
            if (head== nullptr) { //length==0
                cout << "size = 0\n";
                return ;
            }
            Node* node2 = head->next;
            debug_remove_node(head);
            delete head;
            head = node2;
            --length;
            if (head==nullptr)tail = nullptr;
            debug_verify_data_integrity();

        }
        void delete_back() {
            // Node* node = head;
            if (head == nullptr||tail->next==nullptr) { //length==0
          //  if (length <= 1) {
                delete_front();
                return;
            }
            Node* node= get_nth(length-2);
            debug_remove_node(tail);
            delete tail;
            tail = node;
            tail->next = nullptr;
            --length;
            debug_verify_data_integrity();
        }
        void delete_nth(int indx) {
            if (indx == 0) {
                delete_front();
                return;
            }
            else if (indx >=length) {
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
            for (Node* cur = head; cur != nullptr; cur = cur->next,c++) {
                if (num == cur->data) {
                    delete_nth(c);
                    return;
                }
            }
        }
        void delete_node(Node* prev,Node *cur) {//Overloading
            prev->next = cur->next;
           debug_remove_node(cur);
            delete cur;
            --length;
        }
        void delete_even_pos() { // O(n) time - O(1) memory
            if (length <= 1)
                return;
            Node* prev=head;
            for (Node* cur = head->next; cur != nullptr; ) {
            //  cur = cur->next
                    delete_node(prev,cur);
                    if (!prev->next)	// tail
                        break;
                  // prev = prev->next;
                   // cur = cur->next;
                    cur = prev->next->next;
                    prev = prev->next;
            }
            debug_verify_data_integrity();
        }
        int find(Node* head,int num) {
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
            int c = length-1;
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
        int improved_search(int num) { //shift the element u search for one to the left
            int c = 0;
            Node* prev = nullptr;
            for (Node* i = head; i != nullptr; i = i->next,c++) {
                if (num == (i->data)) {
                    if (c != 0)swap(i->data, prev->data);
                    else return c;//prev = i; 
                    return c-1;
                }
                prev = i;
                //++c;
            }
            return -1;
        }
        void checker() {//data integrity of the linked list
            
            if (length == 0 && head == nullptr && tail == nullptr) {
                cout << "Empty\n";
            }
            else {
                cout << "its size= " << length << "\n";
            }
        }
        bool is_same_length(const LinkedList &list) {
            if (list.length == length) {
                cout << "Same Length ";
                return true;
           }
            cout << "Not Same Length ";

            return false;
        }
        bool is_same_list(const LinkedList& list) {
            if (is_same_length(list)) {
                Node* l1 = head;
                Node* l2 = list.head;
               
                while (l1!=nullptr) {
                    if (l1->data == l2->data) {
                       l1= l1->next;
                       l2= l2->next;
                    }
                    else {
                        cout << " But NOT the Same List: ";
                        return false;
                    }
               }
                cout << " and the Same List: ";
                return true;
           }
            else {
                cout << "So NOT the Same List: ";
                    return false;
            }
        }
        bool is_same_list_2(const LinkedList& list) {
                Node* l1 = head;
                Node* l2 = list.head;
                while (l1 != nullptr&&l2!=nullptr) {
                    if (l1->data == l2->data) {
                        l1 = l1->next;
                        l2 = l2->next;
                    }
                    else {
                        cout << " NOT the Same List: ";
                        return false;
                    }
                }
                if (l1 != nullptr && l2 == nullptr || l1 == nullptr && l2 != nullptr) {
                    cout << " NOT the Same List: ";
                    return false;
                }
                else {
                    cout << " Same List: ";
                    return true;
                }
        }

        void swap_each_pair() {
            for (Node* i = head; i != nullptr; i = i->next) {
                if (i->next!=nullptr) {
                    swap(i->data, i->next->data);
                   
                    i = i->next;
                }
            }
        } 
        void swap_headWithTail() {
            if (length <= 1)
                return;
            Node* prevtail = get_nth(length - 2); 
            Node* afterhead = head->next;
            tail->next = afterhead; //link tail to the 2nd node
            prevtail->next = head;
            head->next = nullptr;
            swap(tail,head);// ???
            debug_verify_data_integrity();
        }
        void left_rotate(int n ) {
           --n;
            if (length <= 1 || n % length == 0)
                return;

            n %= length;//remove useless cycles
            Node* node = get_nth(n );
            tail->next = head;//we must link them coz the head will be after the node then the array will be shifted 
            tail=node;
            head = node->next;
            tail->next = nullptr;
            debug_verify_data_integrity();
        }
        void remove_duplicates() {
            map<int, int>freq;
           
            for (Node* i = head; i != nullptr; i = i->next) {
                freq[i->data]++;
            } 
            int c = 0;
            for (Node* i = head; i != nullptr; i = i->next, c++) {
                if (freq.count(i->data) && freq[i->data]>1) {
                     freq[i->data]--; 
                     delete_nth(c); 
                  
                    if (i->next != nullptr) {
                        i = head;
                        c = 0;
                        continue;
                   }
                    else {
                        break;
                    }
                }
            }
        }
        void remove_last_occurence(int num) {
            map<int, int>freq;

            for (Node* i = head; i != nullptr; i = i->next) {
                if(i->data==num)
                freq[num]++;
            }
            if (freq[num] <1)return;
            int c = 0;
            for (Node* i = head; i != nullptr; i = i->next, c++) {
                if (num == i->data && freq[i->data] > 1) {
                    freq[i->data]--;
                }
                else if (num == i->data && freq[i->data] == 1) {
                    delete_nth(c);
                    freq[i->data]--;
                    return;
                }
                    
                
            }
        }
        void move_to_back(int num) {
            if (length <= 1 )
                return;
            int len = length;
            for (Node* i = head,*prev=nullptr;len--;) {// i = i->next
                if (i->data == num) {
                    Node* next = i->next;
                    tail->next = i;
                    tail = i;
                    if (prev != nullptr)
                        prev->next = next;
                    else
                        head = next;
                    tail->next = nullptr;
                    i =next;
                }
                else {
                    prev = i;
                    i = i->next;
                }
            }
            debug_verify_data_integrity();
        }
        int max(Node* node = nullptr, bool firstcall = true) {
           // Node* node = head; //redefintion  CompileErr  <>  XX
            if (firstcall) {
                return this->max(head,false);
            }
           if (node == nullptr)return INT_MIN;//to stop coz the int min not affect on the max element

            return std::max(node->data, this->max(node->next,false));

          
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
    class LinkedList_head {
        Node* head{};

        
    public:
        void add_element(int num) {
            Node* node = new Node(num);
            node->next = head;
            head = node;
        }
        void print() {//reversed
            for(Node*cur=head;cur;cur=cur->next)
                cout << cur->data<<" " ;
            cout << endl;
        }
        void print2() {//reversed
            Node* temphead = head;
            while (temphead != nullptr) {
                cout << temphead->data << " ";
                temphead = temphead->next;
            }
            cout << "\n";
        }
       
        Node* get_tail() {// O(n) time - O(1) memory
            Node* temphead = head;
            while (temphead->next != nullptr) {
                
                temphead = temphead->next;
            }
            return temphead;
        }
       
        ~LinkedList_head() {
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
int main()
{   
   
   /* Node* newnode1=new Node(66);
    newnode1->next = nullptr;
    Node* head = newnode1;
   
    Node* newnode2 = new Node(77);
    newnode2->next = nullptr;
    newnode1->next = newnode2;

    Node* newnode0 = new Node(44);
    newnode0->next = newnode1;
    head = newnode0;

    cout << head->data << endl;
    cout << head->next->data << endl;
    cout << head->next->next->data << endl;
    cout << "\n-----\n\n";*/

  
    //Node* Node1 = new Node(3); // node* Node1(3); //Compile Error
    //Node* Node2 = new Node(5);
    //Node* Node3 = new Node(7);
    //Node1->next = Node2;
    //Node2->next = Node3;
    //Node3->next = nullptr;
    //cout << Node1->next << " " << Node1->data << endl;
    //cout << Node1->next->next->next << " " << endl;
    //cout<<Node1->next->next->data << endl;
    //cout << "\n------------\n";
    LinkedList list;
    list.insert_end(6);
    list.insert_end(9);
    list.insert_end(14);
    list.insert_end(3);
    list.print_loop();
   
    cout << list.search(2) << "\n"; //-1
    cout << list.search(14) << "\n"; //2
    cout << list.improved_search(14) << "\n"; //2
    list.print_loop(); 
    list.insert_front(99);
    list.print_loop();
    list.debug_print_list();
    list.delete_front();
    list.insert_end(7);
    list.print_loop();//6 14 9 3 7 
    cout << list.get_nth(2) << "\n"; //9
    cout << list.get_nth_back(0) << "\n";//7
    cout << list.get_nth_back(3) << "\n";//14
    LinkedList list2;
    list2.insert_end(14);
    list2.insert_end(9);
    list2.insert_end(3);
    list2.insert_end(5);
    list2.insert_end(6);
    list2.insert_end(99);
    list2.insert_end(10);
   // list2.insert_end(77);
    list2.print();
    list.print();
    cout<<list.is_same_length(list2)<<endl;
    list.delete_front();
    list2.print();
    list.print();
    cout << list.is_same_length(list2) << endl;
    cout << list.is_same_list(list2) << endl;
    cout << list.is_same_list_2(list2)<<endl;
   list.delete_front();
    list.print();
    cout << list.get_nth_back(0)->data << "\n";//7
    list.delete_back();
    list.print();
    list.delete_back();
   // list.delete_back();
    list.print();
    list2.print();
    list2.delete_nth(2);
    list2.print();
    list2.delete_nth(5);
    list2.delete_nth(6);//out range
    cout << "\n";
    list2.delete_nth(4);
    list2.insert_front(99);
   // list2.delete_nth(3);
    //list2.delete_nth(2);
    //list2.delete_nth(1);
    //list2.delete_nth(0);
    list2.print();
   // list2.delete_with_key(14);
    list2.print();
    list2.swap_each_pair();
    list2.print();
   /* cout << list2.get_nth(0)<<" ";
    cout << list2.get_nth(0)->next<<" ";
    cout << list2.get_nth(1);*/
    list2.reverse();
    list2.print();
  //  list2.delete_even_pos();
    list2.print();
    list2.swap_headWithTail();
    list2.print();
    list2.left_rotate(3);
    list2.print();
    list2.insert_end(5);
    list2.insert_end(16);
    list2.insert_end(9);
    list2.insert_end(4);
    list2.print();

    list2.left_rotate(2);
    list2.print();
    list2.insert_end(16);
    list2.insert_end(9);
    list2.insert_end(4);
    list2.insert_end(1);
    list2.insert_end(1);
    list2.insert_end(42);
    list2.insert_end(1);

    list2.print();

    list2.remove_duplicates();
   list2.print();
   list2.insert_end(666);
   list2.insert_front(4);
   list2.insert_front(4);
   list2.insert_end(4);
   
   list2.print();
   list2.remove_last_occurence(666);
   list2.print();
   list2.remove_last_occurence(4);
   list2.print();
   list2.remove_last_occurence(9869);
   list2.print();
   list2.move_to_back(4);
   list2.print();
   list2.move_to_back(16);
   list2.print();
   list2.move_to_back(63263);
   list2.print();
   cout<<list2.max();
    cout << "******************************************\n";
    LinkedList list3;
    list3.insert_sorted(10);
    list3.print();
    list3.insert_sorted(1);
    list3.print();
    list3.insert_sorted(2);
    list3.print();
    list3.insert_sorted(4);
    list3.print();
    list3.insert_sorted(11);
    list3.print();
    list3.insert_sorted(0);
    list3.print();
    list3.insert_sorted(3);
    list3.print();
    list3.insert_sorted(5);
    list3.print();
    list3.insert_sorted(100);
    list3.print();
    list3.insert_sorted(-3);
    list3.print();
    list3.insert_sorted(-1);
    list3.print();

    cout << "******************************************\n";

    LinkedList_head l;//with head only No tail
    l.add_element(9986);
    l.add_element(6);
    l.add_element(8);
    l.add_element(4);
    l.print(); 
    l.print2();
    cout << l.get_tail()->data;
    
    return 0;
}