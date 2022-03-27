//Afham Bashir.
//Assignment 7 
#pragma once

#include <iomanip>
#include <iostream>
#include <string> 
#include <list> //added for the string parameter that collisions uses 

template <typename T>
class HashTable {
public:
	static const size_t TABLE_SIZE = 1000;

private:

	class Entry { // An entry in the table
	public:
		std::string key;
		T data;
		bool used;
		Entry () { used = false;}  
	};

	Entry entries[TABLE_SIZE];

	size_t hash1 (const std::string& key) const {
		size_t hashVal = 0;
		for (char ch: key)
			hashVal += ch;
		return hashVal % TABLE_SIZE;
	}

	// This funciton simply calls the appropriate hash function being used
	// for testing.
	size_t hash (const std::string& key) const { return hash1(key); }

  size_t hash2 (const std::string& key) const {
 
    if( key.size() == 2 ) { 
    return ( key[ 0 ] + 27 * key[ 1 ]  ) % TABLE_SIZE; } 
    if( key.size() == 1){ 
    return ( key[ 0 ]) % TABLE_SIZE; } 
    //return hash with different algorithm depending on the number of char in the random string
    
    else {  // if the random string has more thna two char. 
      return ( key[ 0 ] + 27 * key[ 1 ] + 729 * key[ 2 ] ) % TABLE_SIZE; }
      //multiplies the first 3 characters of the random string key, after using scalars, mods by table size to keep inbounds

  }

  size_t hash3 (const std::string& key) const {
    size_t hashVal = 0;
    for( char ch : key )
      hashVal = 37 * hashVal + ch;
      //hash is calculated by mulitply the hasv values, and adding value of all chars
    return hashVal % TABLE_SIZE;
  }
  
public:
	// Operator [] is overloaded to use a string value as the index to the
	// table.
	T& operator[] (const std::string& k);
	const T& operator[] (const std::string& k) const;

	// The print function is provided only for debugging and experimentation
	// purposes.
	void print (std::ostream& out) const;
  size_t collisions (std::list<std::string> keys) const; 
    //prototype that finds number of collisions and is constant. 
};

  //collisions takes the list of all the random strings already generated in the main. 
  template<typename T>
  size_t HashTable<T>::collisions ( std::list<std::string> keys) const { 
    size_t count =0 ;     // used to track the number of collisions 
    int expected_index;   // will contain the expected hash of the key 
    int actual_index;     // index of the location of key in the entries arrray 
    
    for( std::list<std::string>::iterator itr = keys.begin( ); itr != keys.end( ); ++itr ) { //iterator loops through all keys 
      std::string key= *itr;    //deferencing the iterator provides the string key located there
      expected_index = hash(key);   // calls the hash funcion for the key, and returns hash based on algorithm

      // i goes through all keys to find actual location of key in the entries arrray 
        for( int i =0; i < TABLE_SIZE; i++ ){  
          if( entries[i].key == key  ) { 
            actual_index = i; 
            break;  //breaks when index has been found
            } 
          }

      if (expected_index != actual_index) { 
        //if the expected hash and the acutal location index arent same there was a collision
        count++; 
      }

    }
  return count; 
} 

template <typename T>
T& HashTable<T>::operator[] (const std::string& k) {
// Determine the index appropriate to the given
//	key value (k). If the entry at that index is not previously used, establish
//	it as a new entry.

	// Determine the has value for k
	size_t index = hash(k);

	// Find the actual index for k
	size_t count = 0;
	while (entries[index].used && entries[index].key != k) {
		if (++count > TABLE_SIZE)
			throw "Hash table overflow";
		index = (index + 1) % TABLE_SIZE; // Linear probing...
	}

	// index is location where k is to be stored
	if (!entries[index].used) {
		entries[index].key = k;
		entries[index].used = true;
	}

	return entries[index].data;
}

template <typename T>
const T& HashTable<T>::operator[] (const std::string& k) const {
// Determine the index appropriate to the given
//	key value (k). If the entry at that index is not previously used, throw
//	an exception.

	size_t index = hash(k);
	size_t count = 0;
	while (entries[index].used && entries[index].key != k &&
			++count <= TABLE_SIZE)
		index = (index + 1) % TABLE_SIZE;

	if (!entries[index].used || entries[index].key != k)
		throw "Key not found";

	return entries[index].data;
}

template <typename T>
void HashTable<T>::print (std::ostream& out) const {
	// Outputs the hash table for debugging and experimentation purposes.
	out << "   Index    Hash  Key\n";
	out << "   -----    ----  ---\n";
	for (size_t i = 0; i < TABLE_SIZE; i++)
		if (entries[i].used)
			out << std::setw(8) << i << std::setw(8) << hash(entries[i].key)
				<< "  " << entries[i].key << std::endl;
}