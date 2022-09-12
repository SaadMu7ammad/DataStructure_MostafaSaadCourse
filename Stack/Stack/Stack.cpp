#include<iostream>
#include<Bits/stdc++.h>
#include<algorithm>
#include"stack3.h"
using namespace std;
typedef char type;
//typedef int type;
class Stack {
private:
    int top{};
    int size{};
    type* arr{};
public:
    Stack(int size) :size(size),top(-1) {
        arr = new type[size];
    }
    bool isFull() {
        if (top + 1 == size) {
            return true;
        }
        return false;
    }
    bool isEmpty() {
        if (top ==-1) {
            return true;
        }
        return false;
    }
    void push(type num) {
        assert(isFull()!=1);
        arr[++top] = num;
    }
    type pop() {
        assert(isEmpty() != 1);
       return arr[top--];
    }
    type peek() {
        assert(isEmpty() != -1);
        return arr[top];
    }
    void print() {
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    void print_reversed() {
        for (int i = 0; i <=top; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    int length() {
        return top;
   }
    void push_back(int num) {//at the bottom
        if (isEmpty())push(num);// add the 10 when stack is empty then go the the stack (according to the recursion)
        else {
            //eg: 4 3 2 1 and want to add 10
            int temp = pop();
            push_back(num);//call (go up)
            push(temp);// 4 3 2 1 
        }
    }
    void reverse(int top) {//1 2 3 4
        if (isEmpty()) return;
        else {
            int temp = pop(); // 4
            reverse(temp); //3 2 1 //reverse the reamining array
            push_back(temp);//4 3 2 1//then add the element at the bottom
        }
    }
    void clear() {
        delete[] arr;
        top = -1;
        arr = new type[size];
    }
   
    ~Stack() {
        delete[] arr;
    }
};
class Stacks2 { //another implementation to deal with two stacks inside
private:
    int top1{};
    int top2{};
    int size{};
    int* arr{};
public:
    Stacks2(int size) :size(size), top1(-1),top2(size) {
        arr = new int[size];
    }
    int isFull() {
        return top1 + 1 == top2;
    }
    int isEmpty(int id) {
        if (id == 1)
            return top1 == -1;
        return top2 == size;
    }
    void push(int id,int num) {
        assert(!isFull());
        if(id==1)
        arr[++top1] = num;
        else
        arr[--top2] = num;
    }
    int pop(int id) {
        assert(!isEmpty(id));
        if (id == 1)
           return arr[top1--] ;
        else
            return arr[top2++] ;
    }
    int peek(int id) {
        assert(!isEmpty(id));
        if (id == 1)
            return arr[top1];
        else
            return arr[top2];
    }
    void print() {
        for (int i = top1; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << "\n";
        for (int i = top2; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    void clear() {
        delete[] arr;
        top1 = -1;
        top2 = size;
        arr = new int[size];
    }
    ~Stacks2() {
        delete[] arr;
    }
};
string reverse_string(string line) { // ABC when put into stack >> ( C >> TOP
                                       //                             B
                                       //                             A )
                                      // so print from the top to reverse it
    line += ' ';// simple trick. add dummy space to force last group to be formed
    string result = "";
    Stack st(line.length());
    for (int i = 0; i < line.length(); i++) {
        while (line[i] != ' ') {
            st.push(line[i]);
            ++i;

        }
        while (st.isEmpty() != 1) {
            result += st.pop();
        }
        result += ' ';
    }
    return result;
}
int reverse_num(int num) { 
    Stack st(30);
    if (num == 0)return 0;

    while (num) {
        st.push(num % 10);
        num /= 10;
   }
    int tens = 1;
    int newnum = 0;
    while (!st.isEmpty()) {
        newnum +=(st.pop()*tens);
       
        tens *= 10;
    }

    return newnum;
}
bool valid_parentheses(string x) { //uncomment the line 6 & comment 7
    Stack st(100);
    for (int i = 0; i < x.length(); i++) {
        if (x[i] == ')') {
            if (!st.isEmpty()&&st.peek() == '(') {
                st.pop();
            }
        }
        else  if (!st.isEmpty() && x[i] == '}') {
            if (st.peek() == '{') {
                st.pop();
            }
        }
        else  if (!st.isEmpty() && x[i] == ']') {
            if (st.peek() == '[') {
                st.pop();
            }
        }
        else {
            st.push(x[i]);
        }
    }
    if (st.isEmpty()) {
        cout << "Valid\n";
        return true;
    }
    else {
        cout << "Not Valid\n";
        return false;
    }
}
string Remove_all_adjacent(string x) {
    string result = "";
    Stack st(1000);
    for (int i = 0; i < x.length(); i++) {
        if (st.isEmpty() == 1) {
            st.push(x[i]);
        }
        else if (x[i] == st.peek()) {
            st.pop();
        }
        else {
            st.push(x[i]);
        }
    }
    while (!st.isEmpty()) {
        result +=st.pop();
    }
     reverse(result.begin(), result.end());
    return result;
}
void asteroid_collision(int arr[],int len) {
    Stack st(len);//typedef int type;
    for (int i = 0; i < len; i++) {
        int asteroid = arr[i];
        bool deletedastr = false;
        bool add = false;
            while (!st.isEmpty() && asteroid < 0 && st.peek() >= 0) {
                 if (st.peek()<-asteroid ) {
                    st.pop();
                    continue;
                }
              else if ( st.peek()==-asteroid ) {
                    st.pop();
                    deletedastr = true;//no push again coz the two deleted
                    break;
                }
              else {
                     deletedastr = true; //no push again coz the astroid is bigger so will not replaced
                     break;
                 }
            }
            if (deletedastr ==false ) {
                st.push(asteroid);
            }
    }
    st.print_reversed();
}
int factorial(int num) {

    if (num == 1)return 1;
    return num * factorial(num - 1);
}
void scoreOfParentheses(string str) {
    Stack st(str.length());
    st.push(0);//to make the stack never empty
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            st.push(0);
        }
        else {
            int last = st.pop();
            if (last == 0) {
                last = 1;// the prev is (
            }
            else {
                last *= 2; // the prev is )
            }
            int all = st.pop() + last;//update the val
            st.push(all);
        }
    }
    cout << st.peek()<<"\n";
}
void next_greater_num(int v[], int len) {
    Stack pos(len);//indexs
    //O(n) time! We iterate on numbers ~twice
    for (int i = 0; i < (int)len; ++i) {
        while (!pos.isEmpty() && v[i] > v[pos.peek()]) {
            int indx = pos.pop();
            v[indx] = v[i];
        }
        pos.push(i);
    }
    while (!pos.isEmpty()) {
        int indx = pos.pop();
        v[indx] = -1;
    }
    for (int i = 0; i < (int)len; ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}
void convert_prefix_to_postfix(string operation) {
    operation += '-';//added instead of the last while in the func
    Stack st(100);//typedef char type;
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
                        while (!st.isEmpty() &&( st.peek() == '+' || st.peek() == '-')) {
                            result += st.pop();
                        }
                        st.push(operation[i]);
                    }
                }
                else {
                        while (!st.isEmpty() ) {
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
    cout << result<<"\n";
}
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '(')return 0; //low priority to not added it to the string
    return 2;	// For * /
}
void convert_prefix_to_postfix_shorterCode(string infix) {
    infix += '-';
    Stack operators(100);
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
    cout<<postfix<<endl;
}
void convert_prefix_to_postfix_withparentheses(string infix) {
    infix += '-';
    Stack operators(100);
    string postfix;
    for (int i = 0; i < (int)infix.size(); ++i) {
        if (isdigit(infix[i]))postfix += infix[i];
        else if (infix[i] == '(') operators.push(infix[i]);
        else if (infix[i] == ')') {
            while (!operators.isEmpty() && operators.peek() != '(')	// remaining
                postfix += operators.pop();
           if(!operators.isEmpty())operators.pop();//remove the (
        }
        else {//the normal part that u founded it in the above functions
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(infix[i])) {
                postfix += operators.pop();
            }
            operators.push(infix[i]);	
        }
    }
    cout<<postfix << endl;
}
int main()
{
    //int stack 
    /*Stack st(5);
    cout << st.isEmpty() << "\n";;
    st.push(4);
    st.push(7);
    st.push(9);
    st.push(3);
    st.print();
    st.pop();
    st.print();
    st.push(55);
    st.push(8);
    st.print();
    cout << st.peek()<<"\n";
    while (!st.isEmpty()) {
        cout << st.peek() << " ";
        st.pop();
    }
    st.clear();
    st.print();
    cout << reverse_num(1234);*/
  //  cout << "--------------\n";
    //char stack 
    //UNCOMMENT THE LINE 6 >>TYPEDEF CHAR
    //string line;
    //getline(cin, line);
   // cout<<reverse_string(line);
   // cout << "\n--------------\n";
    //char stack 
    //string x = "()()()()";
    //cout << valid_parentheses(x)<<"\n";//valid
    // x= "(]()";
    //cout << valid_parentheses(x)<<"\n";//Not valid
    //x = "[]()";
    //cout << valid_parentheses(x)<<"\n";//valid
    //x = "[{()}]{}()";
    //cout << valid_parentheses(x) << "\n";//valid
    //cout << "\n--------------\n";
    ////char stack 
    //string word = "abbcxxayrroope";
    //cout << Remove_all_adjacent(word);

    //cout << "\n--------------\n";
    //new stack design that include two stacks
    //Stacks2 stnew(10);
    //stnew.push(2, 5);
    //stnew.push(2, 6);
    //stnew.pop(2);
    //stnew.push(2, 7);
    //stnew.push(2, 9);
    //stnew.push(1, 4);
    //cout << stnew.peek(1) << "\n";
    //cout << stnew.peek(2) << "\n";
    //stnew.push(1, 6);
    //stnew.push(1, 8);
    //stnew.push(2, 3);
    //stnew.push(2, 4);
    //stnew.push(2, 5);
    ////stnew.push(2, 6); //stack is Full
    //stnew.push(1,6);
    //stnew.print();
    //problem 1 (asteroid_collision) Med-Hard Problem
  /*  int arr1[4]{ 10,2,-5 };
    asteroid_collision(arr1, 3);
   int arr2[5]{ -2,-1,1,2 };
  asteroid_collision(arr2, 4);
   int arr3[3]{-8,8 };
   asteroid_collision(arr3, 2);
   int arr4[4]{5,10,-5};
   asteroid_collision(arr4, 3);
   int arr5[3]{ 8,-8 };
   asteroid_collision(arr5, 2);
    int arr6[4]{ 1, 0, -1, 1 };
    asteroid_collision(arr6, 2);*/
    //problem 2&3 (insert at the bottom & reverse) Med-Hard Problem
   /*Stack st(5);
    st.push(4);
    st.push(3);
    st.push(2);
    st.push(1);
    st.print();
    st.push_back(10);
    st.print();
    st.reverse(st.peek());
    st.print();*/
    //problem 5 (count the parentheses) Med-Hard Problem
    //scoreOfParentheses("(()(()))");//6
    //scoreOfParentheses("()");//1
    //scoreOfParentheses("((()))");// ( (1) * 2 ) * 2 = 4
    //problem 6 (Next Greater Element) Hard Problem
   /* const int LEN1 = 8;
    int v1[LEN1]{ 73, 74, 75, 71, 69, 72, 76, 73 };
    next_greater_num(v1, LEN1);*/
    //Last Problem Hard
    //many tests
    /*convert_prefix_to_postfix("1+3*5-8/2");
    convert_prefix_to_postfix_shorterCode("1+3*5-8/2");
    convert_prefix_to_postfix("1-2+3");
    convert_prefix_to_postfix_shorterCode("1-2+3");
    convert_prefix_to_postfix("2*4-1-2+3*4+3-2/2+0*2");
    convert_prefix_to_postfix_shorterCode("2*4-1-2+3*4+3-2/2+0*2");
    convert_prefix_to_postfix_withparentheses("2+3-((5+2)*3)");*/
        //problem4 Hard
       /* stack3 st(5);
    	cout << 5 << " " << st.factorial_stack(5) << "\n";*/

    return 0;
}
