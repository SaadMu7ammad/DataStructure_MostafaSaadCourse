#include<iostream>
#include <bits/stdc++.h>
using namespace std;
deque<int>preorder;
deque<int>inorder;
class BinaryTree {
private:
	int data{ };
	BinaryTree* left{ };
	BinaryTree* right{ };
	
public:
	
	BinaryTree(int data) :
		data(data) {
	}
	
	BinaryTree(deque<int>& preorder, deque<int>& inorder, int inorder_start = 0, int inorder_end = inorder.size() - 1) {
		// next preorder is the current root
		data = preorder.front();
		preorder.pop_front();
		// Find where is this root in the inorder current sequence
		for (int split = inorder_start; split <= inorder_end; ++split) {
			if (inorder[split] == data) {
				if (inorder_start < split)	// there is a left tree
					left = new BinaryTree(preorder, inorder, inorder_start, split - 1);
				if (split < inorder_end)
					right = new BinaryTree(preorder, inorder, split + 1, inorder_end);
				break;
			}
		}
	}
	BinaryTree(queue<pair<int,int>>&preorderq) {
		// next preorder is the current root
		pair<int, int>p = preorderq.front();
		preorderq.pop();
		data = p.first;
		if (p.second == 0) {//not a leaf
			left = new BinaryTree(preorderq);
			right = new BinaryTree(preorderq);
		}
		
	}
	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;
		// iterate on the path, create all necessary nodes
		for (int i = 0; i < (int)values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new BinaryTree(values[i]);
				else
					assert(current->left->data == values[i]);
				current = current->left;
			}
			else {
				if (!current->right)
					current->right = new BinaryTree(values[i]);
				else
					assert(current->right->data == values[i]);
				current = current->right;
			}
		}
	}
	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		inorder.push_back(data);
		if (right)
			right->print_inorder();
	}
	void print_preorder_complete() {
		cout << data << " ";
		preorder.push_back(data);
		if (left)
			left->print_preorder();
		else
			cout << -1;
		if (right)
			right->print_preorder();
		else
			cout << -1;// 2 null ptr indicating to that node is a leaf 
	}
	void print_preorder() {
		cout << data << " ";
		preorder.push_back(data);
		if (left)
			left->print_preorder();
		if (right)
			right->print_preorder();
	}
	////////////////////////////////////////////
	int tree_max() {
		int res = data;
		if (left)
			res = max(res, left->tree_max());
		if (right)
			res = max(res, right->tree_max());
		return res;
	}
	int tree_height() {
		int res = 0;
		if (left)
			res = 1 + left->tree_height();
		if (right)
			res = max(res, 1 + right->tree_height());
		return res;
	}
	int total_nodes() {
		int res = 1;
		if (left)
			res += left->total_nodes();
		if (right)
			res += right->total_nodes();
		return res;
	}
	int leafs_count() {
		int res = !left && !right;
		if (left)
			res += left->leafs_count();
		if (right)
			res += right->leafs_count();
		return res;
	}
	bool is_exists(int value) {
		bool res = value == data;
		if (!res && left)
			res = left->is_exists(value);
		if (!res && right)
			res = right->is_exists(value);
		return res;
	}
	bool is_perfect(int h = -1) {
		if (h == -1)	// first call
			h = tree_height();
		// All leaves must be on the same last level
		if (!left && !right)
			return h == 0;
		if (!left && right || left && !right)
			return false;	// one child!
		// perfect on level h is perfect on h-1 for children
		return left->is_perfect(h - 1) && right->is_perfect(h - 1);
	}
	bool is_perfect_fomula() {
		int h = tree_height();
		int n = total_nodes();
		return pow(2, h + 1) - 1 == n;
	}
	void level_order_traversal1() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		while (!nodes_queue.empty()) {
			BinaryTree* cur = nodes_queue.front();
			nodes_queue.pop();

			cout << cur->data << " ";
			if (cur->left)
				nodes_queue.push(cur->left);
			if (cur->right)
				nodes_queue.push(cur->right);
		}
		cout << "\n";
	}

	void level_order_traversal2() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();
			 
			cout << "Level " << level << ": ";
			while (sz--) {
				BinaryTree* cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}
	void build_preorder(queue<pair<int, int> >& preorder_queue) {
		preorder_queue.push(make_pair(data, !left && !right));

		if (left)
			left->build_preorder(preorder_queue);

		if (right)
			right->build_preorder(preorder_queue);
	}
	bool is_mirror(BinaryTree* first, BinaryTree* second) {	// O(n). Think like preorder traversal
		if (first==nullptr && second==nullptr)
			return true;

		if (first == nullptr && second!=nullptr || first != nullptr && second == nullptr || first->data != second->data)
			return false;	// one subtree only or different values

		return is_mirror(first->left, second->right) && is_mirror(first->right, second->left);
	}
	
};



int main() {
	BinaryTree tree4(1);
	tree4.add({ 2 ,4,5 }, { 'L','L','L' });
	tree4.add({ 2 ,4,5 }, { 'L','L','R'});
	tree4.add({ 2 ,5,5 }, { 'L','R','R' });
	tree4.add({ 2 ,5,5}, { 'L','R','L'});
	tree4.add({ 3 ,7 ,5 }, { 'R','R' ,'R' });
	tree4.add({ 3 ,7 ,5}, { 'R','R' ,'L'});
	tree4.add({ 3 ,4 ,5 }, { 'R','L','R' });
	tree4.add({ 3 ,4 ,5}, { 'R','L','L'});
	tree4.print_inorder();
	cout << "\n";
	cout << "---------------------------------------------------------------\n";
	tree4.print_preorder();
	cout << "\n";
	cout << "---------------------------------------------------------------\n";

	cout << tree4.tree_height() << '\n';
	cout << "\n";
	cout << tree4.total_nodes() << '\n';
	cout << "---------------------------------------------------------------\n";
	cout << tree4.leafs_count() << '\n';
	cout << "---------------------------------------------------------------\n";
	cout << tree4.is_perfect() << " " << tree4.is_perfect_fomula() << '\n';
	cout << "---------------------------------------------------------------\n";
	tree4.level_order_traversal1();
	tree4.level_order_traversal2();
	cout<< "---------------------------------------------------------------\n";
	//the preorder and inorder are global dequeus
	/*for (int i = 0; i < inorder.size(); i++)cout<< inorder[i] << " ";
	cout<<"\n";
	for (int i = 0; i <preorder.size(); i++) cout<< preorder[i] << " ";
	cout << "\n--------------------------------------------------------\n";*/
	BinaryTree bt(preorder, inorder);
	bt.level_order_traversal1();
	cout <<"\n--------------------------------------------------------\n"; 

	/*BinaryTree tree(1);

	tree.add({ 2, 4 }, { 'L', 'L' });
	tree.add({ 3 }, { 'R' });
	tree.add({ 2, 5, 6 }, { 'L', 'R', 'L' });
	tree.add({ 2, 5, 7, 8, 10 }, { 'L', 'R', 'R', 'L', 'L' });
	tree.add({ 2, 5, 7, 8, 11 }, { 'L', 'R', 'R', 'L', 'R' });
	tree.add({ 2, 5, 7, 9 }, { 'L', 'R', 'R', 'R' });

	queue<pair<int, int> > preorder_queue;
	tree.build_preorder(preorder_queue);
	tree.print_preorder();
	BinaryTree tree_created(preorder_queue);
	tree_created.print_preorder();
	cout << "\n";*/

	
	cout << "\n--------------------------------------------------------\n";

	BinaryTree tree(1);

	tree.add({ 2, 3,5 }, { 'L', 'L','L' });
	tree.add({ 2, 3,6}, { 'L', 'L','R'});
	tree.add({ 2, 4,7 }, { 'L', 'R','L' });
	tree.add({ 2, 4,8 }, { 'L', 'R','R' });

	tree.add({ 2, 3,5 }, { 'R', 'R','R' });
	tree.add({ 2, 3,6 }, { 'R', 'R','L' });
	tree.add({ 2, 4,7 }, { 'R', 'L','R' });
	tree.add({ 2, 4,8 }, { 'R', 'L','L' });
	cout<<tree.is_mirror(&tree, &tree)<<"\n";
	cout << "\n--------------------------------------------------------\n";

	

	return 0;
}

