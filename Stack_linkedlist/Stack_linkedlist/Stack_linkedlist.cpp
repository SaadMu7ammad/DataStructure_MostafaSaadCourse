#include <iostream>
#include <Bits/stdc++.h>
using namespace std;
//typedef char type;
typedef int type;
class Stack {
private:
    struct Node {
        int data{};
        Node* next{};
        int length;
        Node(int data):data(data) {
        }
    };
    Node* head{};
public:
    void push(type num) {
        Node* node = new Node(num);
        node->next = head;
        head = node;
    }
    type pop() {
        assert(!isEmpty());
        Node* temp = head;
        head = head->next;
        return temp->data;
        delete temp;
    }
    type peek() {
        assert(!isEmpty()); 
        return head->data;
    }
    bool isEmpty() {
        return head == nullptr;
    }
    void print() {
        for (Node* i = head; i; i = i->next) {
            cout << i->data << " ";
        }
        cout << "\n";
    }
    ~Stack() {
        while (!isEmpty())
            pop();
    }
};
void convert_prefix_to_postfix(string operation) {
    operation += '-';//added instead of the last while in the func
    Stack st;//typedef char type;
    //Stack st(100);//without linkedlist
    string result = "";
    for (int i = 0; i < operation.length(); i++) {
        if (isdigit(operation[i])) {
            result += operation[i];
        }
        else {
            if (st.isEmpty()) {
                st.push(operation[i]);
            }
            else {
                if (operation[i] == '*' || operation[i] == '/') {
                    if (st.peek() != '*' && st.peek() != '/') {
                        st.push(operation[i]);
                    }
                    else {
                        while (!st.isEmpty() && (st.peek() == '+' || st.peek() == '-')) {
                            result += st.pop();
                        }
                        st.push(operation[i]);
                    }
                }
                else {
                    while (!st.isEmpty()) {
                        result += st.pop();
                    }
                    st.push(operation[i]);
                }
            }
        }
    }
    /*  while (!st.isEmpty()) {
          result += st.pop();
      }*/
    cout << result << "\n";
}
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    else if (op == '(')return 0; //low priority to not added it to the string
    return 2;	
}
void convert_prefix_to_postfix_shorterCode(string infix) {
    infix += '-';
   // Stack operators(100);
    Stack operators;
    string postfix;
    for (int i = 0; i < (int)infix.size(); ++i) {
        if (isdigit(infix[i]))
            postfix += infix[i];
        else {
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(infix[i]))
                postfix += operators.pop();
            operators.push(infix[i]);	// higher than any in stack
        }
    }
    //while (!operators.isEmpty())	// remaining
    //    postfix += operators.pop();
    //we could uncomment the while above and comment  the infix+='-' line 
    cout << postfix << endl;
}
void convert_prefix_to_postfix_withparentheses(string infix) {
    infix += '-';
    //Stack operators(100);
    Stack operators;
    string postfix;
    for (int i = 0; i < (int)infix.size(); ++i) {
        if (isdigit(infix[i]))postfix += infix[i];
        else if (infix[i] == '(') operators.push(infix[i]);
        else if (infix[i] == ')') {
            while (!operators.isEmpty() && operators.peek() != '(')	// remaining
                postfix += operators.pop();
            if (!operators.isEmpty())operators.pop();//remove the (
        }
        else {//the normal part that u founded it in the above functions
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(infix[i])) {
                postfix += operators.pop();
            }
            operators.push(infix[i]);
        }
    }
    cout << postfix << "\n";
}
int main()
{
    Stack st;
    st.push(5);
    st.push(8);
    st.push(3);
    st.print();
    cout<<st.peek()<<"\n";
    cout << st.pop() << "\n";
    st.print();
    cout << st.pop() << "\n";
    st.print();
    cout << "---------\n";
    convert_prefix_to_postfix("1+3*5-8/2");
    convert_prefix_to_postfix_shorterCode("1+3*5-8/2");
    convert_prefix_to_postfix("1-2+3");
    convert_prefix_to_postfix_shorterCode("1-2+3");
    convert_prefix_to_postfix("2*4-1-2+3*4+3-2/2+0*2");
    convert_prefix_to_postfix_shorterCode("2*4-1-2+3*4+3-2/2+0*2");
    convert_prefix_to_postfix_withparentheses("2+3-((5+2)*3)");
}