#include "map.h"
#include "pair.h"
#include "vector.h"
#include "exception.h"

#include <iostream>

template class Map<char, int>;

template <typename Key, typename Value>
Map<Key, Value>::Map() {
    this->keys = new Vector<Key>();
    this->vals = new Vector<Value>();
}

template <typename Key, typename Value>
Map<Key, Value>::~Map() {
    delete this->keys;
    delete this->vals;
}

template <typename Key, typename Value>
Map<Key, Value>& Map<Key,Value>::operator=(const Map &other) {
    delete this->keys;
    delete this->vals;

    this->keys = other.keys;
    this->vals = other.vals;
}

template <typename Key, typename Value>
Value& Map<Key, Value>::at(const Key &key) {
    if (this->find(key) == this->end())
        throw OutOfRange("OutOfRange error in Map::at()");

    return this->find(key)->second;
}

template <typename Key, typename Value>
const Value& Map<Key, Value>::at(const Key &key) const {
    if (this->find(key) == this->cend())
        throw OutOfRange("OutOfRange error in Map:at() const");

    return this->find(key)->second;
}

template <typename Item, typename Iterator>
unsigned int get_index(Iterator start, Iterator end, Item to_find) {
    unsigned int index = 0;

    for (auto it = start; it != end; it++, index++)
        if (*it == to_find)
            return index;

#define NOT_FOUND -1
    return NOT_FOUND;
}

template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key &key) {
    unsigned int index = get_index(this->keys->begin(), this->keys->end(), key);

    if (index == NOT_FOUND) {
        this->insert(key, Value());

        unsigned int new_index = get_index(this->keys->begin(), this->keys->end(), key);

        return this->vals->operator[](new_index);
    } 

    return this->vals->operator[](index);
}

template <typename Key, typename Value>
bool Map<Key, Value>::empty() const {
    return this->cbegin() == this->cend();
}

template <typename Key, typename Value>
unsigned int Map<Key, Value>::size() const {
    return this->keys->get_size();
}

template <typename Key, typename Value>
void Map<Key, Value>::clear() {
    this->keys->clear();
    this->vals->clear();
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::find(const Key &key) const {
    auto it = this->cbegin();

    for ( ; it != this->cend() && it->first != key; it++);

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key,Value>::find(const Key &key) {
    auto it = this->begin();

    for ( ; it != this->end() && it->first != key; it++);
        
    return it;
}

template <typename Key, typename Value>
unsigned int Map<Key, Value>::count(const Key &key) const {
    int count = 0;

    for (auto it = this->cbegin(); it != this->cend(); it++) {
        if (it->first == key)
            count++;

        if (count > 1)
            throw Error("Error : Duplicate keys in Map found");
    }

    return count;
}

template <typename Key, typename Value>
Pair<typename Map<Key, Value>::Iterator, bool> Map<Key, Value>::insert(const Key &key, const Value &val) {
    if (this->find(key) == this->end()) {
        this->keys->push_back(key);
        this->vals->push_back(val);

        auto it = Map<Key, Value>::Iterator(this->keys->end() - 1, this->vals->end() - 1);

        return Pair<Map<Key, Value>::Iterator, bool>(it, true);
    }

    return Pair<Map<Key, Value>::Iterator, bool>(this->find(key), false);
}

/*
template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::erase(typename Map<Key, Value>::Iterator position) {
    auto key_erase_it = this->keys->erase(position.key_it);
    auto val_erase_it = this->vals->erase(position.val_it);

    return Map<Key, Value>::Iterator(key_erase_it, val_erase_it);
}
*/

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::begin() {
    return Map<Key, Value>::Iterator(this->keys->begin(), this->vals->begin());
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::end() {
    return Map<Key, Value>::Iterator(this->keys->end(), this->vals->end());
}

template <typename Key, typename Value>
Map<Key, Value>::Iterator::Iterator() {
    this->key_it = nullptr;
    this->val_it = nullptr;
}

template <typename Key, typename Value>
Map<Key, Value>::Iterator::Iterator(typename Vector<Key>::Iterator key_it, typename Vector<Value>::Iterator val_it) {
    this->key_it = key_it;
    this->val_it = val_it;
}

template <typename Key, typename Value>
Map<Key, Value>::Iterator::Iterator(const Map<Key, Value>::Iterator &iterator) {
    this->key_it = iterator.key_it;
    this->val_it = iterator.val_it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator& Map<Key, Value>::Iterator::operator=(const Iterator &iterator) {
    this->key_it = iterator.key_it;
    this->val_it = iterator.val_it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key,Value>::Iterator::operator++() {
    auto iterator = *this;

    this->key_it++;
    this->val_it++;

    return iterator;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::Iterator::operator++(int) {
    this->key_it++;
    this->val_it++;

    return *this;
};

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::Iterator::operator--() {
    auto iterator = *this;

    this->key_it--;
    this->val_it--;

    return iterator;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::Iterator::operator--(int) {
    this->key_it--;
    this->val_it--;

    return *this;
}

template <typename Key, typename Value>
Pair<Key, Value>* Map<Key, Value>::Iterator::operator->() {
    Pair<Key, Value> *pair = new Pair<Key, Value>(*(this->key_it), *(this->val_it));

    return pair;
}

template <typename Key, typename Value>
Pair<Key, Value>& Map<Key, Value>::Iterator::operator*() {
    Pair<Key, Value> *pair = new Pair<Key, Value>(*(this->key_it), *(this->val_it));
    
    return *pair;
}

template <typename Key, typename Value>
bool Map<Key, Value>::Iterator::operator==(const Iterator &iterator) const {
    return key_it == iterator.key_it && val_it == iterator.val_it;
}

template <typename Key, typename Value>
bool Map<Key, Value>::Iterator::operator!=(const Iterator &iterator) const {
    return key_it != iterator.key_it && val_it != iterator.val_it;
}

template <typename Key, typename Value>
Map<Key, Value>::ConstIterator::ConstIterator() {
    this->key_it = nullptr;
    this->val_it = nullptr;
}

template <typename Key, typename Value>
Map<Key, Value>::ConstIterator::ConstIterator(typename Vector<Key>::ConstIterator key_it, typename Vector<Value>::ConstIterator val_it) {
    this->key_it = key_it;
    this->val_it = val_it;
}

template <typename Key, typename Value>
Map<Key, Value>::ConstIterator::ConstIterator(const ConstIterator &iterator) {
    this->key_it = iterator.key_it;
    this->val_it = iterator.val_it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator& Map<Key, Value>::ConstIterator::operator=(const ConstIterator &iterator) {
    this->key_it = iterator.key_it;
    this->val_it = iterator.val_it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::cbegin() const {
    return Map<Key, Value>::ConstIterator(this->keys->cbegin(), this->vals->cbegin());
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::cend() const {
    return Map<Key, Value>::ConstIterator(this->keys->cend(), this->vals->cend());
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::ConstIterator::operator++() {
    auto iterator = *this;

    this->key_it++;
    this->val_it++;

    return iterator;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::ConstIterator::operator++(int) {
    this->key_it++;
    this->val_it++;

    return *this;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::ConstIterator::operator--() {
    auto iterator = *this;

    this->key_it--;
    this->val_it--;

    return iterator;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::ConstIterator::operator--(int) {
    this->key_it--;
    this->val_it--;

    return *this;
}

template <typename Key, typename Value>
const Pair<Key, Value>* Map<Key, Value>::ConstIterator::operator->() const {
    Pair<Key, Value> *pair = new Pair<Key, Value>(*(this->key_it), *(this->val_it));

    return pair;
}

template <typename Key, typename Value>
const Pair<Key, Value>& Map<Key, Value>::ConstIterator::operator*() const {
    Pair<Key, Value> *pair = new Pair<Key, Value>(*(this->key_it), *(this->val_it));
    
    return *pair;
}

template <typename Key, typename Value>
bool Map<Key, Value>::ConstIterator::operator==(const ConstIterator &iterator) const {
    return this->key_it == iterator.key_it && this->val_it == iterator.val_it;
}

template <typename Key, typename Value>
bool Map<Key, Value>::ConstIterator::operator!=(const ConstIterator &iterator) const {
    return this->key_it != iterator.key_it && this->val_it != iterator.val_it;
}
