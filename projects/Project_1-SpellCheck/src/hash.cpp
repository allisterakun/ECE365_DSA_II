//
//  hash.cpp
//  SpellCheck
//
//  Created by Allister Liu on 9/19/20.
//

#include "hash.hpp"

//prime consants used to calculate hash index from key
#define A 54059             // a prime
#define B 76963             // another prime
#define FIRSTH 37           // also prime

using namespace std;

// The constructor initializes the hash table.
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable::hashTable(int size) : capacity(getPrime(size)), data(capacity), filled(0){}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv){
    int hashIndex = findPos(key);
        if(hashIndex == -1)
        {
            hashIndex = hash(key);
            while(data[hashIndex].isOccupied)
            {
                hashIndex++;
                hashIndex %= capacity;
                if(data[hashIndex].key == key){
                    break;
                }
            }
            data[hashIndex].key = key;
            data[hashIndex].isOccupied = true;
            data[hashIndex].isDeleted = false;
            data[hashIndex].pv = pv;
            filled++;
    
            if(filled > (capacity / 2))
            {
                if(!rehash())
                    return 2;
            }
            return 0;
    
        }
        else {
            data[hashIndex].pv = pv;
            //cout << "WARNING: The word '" << key << "' already exists in the hash table." << endl;
            return 1;
        }
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const string &key){
    return (findPos(key) != -1);
}


// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return nullptr.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void * hashTable::getPointer(const std::string &key, bool *b){
    return nullptr;
}

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const std::string &key, void *pv){
    return 0;
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key){
    unsigned hashIndex = findPos(key);
    if(hashIndex == -1){
        return false;
    }
    data[hashIndex].isDeleted = true;       //lazily deleted.
    return true;
}

// The hash function.
//from StackOverflow
//https://stackoverflow.com/questions/8317508/hash-function-for-a-string
int hashTable::hash(const std::string &key){
    const char *strPtr = key.c_str();       //pointer pointing to the first character of the string.
                                            //the pointer will point to 0 if it reaches the end of the string.
    unsigned int hashIndex = FIRSTH;
    while(*strPtr){
        hashIndex = (hashIndex * A) ^ (strPtr[0] * B);
        strPtr++;
    }
    return hashIndex % capacity;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key){
    int hashIndex = hash(key);
    while(data[hashIndex].isOccupied){
        if(data[hashIndex].key == key){
            if(!data[hashIndex].isDeleted){
                return hashIndex;
            }
            else{
                return -1;
            }
        }
        hashIndex++;
        hashIndex %= capacity;
    }
    return -1;
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
    int oSize = data.size();
    vector<hashItem> temp = data;
    data.clear();
    capacity = getPrime(capacity);
    if(capacity == data.size()) {
        cout << "The hash table has reached its maximum capacity." << endl;
        return false;
    }
    data.resize(capacity);
    if(data.size() != capacity){
        cout << "ERROR: Unable to rehash the hash table." << endl;
        return false;
    }
    int nSize = data.size();
    filled = 0;
    for(auto& item : temp)
    {
        if(item.isOccupied && !item.isDeleted)
            insert(item.key, item.pv);
    }
    //cout << "The has table is resized from" << oSize << " to " << nSize << "." << endl;
    return true;
}


//getPrime function
unsigned int hashTable::getPrime(int size){
    
    static vector<unsigned int> primeNums = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    
    for(unsigned int result : primeNums){
        if(result > (size * 2)){
            return result;
        }
    }
    return primeNums[primeNums.size()-1];
}

void hashTable::display()
{
    for(int i=0 ; i<capacity ; i++)
    {
        if(data[i].isOccupied)
            cout << data[i].key<< endl;
    }
} 
