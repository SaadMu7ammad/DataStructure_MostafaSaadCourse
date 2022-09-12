#pragma once
struct StackElement {
	int n;
	int result{ -1 };	// if < 0, not answered
	StackElement(int n = 1, int result = -1) :
		n(n), result(result) {
	}
	bool is_computed() {
		return result >= 0;
	}
};
class stack3 {
private:
	int size{ };
	int top{ };
	StackElement* array{};
public:
	stack3(int size) :
		size(size), top(-1) {
		array = new StackElement[size]{ };
	}

	~stack3() {
		delete[] array;
	}

	void push(StackElement x) {
		if(!isFull());
		array[++top] = x;
	}

	StackElement pop() {
		if(!isEmpty());
		return array[top--];
	}

	StackElement peek() {
		if(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}
	int factorial_stack(int n) {
		if (n <= 1)
			return 1;
		//stack3 st(n);
		push(StackElement(n));
		StackElement cur(1);
		// Simulate recursion
		// Every stack call get into stack
		// Once reaches base, stop and go back with result
		while (!isEmpty()) {
			cur = peek();
			if (!cur.is_computed()) {	// more recursive calls!
				if (cur.n <= 1) {		// base case: finally stop
					cur.result = 1;
					pop();
					push(cur);
				}
				else
					push(StackElement(cur.n - 1));	// factorial(cur-1);
			}
			else {
				// The previous element called me?
				cur = pop();
				/*cout << "n = " << cur.n << "\n";
				cout << "result = " << cur.result << "\n";
				cout << "--\n";*/
				if (!isEmpty()) {	// someone called me
					StackElement parent =pop();
					/*cout << "n = " << parent.n << "\n";
					cout << "result = " << parent.result << "\n";
					cout << "--\n";*/
					parent.result = parent.n * cur.result;	// n * fact(n-1)
					push(parent);
				}
			}
		}
		return cur.result;
	}
};

