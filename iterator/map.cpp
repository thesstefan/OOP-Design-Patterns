#include <iostream>

#include "map.h"
#include "pair.h"
#include "vector.h"

template class Map<char, int>;

template <typename Key, typename Value>
Map<Key, Value>::Map() {
    this->keys = new Vector<Key>();
    this->values = new Vector<Value>();
}

template <typename Key, typename Value>
Map<Key, Value>::~Map() {
    delete[] this->keys;
    delete[] this->values;
}

template <typename Key, typename Value>
bool Map<Key, Value>::empty() const {
    return this->keys->get_size() == 0;
}

template <typename Key, typename Value>
unsigned int Map<Key, Value>::size() const {
    return this->keys->get_size();
}

template <typename Key, typename Value>
bool Map<Key, Value>::find(const Key &key) {
    for (auto it = this->keys->cbegin(); it != this->keys->cend(); it++)
        if (*it == key)
            return true;

    return false;
}

template <typename Key, typename Value>
bool Map<Key, Value>::insert(const Pair<Key, Value> &pair) {
    if (this->find(pair.first) == false) {
        this->keys->push_back(pair.first);
        this->values->push_back(pair.second);

        return true;
    }

    return false;
}
