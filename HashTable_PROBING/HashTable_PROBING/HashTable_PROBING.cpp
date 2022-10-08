#include<iostream>
#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
int hash_string(string str, int n = 65407) {
	long long sum = 0;//to avoid overflow
	long long nn = n;
	for (int i = 0; i < (int)str.size(); ++i) {
		int val = 0;
		val = str[i] - 'a';
		sum = (sum * 26 + val) % nn;	// base 26 number
	}
	return sum;
}
int hash_string_num(string str, int n = 65407) {
	long long sum = 0;//to avoid overflow
	long long nn = n;
	for (int i = 0; i < (int)str.size(); ++i) {
		int val = 0;
		//lower from 0,25 //upper from 26,51 //digit from 52,61
		if (islower(str[i]))
			val = str[i] - 'a';
		else if (isupper(str[i]))
			val = 26 + str[i] - 'A';
		else if (isdigit(str[i]))
			val = (26 * 2) + str[i] - '0';

		sum = (sum * 62 + val) % nn;	// base =26 lower+26 upper+10 number=62
	}
	return sum;
}
int hash_folding(string str, int n = 65407) {
	long long sum = 0;//to avoid overflow
	long long nn = n;
	for (int i = 0; i < (int)str.size(); i += 4) {
		string block = str.substr(i, 4);
		sum += hash_string(block);
		sum %= nn;
	}
	return sum;
}
struct phoneInfo {
	const static int INTERNAL_LIMIT = 65407;
	string name;
	string number;
	phoneInfo(string name, string number):name(name),number(number) {}
	int hash() {
		return hash_string(name);
	}
	void print() {
		cout << name << " " << number << "\n";
	}
};

class PhoneHashTable {
private:
	
	int table_size{};
	vector < phoneInfo*>table;
	vector < int>num;
	phoneInfo* deleted = new phoneInfo("", "");

public:
	PhoneHashTable(int table_size):table_size(table_size) {
		table.resize(table_size);
	}
	bool put(phoneInfo info) {
		int hash = info.hash() % table_size;
		for (int step = 0; step < table_size; step++) {//the loop to tell that table is full means that we iterating on the whole steps 
			if (table[hash] == deleted || table[hash] == nullptr) {
				table[hash] = new phoneInfo(info.name, info.number);
				return true;
			}
			else if (table[hash]->name == info.name) {
				table[hash]->number = info.number;
				return true;
			}
			hash = (hash + 1) % table_size;
		}
		return false;
	}
	bool remove(phoneInfo info) {
		int hash = info.hash() % table_size;
		for (int step = 0; step < table_size; step++) {//the loop to tell that table is full means that we iterating on the whole steps 
			if (table[hash] == nullptr) {
				return false;
			}
			else if (table[hash]->name == info.name) {
				delete table[hash];
				table[hash] = deleted;
				return true;
			}
			hash = (hash + 1) % table_size;
		}
		return false;
	}
	bool get(phoneInfo &info) {
		int hash = info.hash() % table_size;
		for (int step = 0; step < table_size; step++) {//the loop to tell that table is full means that we iterating on the whole steps 
			if (table[hash] == nullptr) {
				break;
			}
			else if (table[hash]->name == info.name) {
				info.number = table[hash]->number;
				return true;
			}
			hash = (hash + 1) % table_size;
		}
		return false;
	}
	void print_all() {
		
		for (int i = 0; i < table_size; i++) {//the loop to tell that table is full means that we iterating on the whole steps 
			cout << "Hash: " << i << " ";
			if (table[i] == nullptr) {
				cout << "Empty\n";
			}
			else if (table[i] == deleted) {
				cout << "X\n";//deleted
			}
			else {
				table[i]->print();
				
			}
			cout << "\n";
			
		}
	}


};

int count_distinct_substr(string str)
{
	unordered_set<string> st;
	int c = 0;
	for (int i = 0; i < str.length(); i++) {
		string subStr;
		for (int j = i; j < str.length(); j++) {
			subStr += str[j];
			st.insert(subStr);
		}
	}
	return st.size() ;
}
int common_substr(string str1,string str2)
{
	unordered_set<string> st1;
	for (int i = 0; i < str1.length(); i++) {
		string subStr;
		for (int j = i; j < str1.length(); j++) {
			subStr += str1[j];
			st1.insert(subStr);
		}
	}
	unordered_set<string> st2;
	int c = 0;
	for (int i = 0; i < str2.length(); i++) {
		string subStr;
		for (int j = i; j < str2.length(); j++) {
			subStr += str2[j];
			st2.insert(subStr);
		}
	}
	for (auto& it : st1) 
		c += st2.count(it);
	return c;
}
int unique_anagrams(string str) {
	unordered_set<string> st;
	int c = 0;
	for (int i = 0; i < str.length(); i++) {
		string subStr;
		for (int j = i; j < str.length(); j++) {
			subStr += str[j];
		//	cout << subStr << " " ;
			sort(subStr.begin(), subStr.end());
			st.insert(subStr);
		}
	}
	return st.size();
}
int hash_vector(const vector<int>& vec) {
	// No need to worry how implemented.
	// src: https://stackoverflow.com/questions/29855908/c-unordered-set-of-vectors
	hash<int> hasher;
	unsigned int seed = 0;
	for (int i : vec)
		seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	return seed % 2147483647;
}
struct HashEntry {
	vector<int> vec;
	int hash() {
		return hash_vector(vec);
	}
	HashEntry(const vector<int>& vec) :
		vec(vec) {
	}
};
class HashTable {
private:
	int table_size;
	vector<vector<HashEntry>> table;
	int total_items = 0;
public:
	HashTable(int table_size = 997) :	// 997 is prime
		table_size(table_size) {
		table.resize(table_size);
	}

	void put(HashEntry item) {
		int idx = item.hash() % table_size;

		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].vec == item.vec) {
				table[idx][i] = item; // exist => update
				return;
			}
		}
		table[idx].push_back(item);
		++total_items;
	}

	int size() {
		return total_items;
	}
};
//Advanced HW Problem

int count_anagram_substrings(const string& str) {	// O(L^3)
	// Add all substrings. To avoid sorting:
	// Represent each string in terms of letters frequency!
	// 2 anagrams have the same letters frequency!
	HashTable s1;
	for (int start = 0; start < (int)str.size(); ++start) {
		for (int end = start; end < (int)str.size(); ++end) {
			vector<int> freq(26);	// O(const)
			for (int i = start; i <= end; ++i)
				++freq[str[i] - 'a'];
			s1.put(freq);
		}
	}
	return s1.size();
}

int main() {
	cout << hash_string("abc", 7) << "\n";		// 0+1*26+2 = 28 % 7 = 0
	cout << hash_string("abcde", 70) << "\n";	// 19010 % 70 = 40  <<< >>>// 1 * 26 * 26 * 26 + 2 * 26 * 26 + 3 * 26 + 4 = 19010
	cout << "---\n";
	cout << hash_string("1aAbc") << "\n";//62398
	cout << hash_string("1aAb") << "\n";//9446
	cout << hash_string("c") << "\n";//2
	cout << "---\n";
	cout << hash_folding("1aAbc") << "\n";//9448 
	cout << hash_folding("1aAb") << "\n";//9446 
	cout << hash_folding("c") << "\n";//2
	cout << "---\n";
	cout << "---\n";
	PhoneHashTable table(11);
	table.put(phoneInfo("mostafa", "604-401-120"));
	table.put(phoneInfo("mostafa", "604-401-777"));
	table.put(phoneInfo("ali", "604-401-343"));
	table.put(phoneInfo("ziad", "604-401-17"));
	table.put(phoneInfo("hany", "604-401-758"));
	table.put(phoneInfo("belal", "604-401-550"));
	table.put(phoneInfo("john", "604-401-223"));

	table.print_all();

	cout << table.remove(phoneInfo("smith", "")) << "\n"; // 0
	cout << table.remove(phoneInfo("hany", "")) << "\n";  // 1
	cout << table.remove(phoneInfo("john", "")) << "\n";  // 1
	table.print_all();
	cout << "----------------\n";
	phoneInfo e("belal", "");
	if (table.get(e))
		cout << e.number << "\n";	// 604-401-550

	table.put(phoneInfo("hany", "604-401-555"));
	table.print_all();
	cout << "----------------\n";
	cout << count_distinct_substr("aaab") << "\n";
	cout << common_substr("aaab", "aa")<<"\n";
	cout << unique_anagrams("abba")<<"\n";
	cout << count_anagram_substrings("abba") << "\n";
	return 0;
}
