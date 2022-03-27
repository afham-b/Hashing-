//Afham Bashir
//Asssignment 7 

#include "hashtable.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
using namespace std;

string random_key();

class HashCheck {
private:
	size_t count;
	HashTable<int> hash;
public:
	HashCheck(const HashTable<int>& h) : hash(h) { count = 0; }
	void operator() (const string key) {
		if (hash[key] != ++count)
			cout << "Key " << key << " does not match value " << count << endl;
	}
};

int main() {

	HashTable<int> hash; // Hash table for testing
	list<string> keys; // Keys added to hash table

//	srand(time((time_t)0)); // Init RNG
  srand(time(0));  //orginal srand function had data type conversion issues. 

	// Add unique entries to the table, filling it to capacity
	size_t count = 0;
	while (count < HashTable<int>::TABLE_SIZE) {
		string key = random_key();
		if (find(keys.begin(), keys.end(), key) == keys.end()) {
			cout << key << endl; // Uncomment to see keys generated
			keys.push_back(key);
			hash[key] = ++count;
		}
	}

	// Verify that all keys map to their original values
	for_each(keys.begin(), keys.end(), HashCheck(hash));

  cout<<"\nThe Number of Collisions: " << hash.collisions(keys) << endl; 
  //output the number of collisions. 

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}

string random_key() {
	// Generate a random string of length 1 through 40
	size_t len = rand() % 40 + 1;
	string key;
	for (size_t i = 0; i < len; i++)
		key += 'a' + rand() % 26;
	return key;
}