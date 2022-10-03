#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf{ };

public:
	trie() {
		memset(child, 0, sizeof(child));
	}
	void insert(string str, int indx = 0) {
		if (indx == (int)str.size()){
			isLeaf = 1;
		}
		else {
			int cur = str[indx] - 'a';
			if (child[cur] == 0) {
				child[cur] = new trie();
			}
			child[cur]->insert(str, indx + 1);
		}
	}
	
	void insert_itr(string str){
		trie* cur = this;
		for (int i = 0; i < str.length(); i++) {
			int ch = str[i] - 'a';
			if (cur->child[ch]==0) {
				cur->child[ch] = new trie();
			}
			cur = cur->child[ch];
		}
		cur->isLeaf = true;
	}
	bool word_exist(string str) {
		trie* cur = this;
		for (int i = 0; i < (int)str.size(); i++) {
			int ch = str[i] - 'a';
			if (cur->child[ch] == 0) {
				return false;
			}
			cur = cur->child[ch];
		}
		/*if (cur->isLeaf = true) {
			return true;
		}
		return false;*/
		// ^^^ the same concept ^^^
		return cur->isLeaf;
	}
	string first_word_prefix(string str) {
		trie* cur = this;		
		string temp="";
		for (int i = 0; i < str.length(); i++) {	
			int ch = str[i] - 'a';
				temp += str[i];
			if (cur->child[ch]==0) {
				//return "none";
				break;
			}
			if ( cur->child[ch]->isLeaf == true) {
				return temp;
			}
		cur = cur->child[ch];
		}
		return str;
	}
	void insertSuffix(string str, int indx = 0) {//for suffix(tricky way)
		reverse(str.begin(), str.end());
		trie* cur = this;
		for (int i = 0; i < str.length(); i++) {
			int ch = str[i] - 'a';
			if (cur->child[ch] == 0) {
				cur->child[ch] = new trie();
			}
			cur = cur->child[ch];
		}
		cur->isLeaf = true;
	}
	bool suffix_exist(string str) {
		reverse(str.begin(), str.end());
		trie* cur = this;
		for (int i = 0; i < str.length(); i++) {
			int ch = str[i] - 'a';
			if (cur->child[ch] == 0) {
				return false;
			}
			cur = cur->child[ch];
		}
		return true;

	}
	// O(NL) where N number of words and L is word length.
	void get_all_string(vector<string>&res,string adder="") {
		if (isLeaf)
			res.push_back(adder);

		for (int i = 0; i < MAX_CHAR; i++) {
			if (child[i] != 0) {
				child[i]->get_all_string(res, adder + (char)(i + 'a'));
			}
		}
	}
	void auto_complete(const string& str, vector<string>& res) {
		trie* cur = this;
		for (int i = 0; i < str.size(); i++) {
			int ch = str[i] - 'a';
			if (cur->child[ch] == 0) {
				return;

				cur = cur->child[ch];
			}
		}
		cur->get_all_string(res, str);
	}
};
class trieMap {
private:
	static const int MAX_CHAR = 26;
	//trieMap* child[MAX_CHAR];
	map<int,trieMap*>child;//based on bbst
	bool isLeaf{ };

public:
	trieMap() {	}
	void insert(string str, int indx = 0) {
		if (indx == (int)str.size()) {
			isLeaf = 1;
		}
		else {
			int cur = str[indx] - 'a';
			if (child.count(cur) == 0) {
				child[cur] = new trieMap();
			}
			child[cur]->insert(str, indx + 1);
		}
	}
	void insert_itr(string str) {
		trieMap* cur = this;
		for (int i = 0; i < str.length(); i++) {
			int ch = str[i] - 'a';
			if (cur->child.count(ch) == 0) {
				cur->child[ch] = new trieMap();
			}
			cur = cur->child[ch];
		}
		cur->isLeaf = true;
	}
	bool word_exist(string str) {
		trieMap* cur = this;
		for (int i = 0; i < (int)str.size(); i++) {
			int ch = str[i] - 'a';
			if (cur->child.count(ch) == 0) {
				return false;
			}
			cur = cur->child[ch];
		}
		/*if (cur->isLeaf = true) {
			return true;
		}
		return false;*/
		// ^^^ the same concept ^^^
		return cur->isLeaf;
	}
	
};
class trieMapOS {
private:
	static const int MAX_CHAR = 26;
	//trieMap* child[MAX_CHAR];
	map<string, trieMapOS*>child;//based on bbst
	bool isLeaf{ };

public:
	trieMapOS() {	}
	
	void insert_itr(const vector<string> &str) {
		trieMapOS* cur = this;
		for (int i = 0; i < str.size(); i++) {
			string ch = str[i] ;
			if (cur->child.count(ch) == 0) {
				cur->child[ch] = new trieMapOS();
			}
			cur = cur->child[ch];
		}
		cur->isLeaf = true;
	}
	bool subpath_exist(const vector<string>& path) {
		trieMapOS* cur = this;
		for (int i = 0; i < (int)path.size(); i++) {
			string ch = path[i];
			if (cur->child.count(ch) == 0) {
				return false;
			}
			if (i == (int)path.size() - 1) {
				return true;
			}
			cur = cur->child[ch];
		}
	}
	

};
void triemap_operations() {
	trieMap root4;
	root4.insert_itr("abc");
	root4.insert_itr("xyzwfe");
	root4.insert_itr("ab");
	cout << root4.word_exist("c") << "\n";
	cout << root4.word_exist("dsaf") << "\n";
	cout << root4.word_exist("ba") << "\n";
	cout << root4.word_exist("ab") << "\n";
}
void TrieMapString_operations() {
	trieMapOS tree5;

	vector<string> path;

	path = { "home", "software", "eclipse" };
	tree5.insert_itr(path);

	path = { "home", "software", "eclipse", "bin" };
	tree5.insert_itr(path);

	path = { "home", "installed", "gnu" };
	tree5.insert_itr(path);

	path = { "user", "mostafa", "tmp" };
	tree5.insert_itr(path);

	path = { "user", "mostafa", "tmp" };
	cout << tree5.subpath_exist(path) << "\n"; // 1

	path = { "user", "mostafa" };
	cout << tree5.subpath_exist(path) << "\n"; // 1

	path = { "user", "mostafa", "private" };
	cout << tree5.subpath_exist(path) << "\n"; // 0
}
int main()
{
	trie tree;
	tree.insert("abcd");
	tree.insert("xyz");
	tree.insert("a");
	tree.insert("ab");
	tree.insert("xyzw");
	tree.insert("bcd");
	cout << tree.word_exist("xyz") << "\n";
	cout << tree.word_exist("xy") << "\n";
	cout << tree.word_exist("bcdr") << "\n";
	cout << tree.word_exist("bcd") << "\n";
	cout << "--------------\n";
	cout << "--------------\n";
	vector<string>res;
	tree.get_all_string(res);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << "\n";
	}
	cout << "--------------\n";
	cout << "--------------\n";
	vector<string>res2;
	tree.auto_complete("ab", res2);
	for (int i = 0; i < res2.size(); i++) {
		cout << res2[i] << "\n";
	}
	cout << "--------------\n";
	cout << "--------------\n";
	trie root2;
	root2.insert("xyz");
	root2.insert("xyzwfe");
	root2.insert("ab");
	cout << root2.first_word_prefix("xyeee") << "\n";
	cout << root2.first_word_prefix("x") << "\n";
	cout << root2.first_word_prefix("xyzabc") << "\n";
	cout << root2.first_word_prefix("ab") << "\n";
	trie root3;
	root3.insertSuffix("abc");
	root3.insertSuffix("xyz");
	root3.insertSuffix("a");
	root3.insertSuffix("ab");
	root3.insertSuffix("xyzw");
	root3.insertSuffix("bcd");
	cout << "--------------\n";
	cout << root3.suffix_exist("c") << "\n";
	cout << root3.suffix_exist("dsaf") << "\n";
	cout << root3.suffix_exist("ba") << "\n";
	cout << root3.suffix_exist("ab") << "\n";
	cout << "--------------\n";
	triemap_operations();
	cout << "--------------\n";
	TrieMapString_operations();
	cout << "--------------\n";

	return 0;
}