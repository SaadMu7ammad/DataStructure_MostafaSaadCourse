#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include <cassert>

using namespace std;
#define ll long long
#define loop(start, n) for (ll i = start; i < n; i++)
#define loop2(start, n) for (ll j = start; j < n; j++)
#define loop3(start, n) for (ll k = start; k < n; k++)
//#define endl "\n"
void sonic()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
}
long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}
long long lcm(long long a, long long b)
{
    return a / gcd(a, b) * b;
}
bool checkPrime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)return false;
    }
    return true;
}
bool sortbysec(pair< long long, long long> a, pair< long long, long long> b)
{
    if (a.second == b.second)
    {
        return (a.first > b.first);
    }
    return a.second > b.second;
}
class v {
private:
    int* arr;
    int s;
    int capacity=1;
public:
    v(int s):s(s) {
        if (s <= 0) {
            s = 1;
           
        }
        capacity= 2* s;
            arr = new int[capacity] {};

    }
    int get(int idx) {
        assert(idx >= 0 && idx < capacity);
        return arr[idx];
    }
    void set(int idx,int val) {
        assert(idx >= 0 && idx < capacity);
        arr[idx]=val;
    }
    void print() {
        for (int i = 0; i < s;i++)cout << arr[i] << " ";
        cout << "\n";
    }
    int find(int num) {
        for (int i = 0; i < s; i++) {

            if (num == arr[i]) {
               // cout << "Founded\n";
               // cout << "at index : " << i << endl;
                return i;
            }
        }
        return -1 ;// "Not Founded\n";
        
    }
    int front() {
        return arr[0];
    }
    int back() {
        return arr[s - 1];
    }
    /*void push_back(int num) {// So SLOW MANY STEPS WITHOUT USING CAPACITY 
        int *arr2=new int[2 * s];
        for (int i = 0; i < s; i++) {
            arr2[i] = arr[i];
        }
        arr2[s++] = num;
        swap(arr2, arr);
        delete[]arr2;
    }*/
    void expand_capacity() {

        capacity *= 2;
        cout << "expand capacity from " << s << " " << capacity << endl;
        int* arr2 = new int[capacity] {};

        for (int i = 0; i < s; i++) {
            arr2[i] = arr[i];
        }
        //  arr2[s++] = num;
        swap(arr, arr2);
        delete[]arr2;
    }
    void push_back(int num) {
        if (s == capacity) {
            expand_capacity();
        }
            arr[s++] = num;
    }
    void insert(int indx, int num) {
        if (s == capacity) {
            expand_capacity();
        }
        for (int i = s; i >indx; i--) {
            arr[i] = arr[i - 1];
        }
        arr[indx] = num;
        ++s;
    }
    void right_rotate() { //0 1 2 3 4 >> 4 0 1 2 3
        insert(0, arr[s - 1]);
        --s;
    }
    void left_rotate() { //0 1 2 3 4 >> 1 2 3 4 0
        int temp = arr[0];
        for (int i = 1; i < s; i++) {
            arr[i-1] = arr[i];
        }
       arr[s-1] = temp;
        //--s;

    }

    void right_rotate(int n) { //0 1 2 3 4 >> 4 0 1 2 3
        n %= s;
        while (n--) {
            insert(0, arr[s - 1]);
            --s;
        }
    }
    void left_rotate(int n) { //0 1 2 3 4 >> 1 2 3 4 0
        n %= s;
        while (n--) {
            insert(s, arr[0]);
            for (int i = 1; i < s; i++) {
                arr[i - 1] = arr[i];
            }
            --s;
        }

    }
    void right_rotate_byNum(int idx) { //0 1 2 3 4 >> 4 0 1 2 3
            insert(0, arr[idx]);
            pop(idx+1);
          /*  for (int i = idx; i < s-1; i++) {
                arr[i ] = arr[i+1];
            }
            
            --s;*/
    }
    void pop(int idx) {
        for (int i = idx; i < s-1; i++) {
            arr[i] = arr[i+1];
        }
        --s;
    }
    void find_transposition(int num) {
        int x = find(num);
        if (x != -1) {
            right_rotate_byNum(x);

        }
    }
    ~v() {
        delete[]arr;
        arr = nullptr;
    }


};
int main()
{
    v obj(3);
    obj.set(0,3);
    obj.set(1,5);
   obj.set(2,9);
    obj.push_back(3);
    obj.push_back(5);
    obj.push_back(9);

    obj.print();
    cout << obj.find(55) << endl;
    cout << obj.find(5) << endl;
    cout << obj.front() << endl;;
    cout<<obj.back() << endl;
    obj.push_back(97);
    obj.push_back(99);
    obj.push_back(100);
    obj.push_back(101);
    obj.set(5, 111);

  /*  for (int i = 0; i < 1000000; i++) {
        obj.push_back(i);
    }*/
    obj.print();
    obj.insert(4, 888);
    obj.insert(0, -2);
    obj.print();
    cout << "---\n";
    obj.right_rotate();
    obj.print();
    obj.right_rotate();
    obj.print();
    cout << "---\n";

    obj.left_rotate();
    obj.print();
    obj.left_rotate();
    obj.print();
    cout << "---\n";
    obj.left_rotate(2);
    obj.print();
    cout << "---\n";
    obj.right_rotate(2);
    obj.print();
    obj.pop(0);
    obj.print();
    obj.pop(1);
    obj.print();
    obj.pop(5);
    obj.print();

    cout << endl << endl;

    v obj1(3);
    obj1.push_back(5);
    obj1.push_back(6);
    obj1.push_back(7);
    obj1.push_back(8);
    obj1.print();
    cout << "--\n";
    //5 6 7 8
    //obj1.find_transposition(6);
    //obj1.print();
   // obj1.find_transposition(5);
    //obj1.print();
    //obj1.left_rotate();
    obj1.print();
    //obj1.left_rotate();
    obj1.print();
  //its size=7 
    obj1.right_rotate(8);
    obj1.print();
    cout << "---\n";
    obj1.left_rotate();
    obj1.print();
    obj1.left_rotate();
    obj1.print();
    obj1.left_rotate();
    obj1.print();
    return 0;
}