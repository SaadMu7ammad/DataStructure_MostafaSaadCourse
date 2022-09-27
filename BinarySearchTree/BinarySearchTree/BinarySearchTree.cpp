#include <iostream>
#include <Bits/stdc++.h>
using namespace std;

class BinarySearchTree {
	int data{};
	BinarySearchTree* left{};
	BinarySearchTree* right{};
public:
	BinarySearchTree(int data, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr) :
		data(data), left(left), right(right) {
	}
	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
	void print_preorder() {
		cout << data << " ";
		if (left)
			left->print_preorder();
		if (right)
			right->print_preorder();
	}
	void fillinorder(vector<int>&arr) {
		if (left)
			left->fillinorder(arr);
		arr.push_back(data);
		if (right)
			right->fillinorder(arr);
	}
	void insert(int num) {
		if (num > data && right == nullptr) {
			right = new BinarySearchTree(num);
		}
		if (num < data && left == nullptr) {
			left = new BinarySearchTree(num);
		}
		if (num > data && right != nullptr) {
			right->insert(num);
		}
		if (num < data && left != nullptr) {
			left->insert(num);
		}
	}
	int minimum() {
		if (left != nullptr) {
			return left->minimum();
		}

		return data;
	}
	BinarySearchTree* minimum_node() {
		if (left != nullptr) {
			return left->minimum_node();
		}

		return this;
	}
	BinarySearchTree* maximum_node() {
		if (right != nullptr) {
			return right->maximum_node();
		}
		return this;
	}
	int maximum() {
		if (right != nullptr) {
			return right->maximum();
		}

		return data;
	}
	bool search(int data) {
		if (this->data == data) {
			return true;
		}
		if (this->data > data) {
			return left!=nullptr &&left->search(data);//verify first if there is no left
		}
		else {
			return right != nullptr && right->search(data);
		}
	}
	bool iterative_search(int target) {
		BinarySearchTree* node = this;
		while (node) {
			if (node->data == target)return true;
			if (target > node->data) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		return false;
	}
	 /*          5
	 *    4              6
	 *               3        7
	 *
	 *   Although 6 is a valid BST, 5 > 3, which is wrong
	 *   Idea: we need to make sure this value is proper with the parents too not just the child?
	 *   We can maintain the current [mn, mx] valid range per node during recursion*/
	 
	bool is_bst0(int mini=INT_MIN,int maxi=INT_MAX) {
		bool status = mini < data && data < maxi;

		if (status == 0)return false;

		bool left_bst = left == nullptr || left->is_bst0(mini,data);
		if (left_bst == false)return false;

		bool right_bst = right == nullptr || right->is_bst0(data ,maxi);
		//if (right_bst == false)return false;
		return right_bst;

	}
	bool is_bst1() {//check the inorder traversal is sorted 
		vector<int>inorder;
		fillinorder(inorder);
		for (int i = 1; i < inorder.size(); i++) {
			if (inorder[i] <inorder[i - 1]) {
				return false;
			}
		}
		return true;
	}
	//bool is_bst2() {
	//	if (left==nullptr && right==nullptr)return true;

	//	if (left != nullptr && right != nullptr&&data > left->data && data < right->data) {
	//		if (left != nullptr && right != nullptr)return left->is_bst2() && right->is_bst2();;

	//	}
	////	return false;
	//}
	//bool is_bst3() {
	//	if (left == nullptr && right == nullptr)return true;

	//	if (left != nullptr && right != nullptr ) {
	//		if(data>left->maximum()&& data < right->minimum())
	//		return left->is_bst3() && right->is_bst3();

	//	}
	//	//	return false;
	//}
	
	//int kth_smallest_number(int k,int c = 1) {
	//	if (k == 0)
	//		return -1234;
	//	if (left) {
	//		int res= left->kth_smallest_number(k,c);
	//		//++c;
	//		if (k == c)
	//			return res;
	//	}
	//	++c;
	//	if (k == c)
	//		return data;
	//		
	//	if (right) 
	//		return right->kth_smallest_number(k,c);
	//			
	//	
	//	return-1234;
	//}
	int kth_smallest(int& k) {
		if (k == 0)
			return -1234;

		if (left) {
			int res = left->kth_smallest(k);
			if (k == 0)
				return res;
		}

		--k;	// for current node
		if (k == 0)
			return data;

		if (right)
			return right->kth_smallest(k);

		return -1234;
	}
	int lca(int a, int b) {

		if (a > data && b > data) {
			return right->lca(a, b);
		}

		if (a < data && b < data) {
			return left->lca(a, b);
		}
		return data;
	}
	bool find_chain(vector<BinarySearchTree*>& ancestor, int target) {
		ancestor.push_back(this);

		if (target == data) {
			return true;
		}
		if (target < data) {
			return left&&left->find_chain(ancestor, target);
		}
		return right && right->find_chain(ancestor, target);
	}
	BinarySearchTree* get_next_chain(vector<BinarySearchTree*>& ancestor) {
		if (ancestor.size() == 0)
			return nullptr;

		BinarySearchTree* temp = ancestor.back();
		ancestor.pop_back();
		return temp;

	}
	int successor(int num, vector<BinarySearchTree*>& ancestor,int prev=0) {
		find_chain(ancestor, num);

		if (num > data&&right!=nullptr) {
			prev = data;
			return right->successor(num,ancestor,prev);
		}
		 if (num < data&&left!=nullptr) {
			prev = data;
			return left->successor(num,ancestor,prev);
		}
		 if (num == data ) {
			if (right == nullptr) {
				//return prev;
				if (prev > data) {
					return prev;
				}
				else {
					while (true) {
						BinarySearchTree* neww = nullptr;
						neww=get_next_chain(ancestor);
						if( neww!=nullptr&&neww->data > num) {
							return neww->data;
							break;
						}
						else if (neww == nullptr ) {
							return maximum();
							break;
						}
					}
				}
			}
			else if (right != nullptr) {
				return right->minimum();
			}
		}
		
	}
	pair<bool, int> successor2(int target) {
		vector<BinarySearchTree*> ancestors;
		//find chain to detect the ancestors of the target
		if (!find_chain(ancestors, target))	// not exist
			return make_pair(false, -1);

		BinarySearchTree* child = get_next_chain(ancestors);

		if (child->right)	// must have be in min of right
			return make_pair(true, child->right->minimum());

		BinarySearchTree* parent = get_next_chain(ancestors);

		// Cancel chain of ancestors I am BIGGER than them
		while (parent && parent->right == child)//go up in the chain untill we found a number that is is right is not the
												// child of that number
			child = parent, parent = get_next_chain(ancestors);

		if (parent)	//
			return make_pair(true, parent->data);
		return make_pair(false, -1);
	}
	pair<bool, int> predecessor2(int target) {
		vector<BinarySearchTree*> ancestors;
		//find chain to detect the ancestors of the target
		if (!find_chain(ancestors, target))	// not exist
			return make_pair(false, -1);

		BinarySearchTree* child = get_next_chain(ancestors);

		if (child->left)	// must have be in min of right
			return make_pair(true, child->left->maximum());

		BinarySearchTree* parent = get_next_chain(ancestors);
		if (parent->data < child->data)
			return make_pair(true, parent->data);


		while (parent && parent->left == child)//go up in the chain untill we found a number that is is right is not the
												// child of that number
			child = parent, parent = get_next_chain(ancestors);

		if (parent)	//
			return make_pair(true, parent->data);
		return make_pair(false, -1);
	}
	int predecessor(int num, vector<BinarySearchTree*>& ancestor2, int prev = 0) {
		find_chain(ancestor2, num);

		if (num > data && right != nullptr) {
			prev = data;
			return right->predecessor(num, ancestor2, prev);
		}
		if (num < data && left != nullptr) {
			prev = data;
			return left->predecessor(num, ancestor2, prev);
		}
		if (num == data) {
			if (left == nullptr) {
				//return prev;
				if (prev < data) {
					return prev;
				}
				else {
					while (true) {
						BinarySearchTree* neww = nullptr;
						neww = get_next_chain(ancestor2);
						if (neww != nullptr && neww->data < num) {
							return neww->data;
							break;
						}
						else if (neww == nullptr) {
							return maximum();
							break;
						}
					}
				}
			}
			else if (left != nullptr) {
				return left->maximum();
			}
		}

	}
	void special_delete(BinarySearchTree* child) {
		// Instead of deleting node and return its child
		// copy child data and remove him
		// why? as sometimes node is actually the original this
		// Deleting it is RTE
		// This is another complication we pay for our coding style
		// to use only a single class instead of class + struct like linkedlist
		data = child->data;
		left = child->left;
		right = child->right;
		delete child;
	}
	//Use successor
	BinarySearchTree* delete_node(int target, BinarySearchTree* node) {//the comment code is updated coz its buggy
		if (node == nullptr) {
			return nullptr;
		}
		if (target > data) {
			node->right = delete_node(target, node->right);
		}
		if (target < data) {
			node->left = delete_node(target, node->left);

		}
		else {
		//	BinarySearchTree* temp = node;
			if (node->right == nullptr&& node->left == nullptr) {// no child
				delete node;
				node = nullptr;
			}
			else if (node->right == nullptr) {//no right
				//node = node->left;
				node->special_delete(node->left);		// connect with child

			}
			else if (node->left == nullptr) {//no left
				//node = node->right;
				node->special_delete(node->right);		// connect with child

			}
			else {
				BinarySearchTree* min = node->right->minimum_node();
				node->data = min->data;
				node->right = delete_node(min->data, node->right);
				//temp = nullptr;
			}
			/*if (temp != nullptr)
				delete temp;*/
		}
		return node;//the next upon deleted

	}
	//Use predecessor
	BinarySearchTree* delete_node2(int target, BinarySearchTree* node) {
		if (node == nullptr) {
			return nullptr;
		}
		if (target > data) {
			node->right = delete_node(target, node->right);
		}
		if (target < data) {
			node->left = delete_node(target, node->left);

		}
		else {
			//	BinarySearchTree* temp = node;
			if (node->right == nullptr && node->left == nullptr) {// no child
				delete node;
				node = nullptr;
			}
			else if (node->right == nullptr) {//no right
				//node = node->left;
				node->special_delete(node->left);		// connect with child

			}
			else if (node->left == nullptr) {//no left
				//node = node->right;
				node->special_delete(node->right);		// connect with child

			}
			else {	// 2 children: Use predecessor
				BinarySearchTree* mx = node->left->maximum_node();
				node->data = mx->data;
				node->left = delete_node2(node->data, node->left);
				//temp = nullptr;
			}
			/*if (temp != nullptr)
				delete temp;*/
		}
		return node;//the next upon deleted

	}
	void delete_value(int val) {
		if (val == data && left == nullptr && right == nullptr) {
			return; //cant delete the root in this case
		}
		delete_node(val, this);
	}
	void delete_value2(int val) {
		if (val == data && left == nullptr && right == nullptr) {
			return; //cant delete the root in this case
		}
		delete_node2(val, this);
	}
};
class BinarySearchTree2 {
	int data{};
	BinarySearchTree2* left{};
	BinarySearchTree2* right{};
	BinarySearchTree2* parent{};
public:
	BinarySearchTree2(int data, BinarySearchTree2* parent = nullptr) :
		data(data), parent(parent) {
	}
	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
	int minimum() {
		if (left != nullptr) {
			return left->minimum();
		}

		return data;
	}
	
	void insert(int num) {
		if (num > data && right == nullptr) {
			right = new BinarySearchTree2(num, this);
		}
		if (num < data && left == nullptr) {
			left = new BinarySearchTree2(num, this);
		}
		if (num > data && right != nullptr) {
			right->insert(num);
		}
		if (num < data && left != nullptr) {
			left->insert(num);
		}
	}
	BinarySearchTree2* search(int target) {
		if (data == target) {
			return this;
		}
		if (data > target) {
			if (left == nullptr)return nullptr;
			return left->search(target);
		}
		else {
			if (right == nullptr)return nullptr;

			return right->search(target);
		}
	}
	pair<bool, int>successor(int target) {
		BinarySearchTree2* child = search(target);
		if (child == nullptr)return make_pair(false, -1);
		if (child->right) {
			return make_pair(true, child->right->minimum());
		}
		BinarySearchTree2* parent = child->parent;
		while (parent && parent->right == child)
			child = parent, parent = child->parent;

		if (parent)
			return make_pair(true, parent->data);
		return make_pair(false, -1);

	}
	
};
BinarySearchTree* build_balanced_bst_tree(const vector<int>& values, int l = 0, int r = -10) {
	if (r == -10)
		r = (int)values.size() - 1;

	if (l > r)
		return nullptr;

	// The best root for N sorted numbers is their middle number
	// as N/2 numbers before and after. Keep applying recursively
	int mid = (l + r) / 2;
	BinarySearchTree* left = build_balanced_bst_tree(values, l, mid - 1);
	BinarySearchTree* right = build_balanced_bst_tree(values, mid + 1, r);
	BinarySearchTree* root = new BinarySearchTree(values[mid], left, right);

	return root;
}
bool is_degenerate(vector<int>& preorder) {
	if (preorder.size() <= 2)return true;
	int mini = 0;
	int maxi = 1000;

	for (int i = 1; i < preorder.size(); i++) {
		if (preorder[i] < mini || preorder[i] > maxi)
			return false;

		if (preorder[i] > preorder[i - 1]) {
			mini = preorder[i - 1] + 1;
		}
		else {
			maxi = preorder[i - 1] - 1;//400 300 200 
											//300
										//200
											//250
												//275
			//so when arr[i-1]300 and arr[i]=200
			//so the maxi of node 200 is till 299
			// by Eq arr[i-1]-1=300-1=299
		}
	}
	return true;
}
int main()
 {
	BinarySearchTree bst(50);
	bst.insert(20);
	bst.insert(60);
	bst.insert(15);
	bst.insert(45);
	bst.insert(35);
	bst.insert(70);
	bst.insert(73);

	bst.print_inorder();
	cout << '\n';
	cout << bst.minimum();
	cout << '\n';
	cout << "--------------------------------\n";

	int i = 3;
	cout << bst.kth_smallest(i);
	cout << '\n';
	//cout << bst.kth_smallest_number(2);
	cout << "\n--------------------------------\n";
	cout << bst.search(20) << "\n";
	cout << bst.search(60) << "\n";
	cout << bst.search(99) << "\n";
	cout << bst.search(231)<<"\n";
	cout << endl;
	cout << endl;
	cout << bst.iterative_search(20) << "\n";
	cout << bst.iterative_search(60) << "\n";
	cout << bst.iterative_search(99) << "\n";
	cout << bst.iterative_search(231) << "\n";
	cout << "----------------\n";
	cout << bst.is_bst0() << "\n";
	cout << bst.is_bst1() << "\n";
	//cout << bst.is_bst2() << "\n";
	//cout << bst.is_bst3()<<"\n";
	
	cout << "--------------------------------\n";
	vector<int>arr;
	BinarySearchTree *bst3 = build_balanced_bst_tree({ 0,1,2,3,4,5,6,7,8,9 });
	bst3->fillinorder(arr);
	for (int i = 0; i < 10; i++)cout << arr[i] << " ";
	cout << "\n--------------------------------\n";
	cout << bst.lca(35, 45)<<"\n";
	cout << bst.lca(15, 45) << "\n";
	cout << bst.lca(70, 45) << "\n";
	cout << "\n--------------------------------\n";
	vector<int> a;
	a = { 25, 8, 11, 13, 12 };
	cout<<is_degenerate(a)<<"\n";
	a = { 100, 70, 60, 75 };
	cout <<is_degenerate(a)<<"\n";
	a = { 500,400,300,200,250,275,260 };
	cout << is_degenerate(a) << "\n";
	cout << "\n--------------------------------\n";
	vector<BinarySearchTree*>ancestor{};
	cout << bst.successor(70, ancestor) << "\n";
	cout << bst.successor(20, ancestor) << "\n";
	cout << bst.successor(45, ancestor) << "\n";
	cout << bst.successor(35, ancestor) << "\n";
	cout << bst.successor(60, ancestor) << "\n";
	cout << bst.successor(73, ancestor) << "\n";//if no successor print the same val
	cout << bst.successor(50, ancestor) << "\n";
	cout << bst.successor(15, ancestor) << "\n";
	cout << "\n--------------------------------\n";
	cout << bst.successor2(70).second << "\n";
	cout << bst.successor2(20).second << "\n";
	cout << bst.successor2(45).second << "\n";
	cout << bst.successor2(35).second << "\n";
	cout << bst.successor2(60).second << "\n";
	cout << bst.successor2(73).second << "\n";//if no successor print -1
	cout << bst.successor2(50).second << "\n";
	cout << bst.successor2(15).second << "\n";
	cout << "\n--------------------------------\n";
	cout << "\n--------------------------------\n";
	vector<BinarySearchTree*>ancestor2{};
	cout << bst.predecessor(70, ancestor2) << "\n";
	cout << bst.predecessor(20, ancestor2) << "\n";
	cout << bst.predecessor(45, ancestor2) << "\n";
	cout << bst.predecessor(35, ancestor2) << "\n";
	cout << bst.predecessor(60, ancestor2) << "\n";
	cout << bst.predecessor(73, ancestor2) << "\n";
	cout << bst.predecessor(50, ancestor2) << "\n";
	cout << bst.predecessor(15, ancestor2) << "\n";
	cout << "\n--------------------------------\n";
	cout << bst.predecessor2(70).second << "\n";
	cout << bst.predecessor2(20).second << "\n";
	cout << bst.predecessor2(45).second << "\n";
	cout << bst.predecessor2(35).second << "\n";
	cout << bst.predecessor2(60).second << "\n";
	cout << bst.predecessor2(73).second << "\n";
	cout << bst.predecessor2(50).second << "\n";
	cout << bst.predecessor2(15).second << "\n";//-1 coz no element samller than em
	cout << "\n--------------------------------\n";
	cout << "\n--------------------------------\n";
	BinarySearchTree bst5(10);
	bst5.insert(5);
	bst5.insert(3);
	bst5.delete_value(10);
	bst5.print_inorder();
	cout << "\n--------------------------------\n";
	cout << "\n--------------------------------\n";
	BinarySearchTree bst6(10);
	bst6.insert(5);
	bst6.insert(3);
	bst6.delete_value2(10);
	bst6.print_inorder();
	return 0;
}