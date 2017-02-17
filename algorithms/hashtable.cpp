#ifndef HASH_TABLE_H
#define HASH_TABLE_H
 
#define TABLE_SIZE 100
 
// Hash node class template
template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value)
        : key(key)
        , value(value)
        , next(nullptr) {
    }
 
    K getKey() const {
        return key;
    }
 
    V& getValue() {
        return value;
    }
 
    V const& getValue() const {
        return value;
    }
 
    void setValue(V value) {
        HashNode::value = value;
    }
 
    HashNode *getNext() const {
        return next;
    }
 
    void setNext(HashNode *next) {
        HashNode::next = next;
    }
private:
    // key-value pair
    K key;
    V value;
    // next bucket with the same key
    HashNode *next;
};
 
// Default hash function class
template <typename K>
struct KeyHash {
    unsigned long operator()(const K& key) const {
        return static_cast<unsigned long>(key) % TABLE_SIZE;
    }
};
 
// Hash map class template
template <typename K, typename V, typename F = KeyHash<K>>
class HashTable {
public:
    HashTable() {
        // construct zero initialized hash table of size
        table = new HashNode<K, V> *[TABLE_SIZE]();
        elements = 0;
    }
 
    ~HashTable() {
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        // destroy the hash table
        delete [] table;
    }
 
    bool get(const K &key, V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];
        while (entry != NULL) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }
 
    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr and entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == nullptr) {
            entry = new HashNode<K, V>(key, value);
            if (prev == nullptr) {
                // insert as first bucket
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
            ++elements;
        } else {
            // just update the value
            entry->setValue(value);
        }
    }
 
    V& operator [] (const K& key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];
        while (entry != NULL) {
            if (entry->getKey() == key) {
                return entry->getValue();
            }
            entry = entry->getNext();
        }
        // key is not found
 
        put(key, V{});
        return (*this)[key];
    }
 
    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr and entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry != nullptr) {
            if (prev == nullptr) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            --elements;
            delete entry;
        }
    }
 
    V& insert(K const& key) {
        put(key, V{});
        return (*this)[key];
    }
 
    size_t size() const {
        return elements;
    }
 
private:
    // hash table
    HashNode<K, V> **table;
    F hashFunc;
    size_t elements;
};
 
#endif // HASH_TABLE_H