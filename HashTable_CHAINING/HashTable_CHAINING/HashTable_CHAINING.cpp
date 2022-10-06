#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//int hash_string(string str, int n = 65407) {
//	long long sum = 0;//to avoid overflow
//	long long nn = n;
//	for (int i = 0; i < (int)str.size(); ++i) {
//		int val = 0;
//		val = str[i] - 'a';
//		sum = (sum * 26 + val) % nn;	// base 26 number
//	}
//	return sum;
//}
int hash_string(string str, int n = 65407) {
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
struct PhoneEntry {
	const static int INTERNAL_LIMIT = 2147483647;
	string name;			// key
	string phone_number;	// data
	int hash() {
		return hash_string(name, INTERNAL_LIMIT);
	}
	PhoneEntry(string name, string phone_number) :
		name(name), phone_number(phone_number) {
	}
	void print() {
		cout << "(" << name << ", " << phone_number << ")  ";
	}
};
class PhoneHashTable {
private:
	int table_size{ };
	double limit_load_factor{ };
	int total_elements{ };
	vector<vector<PhoneEntry>> table;
public:
	PhoneHashTable(int table_size = 10, double limit_load_factor = 0.75) :
		table_size(table_size), limit_load_factor(limit_load_factor) {
		table.resize(table_size);
	}
	void rehashing() {
		double cur_load_factor = (double)total_elements / table_size;
		cout << cur_load_factor << "\n";
		if (cur_load_factor < limit_load_factor)
			return;
		PhoneHashTable new_table(2 * table_size, limit_load_factor);
		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash].size() == 0)
				continue;
			for (int i = 0; i < (int)table[hash].size(); ++i)
				new_table.put(table[hash][i]);
		}
		// Copy & delete
		table_size *= 2;
		table = new_table.table;

		print_all();
	}
	bool get(PhoneEntry& phone) {
		int idx = phone.hash() % table_size;
		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				//phone = table[idx][i];
				return true;
			}
		}
		return false;
	}
	void put(PhoneEntry phone) {
		int idx = phone.hash() % table_size;

		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				table[idx][i] = phone; // exist => update
				return;
			}
		}//not found so it would be an insert not update
		++total_elements;
		rehashing();
		table[idx].push_back(phone);
	}
	bool remove(PhoneEntry phone) {
		int idx = phone.hash() % table_size;
		for (int i = 0; i < (int)table[idx].size(); ++i) {
			if (table[idx][i].name == phone.name) {
				// Swap with last and remove last in O(1)
				swap(table[idx][i], table[idx].back());
				table[idx].pop_back();
				--total_elements;
				rehashing();
				return true;
			}
		}
		return false;
	}
	void print_all() {
		cout << "**********************\n";
		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash].size() == 0)
				continue;

			cout << "Hash " << hash << ": ";
			for (int i = 0; i < (int)table[hash].size(); ++i)
				table[hash][i].print();
			cout << "\n" << flush;
		}
	}

};
class phoneHashTablelinkedlist {
private:
	struct linked_listHash {
		PhoneEntry item;
		linked_listHash* next{ };
		linked_listHash(PhoneEntry item) : item(item) {}
		//linked_listHash* head{ };
	   // linked_listHash* tail{ };
	};
	int table_size{ };
	vector<linked_listHash*> table{};
public:
	phoneHashTablelinkedlist(int table_size) :table_size(table_size) {
		table.resize(table_size);
	}
	//void put(PhoneEntry phone) {
	//	linked_listHash *_phone= new linked_listHash(phone);
	//	int hash = phone.hash() % table_size;
	//	
	//	if (table[hash]->head == nullptr && table[hash]->tail == nullptr) {
	//		table[hash]->head = _phone;
	//		table[hash]->tail = _phone;
	//	}
	//	else {
	//		linked_listHash* cur =table[hash]->head;
	//		while (cur) {
	//			if (cur->item.name == phone.name) {
	//				cur->item = phone;	// exist => update
	//				return;
	//			}
	//			cur = cur->next;
	//		}
	//		table[hash]->tail->next = _phone;
	//		table[hash]->tail = _phone;
	//	}
	//}
	void put(PhoneEntry phone) {
		int hash = phone.hash() % table_size;

		if (!table[hash])
			table[hash] = new linked_listHash(phone);
		else {
			linked_listHash* head = table[hash];
			while (head->next) {
				if (head->item.name == phone.name) {
					head->item = phone;	// exist => update
					return;
				}
				head = head->next;
			}
			// head now is tail
			if (head->item.name == phone.name)
				head->item = phone;	// exist => update
			else
				head->next = new linked_listHash(phone);
		}
	}
	void print_all() {
		cout << "**********************\n";
		for (int hash = 0; hash < table_size; ++hash) {
			if (table[hash] == nullptr)
				continue;
			cout << "Hash " << hash << ": ";
			for (linked_listHash* i = table[hash]; i; i = i->next) {
				i->item.print();
			}
			cout << "\n" << flush;
		}
	}
};
string to_str(int val) {
	ostringstream oss;
	oss << val;
	return oss.str();
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
	PhoneHashTable table2;
	for (int i = 0; i < 5; ++i) {
		table2.put(PhoneEntry(to_str(i), to_str(i * 10)));
	}
	cout << "---\n";
	cout << "---\n";

	phoneHashTablelinkedlist table(3);
	table.put(PhoneEntry("mostafa", "604-401-120"));
	table.put(PhoneEntry("mostafa", "604-401-777"));	// update
	table.put(PhoneEntry("ali", "604-401-343"));
	table.put(PhoneEntry("ziad", "604-401-17"));
	table.put(PhoneEntry("hany", "604-401-758"));
	table.put(PhoneEntry("belal", "604-401-550"));
	table.put(PhoneEntry("john", "604-401-223"));

	table.print_all();
	return 0;
}
