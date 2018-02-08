#pragma once

#include "key_tree.h"
#include "pair.h"

template <typename Key, typename Value>
class Map {
    typedef typename KeyTree<Key, Value>::Iterator Iterator;
    typedef typename KeyTree<Key, Value>::ConstIterator ConstIterator;

    private:
        KeyTree<Key, Value> data;

    public:
        Map();
        Map(const Map& other);

        template <typename IteratorType>
        Map(IteratorType first, IteratorType last);

        ~Map();

        Map& operator=(const Map &other); 

        Value& at(const Key& key);
        const Value& at(const Key& key) const;

        Value& operator[](const Key& key);

        Iterator begin();
        Iterator end();

        ConstIterator cbegin() const;
        ConstIterator cend() const;

        bool empty() const;
        size_t size() const;

        void clear();

        Iterator insert(const Pair<Key, Value>& pair);
        Iterator insert(const Key& key, const Value& value);

        template <typename IteratorType>
        void insert(IteratorType first, IteratorType last);

        void erase(Iterator position);
        size_t erase(const Key& key);

        template <typename IteratorType>
        void erase(IteratorType first, IteratorType last);

        void swap(const Map<Key, Value>& other);

        size_t count (const Key &key) const;

        Iterator find(const Key &key);
        ConstIterator find(const Key &key) const;

        Iterator lower_bound(const Key &key);
        ConstIterator lower_bound(const Key &key) const;

        Iterator upper_bound(const Key &key);
        ConstIterator upper_bound(const Key &key) const;

        Pair<Iterator, Iterator> equal_range(const Key &key);
        Pair<ConstIterator, ConstIterator> equal_range(const Key &key) const;
};

template <typename Key, typename Value>
Map<Key, Value>::Map() {
    this->data = KeyTree<Key, Value>();
}

template <typename Key, typename Value>
template <typename IteratorType>
Map<Key, Value>::Map(IteratorType first, IteratorType last) {
    this->data = KeyTree<Key, Value>();

    for (auto it = first; it != last; it++)
        this->data.insert(*it);
}

template <typename Key, typename Value>
Map<Key, Value>::Map(const Map& other) {
    this->data = other.data;
}

template <typename Key, typename Value>
Map<Key, Value>::~Map() {}

template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(const Map& other) {
    this->data = other.data;
}

template <typename Key, typename Value>
Value& Map<Key, Value>::at(const Key &key) {
    auto result = this->data.search(key);

    if (result == nullptr)
        throw std::out_of_range("Key is not present in Map (Map::at(const KeyType &key))");

    return result->value;
}

template <typename Key, typename Value>
const Value& Map<Key, Value>::at(const Key &key) const {
    auto result = this->data.search(key);

    if (result == nullptr)
        throw std::out_of_range("Key is not present in Map (Map::at(const KeyType &key))");

    return result->value;
}

template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key &key) {
    return (this->data.search(key))->value;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::begin() {
    return this->data.begin();
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::end() {
    return this->data.end();
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::cbegin() const {
    return this->data.cbegin();
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::cend() const {
    return this->data.cend();
}

template <typename Key, typename Value>
bool Map<Key, Value>::empty() const {
    return this->data.begin() == this->data.end();
}

template <typename IteratorType>
ptrdiff_t distance(IteratorType first, IteratorType second) {
    ptrdiff_t distance = 0;

    for (auto it = first; it != second; it++, distance++);

    return ++distance;
}

template <typename Key, typename Value>
size_t Map<Key, Value>::size() const {
    return distance(this->data.cbegin(), this->data.cend());
}

template <typename Key, typename Value>
void Map<Key, Value>::clear() {
    for (auto it = this->data.begin(); it != this->data.end(); it++)
        this->data.erase(it->key);
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::insert(const Pair<Key, Value>& pair) {
    this->data.insert(pair->first, pair->second);

    return Map<Key, Value>::Iterator(this->data.search(pair->first), this->data.max());
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::insert(const Key& key, const Value& value) {
    this->data.insert(key, value);

    return Map<Key, Value>::Iterator(this->data.search(key), this->data.max());
}

template <typename Key, typename Value>
template <typename IteratorType>
void Map<Key, Value>::insert(IteratorType first, IteratorType last) {
    for (auto it = first; it != last; it++)
        this->data.insert(*it);
}

template <typename Key, typename Value>
void Map<Key, Value>::erase(typename Map<Key, Value>::Iterator position) {
    this->data.erase(position->key);
}

template <typename Key, typename Value>
template <typename IteratorType>
void Map<Key, Value>::erase(IteratorType first, IteratorType last) {
    for (auto it = first; it != last; it++)
        this->data.erase(it->key);
}

template <typename Key, typename Value>
size_t Map<Key, Value>::erase(const Key &key) {
    size_t count = 0;

    while (this->data.search(key) != nullptr) {
        this->data.erase(key);

        count++;
    }

    return count;
}

template <typename Key, typename Value>
void Map<Key, Value>::swap(const Map<Key, Value>& other) {
    auto temp = this->data;

    this->data = other.data;

    other.data = temp;
}

template <typename Key, typename Value>
size_t Map<Key, Value>::count(const Key &key) const {
    return (this->data->search(key) != nullptr) ? 1 : 0;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::find(const Key &key) {
    return Map<Key, Value>::Iterator(this->data.search(key), this->data.max());
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::find(const Key &key) const {
    return Map<Key, Value>::ConstIterator(this->data.search(key), this->data.max());
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::lower_bound(const Key &key) {
    auto it = this->begin();

    for ( ; it != this->end() && !(key > it->key) ; it++)

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::lower_bound(const Key &key) const {
    auto it = this->cbegin();

    for ( ; it != this->cend() && !(key > it->key) ; it++)

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::upper_bound(const Key &key) {
    auto it = this->begin();

    for ( ; it != this->end() && key >= it->key ; it++)

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::upper_bound(const Key &key) const {
    auto it = this->cbegin();

    for ( ; it != this->cend() && key >= it->key ; it++)

    return it;
}

template <typename Key, typename Value>
Pair<typename Map<Key, Value>::Iterator, typename Map<Key, Value>::Iterator> Map<Key, Value>::equal_range(const Key &key) {
    return Pair<typename Map<Key, Value>::Iterator, typename Map<Key, Value>::Iterator>(this->lower_bound(key), this->upper_bound(key));
}

template <typename Key, typename Value>
Pair<typename Map<Key, Value>::ConstIterator, typename Map<Key, Value>::ConstIterator> Map<Key, Value>::equal_range(const Key &key) const {
    return Pair<typename Map<Key, Value>::ConstIterator, typename Map<Key, Value>::ConstIterator>(this->lower_bound(key), this->upper_bound(key));
}
