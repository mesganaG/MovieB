#ifndef HashTable_h
#define HashTable_h

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename K, typename V> // k for key, v for value
class HashTable {
  friend ostream &operator<<(ostream &os, const HashTable &ht) {
    for (int i = 0; i < ht.keys.size(); i++) {
      os << "[" << ht.keys[i] << "] = " << *ht.values[i] << endl;
    }
    return os;
  }

public:
  HashTable() = default;

  // Based some of these off of Java's HashMap.
  void put(K &key, V &value) {
    int index = this->indexOf(key);
    if (index ==
        -1) { // indexOf returns -1 if the key doesn't exist in our hashtable.
      keys.push_back(key);
      values.push_back(value);
    } else { // If our indexOf does not return -1, that means it already exists,
             // just replace the old value with the new one.
      values[index] = value;
    }
  }

  bool isEmpty() { return keys.empty(); }
  bool clear() {
    if (this->isEmpty()) {
      return false;
    }
    keys.clear();
    values.clear();
    return true;
  }

  void remove(K key) {
    int indexToRemove = this->indexOf(key);
    if (indexToRemove == -1) {
      return;
    }
    keys.erase(keys.begin() + indexToRemove);
    values.erase(values.begin() + indexToRemove);
  }

  V &get(K key) {
    int index = this->indexOf(key);
    return values[index];
  }

  int indexOf(K key) { // Returns -1 if key doesn't exist, else, return the
                       // index of our key in our vector.
    auto it = find(keys.begin(), keys.end(), key);
    if (it != keys.end()) {
      return it - keys.begin(); // Got our index.
    }
    return -1; // Didn't find object, return -1;
  }

private:
  vector<K> keys;
  vector<V> values;
};
#endif /* HashTable_h */