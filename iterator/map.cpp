#include "map.h"
#include "pair.h"
#include "vector.h"
#include "exception.h"

template class Map<char, int>;

template <typename Key, typename Value>
Map<Key, Value>::Map() {
    this->keys = new Vector<Key>();
    this->values = new Vector<Value>();
}

template <typename Key, typename Value>
Map<Key, Value>::~Map() {
    delete this->keys;
    delete this->values;
}

template <typename Key, typename Value>
Map<Key, Value>& Map<Key,Value>::operator=(const Map &other) {
    delete this->keys;
    delete this->values;

    this->keys = other.keys;
    this->values = other.values;
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

template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key &key) {
    if (this->find(key) == this->end()); 
        return this->insert(Pair<Key, Value>(key, Value())).first->second;

    return this->find(key)->second;
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
    this->values->clear();
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::find(const Key &key) const {
    int count = 0;
    auto it = this->keys->cbegin();

    for ( ; it != this->keys->cend() && *it != key; it++)
        count++;

    return Map<Key, Value>::ConstIterator(it, this->values->cbegin() + count);
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key,Value>::find(const Key &key) {
    int count = 0;
    auto it = this->keys->begin();

    for ( ; it != this->keys->end() && *it != key; it++)
        count++;

    return Map<Key, Value>::Iterator(it, this->values->begin() + count);
}

template <typename Key, typename Value>
unsigned int Map<Key, Value>::count(const Key &key) const {
    int count = 0;

    for (auto it = this->lower_bound(key); it != this->cend(); it++) {
        if (it->first == key)
            count++;

        if (count > 1)
            throw Error("Error : Duplicate keys in Map found");
    }

    return count;
}

template <typename Key, typename Value>
bool Map<Key, Value>::Compare::comp(const Key &first, const Key &second) const {
    if (first < second)
        return true;

    return false;
}

template <typename Key, typename Value>
bool Map<Key, Value>::Compare::equiv(const Key &first, const Key &second) const {
    if (!comp(first, second) && !comp(second, first))
        return true;

    return false;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::lower_bound(const Key &key) {
    auto it = this->begin();

    for ( ; it != this->end() && Compare().comp(it->first, key); it++);

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::lower_bound(const Key &key) const {
    auto it = this->cbegin();

    for ( ; it != this->cend() && Compare().comp(it->first, key); it++);

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::upper_bound(const Key &key) {
    auto it = this->begin();

    for ( ; it != this->end() && (Compare().comp(it->first, key) || Compare().equiv(it->first, key)); it++);

    return it;
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::upper_bound(const Key &key) const {
    auto it = this->cbegin();

    for ( ; it != this->cend() && (Compare().comp(it->first, key) || Compare().equiv(it->first, key)); it++);

    return it;
}

template <typename Key, typename Value>
Pair<typename Map<Key, Value>::Iterator, bool> Map<Key, Value>::insert(const Pair<Key, Value> &pair) {
    if (this->find(pair.first) == this->end()) {
        auto it = this->keys->begin();
        int position = 0;

        for ( ; it != this->keys->end() && Compare().comp(pair.first, *it) != true; it++)
            position++;

        auto insert_key_it = this->keys->insert(it, pair.first);
        auto insert_val_it = this->values->insert(this->values->begin() + position, pair.second);

        return Pair<Map<Key, Value>::Iterator, bool>(Map<Key, Value>::Iterator(insert_key_it, insert_val_it), true);
    }

    return Pair<Map<Key, Value>::Iterator, bool>(this->find(pair.first), false);
}

template <typename Key, typename Value>
void Map<Key, Value>::erase(typename Map<Key, Value>::Iterator position) {
     
}

template <typename Key, typename Value>
unsigned int Map<Key, Value>::erase(const Key &key) {
    int count;

    while (this->find(key) != this->end()) {
        int position = 0;

        for (auto it = this->keys->begin(); it != this->keys->end() && *it != key; it++)
            position++;

        if (*it == key) {
            this->keys->erase(it);
            this->values->erase(this->values->begin() + position);

            count++:
        }
    }

    return count;
}

template <typename Key, typename Value>
void Map<Key, Value>::swap(Map<Key, Value> &other) {
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::begin() {
    return Map<Key, Value>::Iterator(this->keys->begin(), this->values->begin());
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::end() {
    return Map<Key, Value>::Iterator(this->keys->end(), this->values->end());
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
    return Map<Key, Value>::ConstIterator(this->keys->cbegin(), this->values->cbegin());
}

template <typename Key, typename Value>
typename Map<Key, Value>::ConstIterator Map<Key, Value>::cend() const {
    return Map<Key, Value>::ConstIterator(this->keys->cend(), this->values->cend());
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
