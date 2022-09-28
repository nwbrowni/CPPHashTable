#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class HashTable {
    private:
        static const int hashGroups = 10;
        list<pair<int, string>> table[hashGroups];  // array of lists of pairs

    public:
        bool isEmpty() const;
        int hashFunction(int key);
        void insertItem(int key, string value);
        void removeItem(int key);
        string searchTable(int key);
        void printTable();
};

bool HashTable::isEmpty() const {
    int sum{};

    // go through all the lists and add up the size
    for (int i{}; i < hashGroups; i++) {
        sum += table[i].size();
    }

    if (!sum) {
        return true;
    }
    return false;
}

int HashTable::hashFunction(int key) {
    return key % hashGroups;  // key 905, in return this function will spit out 5
}

void HashTable::insertItem(int key, string value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];  // points to the table list that corresponds to the key
    auto bItr = begin(cell);  // points to the start of the table
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        // if it already exists replace the value at that key
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            cout << "[WARNING] Key exists. Value Replaced." << endl;
            break;
        }
    }

    if (!keyExists) {
        cell.emplace_back(key, value);
    }

    return;
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];  // points to the table list that corresponds to the key
    auto bItr = begin(cell);  // points to the start of the table
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        // if we find the key in the table, remove it
        if (bItr->first == key) {
            keyExists = true;
            bItr = cell.erase(bItr);  // remove the LL node
            cout << "[INFO] Item Removed." << endl;
            break;
        }
    }

    if (!keyExists) {
        cout << "[WARNING] Key not found. Pair not removed." << endl;
    }

    return;
}

void HashTable::printTable() {
    // go through each list in the table and print them out
    for (int i{}; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;  // if list is empty move on

        // start at the beginning of the list
        auto bItr = table[i].begin();
        for (; bItr != table[i].end(); bItr++) {
            cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << endl;
        }
    }

    return;
}

int main() {
    HashTable ht;

    // verify is empty
    if (ht.isEmpty()) {
        cout << "Correct answer. Good job." << endl;
    } else {
        cout << "Oh no. We need to check our code!" << endl;
    }

    // test insert
    ht.insertItem(905, "Jim");
    ht.insertItem(201, "Tom");
    ht.insertItem(332, "Bob");
    ht.insertItem(342, "Eric");
    ht.insertItem(124, "Sally");
    ht.insertItem(107, "Sandy");
    ht.insertItem(929, "Barb");
    ht.insertItem(928, "Rob");

    // check our overwriting
    ht.insertItem(928, "Rick");

    // check print
    ht.printTable();

    // check remove
    ht.removeItem(332);
    ht.removeItem(100);  //check robustness

    ht.printTable();

    // test isEmpty 
    if (ht.isEmpty()) {
        cout << "Oh no. We need to check our code!" << endl;
    } else {
        cout << "Correct answer. Good job." << endl;
    }

    return 0;
}