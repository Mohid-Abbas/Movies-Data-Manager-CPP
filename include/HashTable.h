#pragma once
#include "LinkedList.h"
#include "String.h"

// Hash Table implementation using separate chaining
template <typename K, typename V>
class HashTable {
private:
    // Key-Value pair
    struct Entry {
        K key;
        V value;

        Entry() {}
        Entry(const K& k, const V& v) : key(k), value(v) {}

        bool operator==(const Entry& other) const {
            return key == other.key;
        }
    };

    LinkedList<Entry>* table;
    int capacity;
    int size;
    const double loadFactorThreshold = 0.75;

    // Hash function for String keys
    int hashFunction(const String& key) const {
        unsigned long hash = 5381;
        for (int i = 0; i < key.length(); i++) {
            hash = ((hash << 5) + hash) + key[i]; // hash * 33 + c
        }
        return hash % capacity;
    }

    // Generic hash function (for other types)
    template <typename T>
    int hashFunctionGeneric(const T& key) const {
        return (unsigned long)key % capacity;
    }

    // Get hash index
    int getHashIndex(const K& key) const {
        return hashFunction(key);
    }

    // Resize and rehash
    void resize() {
        int oldCapacity = capacity;
        LinkedList<Entry>* oldTable = table;

        capacity = capacity * 2;
        table = new LinkedList<Entry>[capacity];
        size = 0;

        // Rehash all entries
        for (int i = 0; i < oldCapacity; i++) {
            for (auto it = oldTable[i].begin(); it != oldTable[i].end(); ++it) {
                insert((*it).key, (*it).value);
            }
        }

        delete[] oldTable;
    }

public:
    // Constructor
    HashTable(int initialCapacity = 100) : capacity(initialCapacity), size(0) {
        table = new LinkedList<Entry>[capacity];
    }

    // Copy constructor
    HashTable(const HashTable& other) : capacity(other.capacity), size(0) {
        table = new LinkedList<Entry>[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = other.table[i];
        }
        size = other.size;
    }

    // Assignment operator
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            delete[] table;
            capacity = other.capacity;
            size = 0;
            table = new LinkedList<Entry>[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = other.table[i];
            }
            size = other.size;
        }
        return *this;
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Insert key-value pair
    void insert(const K& key, const V& value) {
        int index = getHashIndex(key);

        // Check if key already exists and update
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).key == key) {
                (*it).value = value;
                return;
            }
        }

        // Insert new entry
        table[index].append(Entry(key, value));
        size++;

        // Check load factor and resize if needed
        if ((double)size / capacity > loadFactorThreshold) {
            resize();
        }
    }

    // Search for key and return value
    V* search(const K& key) {
        int index = getHashIndex(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).key == key) {
                return &((*it).value);
            }
        }
        return nullptr;
    }

    const V* search(const K& key) const {
        int index = getHashIndex(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).key == key) {
                return &((*it).value);
            }
        }
        return nullptr;
    }

    // Check if key exists
    bool contains(const K& key) const {
        return search(key) != nullptr;
    }

    // Remove key-value pair
    bool remove(const K& key) {
        int index = getHashIndex(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it).key == key) {
                table[index].remove(*it);
                size--;
                return true;
            }
        }
        return false;
    }

    // Get size
    int getSize() const {
        return size;
    }

    // Check if empty
    bool isEmpty() const {
        return size == 0;
    }

    // Clear hash table
    void clear() {
        for (int i = 0; i < capacity; i++) {
            table[i].clear();
        }
        size = 0;
    }

    // Get all keys
    LinkedList<K> getKeys() const {
        LinkedList<K> keys;
        for (int i = 0; i < capacity; i++) {
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                keys.append((*it).key);
            }
        }
        return keys;
    }

    // Get all values
    LinkedList<V> getValues() const {
        LinkedList<V> values;
        for (int i = 0; i < capacity; i++) {
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                values.append((*it).value);
            }
        }
        return values;
    }

    // Display hash table (for debugging)
    void display() const {
        for (int i = 0; i < capacity; i++) {
            if (!table[i].isEmpty()) {
                std::cout << "Bucket " << i << ": ";
                for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                    std::cout << "[" << (*it).key << "] ";
                }
                std::cout << std::endl;
            }
        }
    }
};
