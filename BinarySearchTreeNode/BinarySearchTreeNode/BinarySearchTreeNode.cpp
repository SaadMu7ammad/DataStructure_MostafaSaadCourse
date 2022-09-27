#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class BinarySearchTree {
    struct BinaryNode {
        int data{};
        BinaryNode* left{};
        BinaryNode* right{};
        BinaryNode(int data) :data(data) {};
    };
    BinaryNode* root{};
    void insert_val(int val,BinaryNode *node) {
        if (node == nullptr) {
            node->data = val;
        }
        else {
            if (val > node->data) {
                if (node->right == nullptr) 
                    node->right = new BinaryNode(val);
                else
                insert_val(val, node->right);
            }
            else if (val < node->data) {
                if (node->left == nullptr)
                    node->left = new BinaryNode(val);
                else
                    insert_val(val, node->left);
            }
        }
    }
    bool search(int val,BinaryNode *node) {
        if (node == nullptr)return 0;

        if (val > node->data) {
            return node->right&&search(val, node->right);
        }
        else  if (val < node->data) {
            return node->left&&search(val, node->left);
        }
        else {
            return 1;
        }
        return 0;
    }
    void print(BinaryNode* node) {
        if (node == nullptr)return;
        if (node->left) {
            print(node->left);
        }
        cout << node->data<<" ";
        if (node->right) {
            print(node->right);
        }
    }
    void level(BinaryNode* node) {
        if (node == nullptr)return;
        cout << "******************\n";
        queue<BinaryNode*>q;
        q.push(root);
        int lvl = 0;
        while (!q.empty()) {
            int sz = q.size();
            cout << "LEVEL" << lvl++ << "\n";
            while (sz--) {
                BinaryNode* temp = q.front();
                q.pop();
                cout << temp->data << " ";
                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (temp->left != nullptr) {
                    q.push(temp->left);
                }
            } 
            cout << "\n";
        }
    }
    int min(BinaryNode* node) {
        if (node->left == nullptr)return node->data;
        return min(node->left);
    }
    BinaryNode* min_node(BinaryNode* node) {
        if (node->left == nullptr)return node;
        return min_node(node->left);
    }
    BinaryNode* max_node(BinaryNode* node) {
        if (node->right == nullptr)return node;
        return max_node(node->right);
    }
    //BinaryNode* prev(int val, BinaryNode* node, BinaryNode* _prev) {
    //   if (val == root->data)return max_node(root->left);
    //    if (val > node->data) {
    //        _prev = node;
    //        return  prev(val, node->right, _prev);
    //    }
    //    else  if (val < node->data) {
    //        _prev = node;
    //        return prev(val, node->left, _prev);
    //    }
    //    else {
    //        if(node->right) {
    //            _prev = min_node(node->right);
    //        }
    //        else if (node->left) {
    //            _prev = max_node(node->left);
    //        }
    //        return  _prev;
    //    }
    //}
    BinaryNode* del(int val, BinaryNode* node) {
        if (!node)
            return nullptr;
        if (val < node->data)
            node->left = del(val, node->left);
        else if (val > node->data)
            node->right = del(val, node->right);
        else {
            BinaryNode* temp = node;
            if (!node->left && !node->right)	// case 1: no child
                node = nullptr;
            else if (!node->right) 	// case 2: has left only
                node = node->left;		// connect with child
            else if (!node->left)	// case 2: has right only
                node = node->right;
            else { 
                BinaryNode* mn = min_node(node->right);
                node->data = mn->data;
                node->right = del(node->data, node->right);
                temp = nullptr;
            }
            if (temp)
            delete temp;
        }
        return node;
    }
public:
    BinarySearchTree(int val){
        root = new BinaryNode(val);
    }
   /* BinaryNode* prev(int val) {
        return prev(val, root, nullptr);
    }*/
    void insert_val(int val) {
        insert_val(val, root);
    }
    void delete_val(int val) {
        del( val, root);
    }
    int minimum() {
        return min(root);
    }
    bool search(int val) {
        return search(val, root);
    }
    void print_inorder() {
        print(root);
    }
    void level_order_traversal() {
        level(root);
    }
};
int main()
{
    BinarySearchTree bst(50);
    bst.insert_val(20);
    bst.insert_val(15);
    bst.insert_val(45);
    bst.insert_val(35);
    bst.insert_val(60);
    bst.insert_val(70);
    bst.insert_val(73);

    cout << bst.search(73) << "\n";
    cout << bst.search(733) << "\n";
    cout << bst.search(20) << "\n";
    cout<<bst.search(45)<<"\n";
    bst.print_inorder();
    cout << "\n";
    bst.level_order_traversal();
    cout << '\n';
    cout << bst.minimum()<<"\n";    
    cout << "----------------------\n";
    BinarySearchTree bst2(50);
    bst2.insert_val(10);
    bst2.insert_val(60);
    bst2.insert_val(55);
    bst2.insert_val(65);
    bst2.print_inorder();
    bst2.delete_val(10);
    bst2.print_inorder();
    return 0;
}

