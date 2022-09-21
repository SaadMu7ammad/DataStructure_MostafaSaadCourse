
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int data{};
    Node* left{};
    Node* right{};
public:
    Node(int data) :data(data) {}
};
   
class BinaryTree {
    Node* root{};
    
    void print_inorder(Node* cur) {
        if (!cur)return;
        print_inorder(cur->left);
        cout << cur->data << " ";
        print_inorder(cur->right);
    }
    int TreeMax(Node* root)
    {
        if (root == NULL)
            return INT_MIN;
       
        int res = root->data;
        
        res=max(res,TreeMax(root->left));
       
        res = max(res, TreeMax(root->right));
        
        return res;
    }
    int TreeHeight2(Node* root, int height = 0)
    {
        if (root == nullptr)
            return height;


        return max(TreeHeight2(root->left), TreeHeight2(root->right)) + 1;
    }
   
    int TreeHeight(Node* root)
    {
        int lh = 0;
        int rh = 0;
        if (root == NULL) {
            return 0;
        }
        else {
        lh=(TreeHeight(root->left));
        rh=(TreeHeight(root->right));
         
        return max(lh, rh) + 1;
        }
      
       
    }
    int countallnodes(Node* root) {
        //int count=0;
        if (root==nullptr)return 0;
        //return (count+1) + countallnodes(root->right) + countallnodes(root->left);
        return 1+countallnodes(root->right)+countallnodes(root->left);
    }
    int countleaf(Node* root) {
        
        if (root == nullptr)
            return 0;

        else if (root ->left==nullptr&&root->right==nullptr) 
            return 1;
        
        else 
            return countleaf(root->left)+ countleaf(root->right);
        
    }
    bool search(int num, Node* root) {
        if (root==nullptr)return 0;
        
        if (root->data == num)return 1;
        else {
            return search(num,root->left) + search(num,root->right);
        }
    }
    bool perfect(Node* root,int h=-1) {
        if (h == -1)
          h = TreeHeight(root);

         if (root->right == nullptr && root->left == nullptr) {
            return h == 1;
         }
          if ((root->right != nullptr && root->left == nullptr) ||
              (root->right == nullptr && root->left != nullptr)) {
             return false;
         }          
         
         return (perfect(root->left, h - 1) && perfect(root->right, h - 1));
    }
    bool perfectformula(Node* root) {
        int nodes = countallnodes(root);
        int h = TreeHeight(root);
        return (pow(2, h )-1 == nodes);//notice its 2^h not 2^(h+1) coz we asume the h with the root is =1 so we added it before
    }
    void traverselevelbylevel(Node *root) {
       queue<Node*>q; 
       q.push(root);
       while (!q.empty()) {
         Node* front = q.front();
         q.pop();
         cout << front->data<<" ";
         if(front->left)
               q.push(front->left);

         if (front->right)
             q.push(front->right);
       }
       cout << '\n';
    }
    void traverselevelbylevel2(Node* root) {
        queue<Node*>q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int cu_lvl = q.size();
            cout << "level " << level<<": ";
            while (cu_lvl--) {//continue till the q become empty of the node of the level but nots empty at all only the same lvl
                Node* front = q.front();
                q.pop();
                cout << front->data << " ";
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            level++;
            cout << '\n';
        }
    }
    //deque<int> preorder; 
    //deque<int> inorder;

    //Node* generate_binarytree(deque<int>& preorder, deque<int>& inorder, int inorder_start , int inorder_end ) {
    //    if (inorder_end == -1)
    //        inorder_end = (int)inorder.size() - 1;

    //    // next preorder is the current root
    //    root->data = preorder[0];
    //    preorder.pop_front();

    //    // Find where is this root in the inorder current sequence
    //    for (int split = inorder_start; split <= inorder_end; ++split) {
    //        if (inorder[split] == root->data) {
    //            if (inorder_start < split)	// there is a left tree
    //                root->left = generate_binarytree(preorder, inorder, inorder_start, split - 1);
    //            if (split < inorder_end)
    //                root->right = generate_binarytree(preorder, inorder, split + 1, inorder_end);
    //            break;
    //        }
    //    }
    //    return root;
    //}
public:
    //the root initialization
    BinaryTree(int valu_root) :root(new Node(valu_root)) {};
   // BinaryTree(deque<int>& preorder, deque<int>& inorder) :preorder(preorder), inorder(inorder) {};
    BinaryTree() {
		
	}
    void print_inorder() {
        print_inorder(root);
        cout<<"\n";
    }
    void add(vector<int> values, vector<char> direction) {
        assert(values.size() == direction.size());
        Node* current = this->root;
        for (int i = 0; i < (int)values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!current->left) {
                    current->left = new Node(values[i]);
                }
                else {
                    assert(current->left->data == values[i]);
                }
                current = current->left;
            }
            else {
                if (!current->right) {
                    current->right = new Node(values[i]);
                }
                else {
                    assert(current->right->data == values[i]);
                }
                current = current->right;
            }
        }
    }
    int TreeMax()
    {
       return TreeMax(root);
    }
    int TreeHeight()
    {
        return TreeHeight(root);
    }
   
    int TreeHeight2()
    {
        return TreeHeight2(root);
    }
    int countallnodes()
    {
        return countallnodes(root);
    }
    int countleaf()
    {
        return countleaf(root);
    }
    bool search(int num)
    {
        return search( num,root);
    }
    bool perfect()
    {
        return perfect(root);
    }
   bool perfectformula()
    {
        return perfectformula(root);
    }
   void traverselevelbylevel() {
       traverselevelbylevel(root);
   }
   void traverselevelbylevel2() {
       traverselevelbylevel2(root);
   }
  /* Node* generate_binarytree(deque<int>& preorder, deque<int>& inorder) {
       return generate_binarytree(preorder,inorder,0,-1);
   }*/

};

int main()
{
    BinaryTree tree6(1);

    BinaryTree tree5(1);
    tree5.add({ 2 }, { 'L' });
    tree5.add({ 3 }, { 'R' });
    tree5.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    tree5.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
    tree5.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    tree5.add({ 3, 6, 15 }, { 'R', 'R', 'L' });
    tree5.add({ 2, 5, 13 }, { 'L', 'R', 'L' });
    tree5.add({ 3, 6, 12 }, { 'R', 'R', 'R' });
    tree5.add({ 3, 14, 15 }, { 'R', 'L', 'L' });
    tree5.add({ 3, 14, 16 }, { 'R', 'L', 'R' });
    BinaryTree tree4(1);
    tree4.add({ 2 ,4,5 }, { 'L','L','L' });
    tree4.add({ 2 ,4,5 }, { 'L','L','R'});

    tree4.add({ 2 ,5,5 }, { 'L','R','R' });
    tree4.add({ 2 ,5,5}, { 'L','R','L'});

    tree4.add({ 3 ,7 ,5 }, { 'R','R' ,'R' });
    tree4.add({ 3 ,7 ,5}, { 'R','R' ,'L'});

    tree4.add({ 3 ,4 ,5 }, { 'R','L','R' });
    tree4.add({ 3 ,4 ,5}, { 'R','L','L'});

    BinaryTree tree3(2);//the root
    tree3.add({ 9, 4, 7 }, { 'L', 'L', 'L' });
    tree3.add({ 7, 4, 8,10,11 }, { 'R', 'L', 'R','L','R'});

    BinaryTree tree2(1);
    tree2.add({ 2, 4, 7,9,55 }, { 'L', 'L', 'L' ,'L','R' });

    BinaryTree tree(1);
    tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 8,10 }, { 'L', 'L', 'R','L'});
    tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    tree.add({ 3, 6, 15 }, { 'R', 'R', 'L' });
    tree.print_inorder();
    tree2.print_inorder();
    tree3.print_inorder();

    cout << tree.TreeMax() << '\n';
    cout << "---------------------------------------------------------------\n";

    cout << tree.TreeHeight() << '\n';
    cout << tree.TreeHeight2() << '\n';
    cout << "\n";
    cout << tree2.TreeHeight() << '\n';
    cout << tree2.TreeHeight2() << '\n';
    cout << "\n";
    cout << tree3.TreeHeight() << '\n';
    cout << tree3.TreeHeight2() << '\n';
    cout << "\n";
    cout << tree4.TreeHeight() << '\n';
    cout << tree4.TreeHeight2() << '\n';
    cout << "\n";
    cout << tree.countallnodes() << '\n';
    cout << tree2.countallnodes() << '\n';
    cout << tree3.countallnodes() << '\n';
    cout << tree4.countallnodes() << '\n';
    cout << "---------------------------------------------------------------\n";
    cout << tree.countleaf() << '\n';
    cout << tree2.countleaf() << '\n';
    cout << tree3.countleaf() << '\n';
    cout << tree4.countleaf() << '\n';
    cout << "---------------------------------------------------------------\n";
    cout << tree.search(5) << '\n';
    cout << tree.search(1) << '\n';
    cout << tree.search(9) << '\n';
    cout << tree.search(12) << '\n';
    cout << tree2.search(55) << '\n';
    cout << tree2.search(555) << '\n';
    cout << tree3.search(10) << '\n';
    cout << tree3.search(7) << '\n';
    cout << "---------------------------------------------------------------\n";
    cout << tree.perfect()  <<" " <<tree.perfectformula()<< '\n';
    cout << tree2.perfect() << " " << tree2.perfectformula() << '\n';
    cout << tree3.perfect() << " " << tree3.perfectformula() << '\n';
    cout << tree4.perfect() << " " << tree4.perfectformula() << '\n';
    cout << tree5.perfect() << " " << tree5.perfectformula() << '\n';
    cout << tree6.perfect() << " " << tree6.perfectformula() << '\n';
    cout << "---------------------------------------------------------------\n";
    tree3.traverselevelbylevel();
    tree3.traverselevelbylevel2();

    //Not implemented
//deque<int>pre{ 1,2,4,7,8,5,9,3,6,10 };
//    deque<int>in{ 7,4,8,2,5,9,1,3,10,6 };
//    //BinaryTree(pre,in );
//    BinaryTree bt;
//    cout << bt.generate_binarytree(pre, in);

   
    return 0;
} 
