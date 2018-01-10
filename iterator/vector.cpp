#include <iostream>

#include "vector.h"
#include "exception.h"

template class Vector<int>;
template class Vector<char>;

template <typename Item>
Vector<Item>::Vector() {
    this->capacity = 0;
    this->size = 0;
    this->buffer = new Item[0];
}

template <typename Item>
Vector<Item>::Vector(unsigned int size) {
    this->capacity = size;
    this->size = 0;
    this->buffer = new Item[size];
}

template <typename Item>
Vector<Item>::~Vector() {
    delete[] this->buffer;
}

template <typename Item>
Vector<Item>& Vector<Item>::operator=(const Vector<Item> &other) {
    delete[] this->buffer;

    this->buffer = other.buffer;
    this->size = other.size;
    this->capacity = other.capacity;
}

template <typename Item>
void Vector<Item>::assign(unsigned int count, const Item& value) {
    this->clear();

    while (this->size < count)
        this->push_back(value);
}
template <typename Item>
Item& Vector<Item>::at(unsigned int index) {
    if (index < 0 || index > this->size)
        throw OutOfRange("OutOfRange error in Vector::at()");

    return this->buffer[index];
}

template <typename Item>
Item& Vector<Item>::operator[](unsigned int index) {
    return this->buffer[index];
}

template <typename Item>
Item& Vector<Item>::front() {
    return this->buffer[0];
}

template <typename Item>
Item& Vector<Item>::back() {
    return this->buffer[this->size - 1];
}

template <typename Item>
bool Vector<Item>::empty() const {
    return this->size == 0;
}

template <typename Item>
unsigned int Vector<Item>::get_size() const {
    return this->size;
}

template <typename Item>
unsigned int Vector<Item>::get_capacity() const {
    return this->capacity;
}

template <typename Item>
void Vector<Item>::reserve(int capacity, bool copy) {
    Item *new_buffer = new Item[capacity];
    this->capacity = capacity;

    if (new_buffer == nullptr) 
        throw BadAlloc("Memory allocation error in Vector::reserve()");

    if (copy) {
        for (int index = 0; index < this->size; index++)
            new_buffer[index] = this->buffer[index];

        if (this->buffer != nullptr)
            delete[] this->buffer;
    }

    this->buffer = new_buffer;
    this->capacity = capacity;
}


template <typename Item>
bool Vector<Item>::alloc_memory_if_needed()  {
    if (this->size == this->capacity) {
        if (this->capacity == 0)
            reserve(1, false);
        else
            reserve(this->capacity * 2, true);

        return true;
    }

    return false;
}

template <typename Item>
void Vector<Item>::clear() {
    delete[] this->buffer;
    this->size = 0;

    this->buffer = new Item[this->capacity];
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::insert(typename Vector<Item>::Iterator position, const Item& value) {
    this->alloc_memory_if_needed();

    int copy = *position;
    *position = value;

    this->size++;

    for (auto it = position + 1; it != this->end(); it++) {
        int new_copy = *it;

        *it = copy;

        copy = new_copy;
    }

    return position;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::erase(typename Vector<Item>::Iterator position) {
    for (auto it = position; it != this->end() - 1; it++)
        *it = *(it + 1);

    this->size--;

    return position;
}

template <typename Item>
void Vector<Item>::push_back(const Item &item) {
    this->alloc_memory_if_needed();

    this->buffer[this->size++] = item;
}

template <typename Item>
void Vector<Item>::pop_back() {
    this->alloc_memory_if_needed();

    this->size--;
}

template <typename Item>
void swap_(Item &item_1, Item &item_2) {
    Item temp;

    temp = item_1;
    item_1 = item_2;
    item_2 = temp;
}

template <typename Item>
void Vector<Item>::swap(Vector<Item> &other) {
    swap_(this->buffer, other.buffer);
    swap_(this->size, other.size);
    swap_(this->capacity, other.capacity);
}

template <typename Item>
void Vector<Item>::resize(unsigned int count, const Item &value) {
    while (count != this->size) {
        if (count > this->size) 
            this->push_back(value);
        else
            this->pop_back();
    }
}
        
template <typename Item>
Vector<Item>::Iterator::Iterator() {
    this->buffer = nullptr;
}

template <typename Item>
Vector<Item>::Iterator::Iterator(Item *buffer) {
    this->buffer = buffer;
}

template <typename Item>
Vector<Item>::Iterator::Iterator(const Vector<Item>::Iterator &iterator) {
    this->buffer = iterator.buffer;
}

template <typename Item>
typename Vector<Item>::Iterator& Vector<Item>::Iterator::operator=(const Vector<Item>::Iterator &iterator) {
    this->buffer = iterator.buffer;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::begin() {
    return Vector<Item>::Iterator(this->buffer);
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::end() {
    return Vector<Item>::Iterator(this->buffer + this->size);
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator++() {
    auto iterator = *this;

    this->buffer++;

    return iterator;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator++(int) {
    this->buffer++;

    return *this;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator--() {
    auto iterator = *this;

    this->buffer--;

    return iterator;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator--(int) {
    this->buffer--;

    return *this;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator+(int x) {
    auto iterator = *this;

    iterator.buffer += x;

    return iterator;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator-(int x) {
    auto iterator = *this;

    iterator.buffer -= x;

    return iterator;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator+=(int x) {
    this->buffer += x;

    return *this;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator-=(int x) {
    this->buffer -= x;

    return *this;
}

template <typename Item>
Item& Vector<Item>::Iterator::operator*() {
    return *buffer;
}

template <typename Item>
Item* Vector<Item>::Iterator::operator->() {
    return buffer;
}

template <typename Item>
bool Vector<Item>::Iterator::operator==(const Iterator &iterator) {
    return buffer == iterator.buffer;
}

template <typename Item>
bool Vector<Item>::Iterator::operator!=(const Iterator &iterator) {
    return buffer != iterator.buffer;
}

template <typename Item>
Vector<Item>::ConstIterator::ConstIterator() {
    this->buffer = nullptr;
}

template <typename Item>
Vector<Item>::ConstIterator::ConstIterator(Item *buffer) {
    this->buffer = buffer;
}

template <typename Item>
Vector<Item>::ConstIterator::ConstIterator(const Vector<Item>::ConstIterator &iterator) {
    this->buffer = iterator.buffer;
}

template <typename Item>
typename Vector<Item>::ConstIterator& Vector<Item>::ConstIterator::operator=(const Vector<Item>::ConstIterator &iterator) {
    this->buffer = iterator.buffer;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::cbegin() {
    return Vector<Item>::ConstIterator(this->buffer);
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::cend() {
    return Vector<Item>::ConstIterator(this->buffer + this->size);
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator++() {
    ConstIterator iterator = *this;

    this->buffer++;

    return iterator;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator++(int) {
    this->buffer++;

    return *this;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator--() {
    auto iterator = *this;

    this->buffer--;

    return iterator;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator--(int) {
    this->buffer--;

    return *this;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator+(int x) {
    auto iterator = *this;

    iterator.buffer += x;

    return iterator;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator-(int x) {
    auto iterator = *this;

    iterator.buffer -= x;

    return iterator;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator+=(int x) {
    this->buffer += x;

    return *this;
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::ConstIterator::operator-=(int x) {
    this->buffer -= x;

    return *this;
}

template <typename Item>
const Item& Vector<Item>::ConstIterator::operator*() {
    return *buffer;
}

template <typename Item>
const Item* Vector<Item>::ConstIterator::operator->() {
    return buffer;
}

template <typename Item>
bool Vector<Item>::ConstIterator::operator==(const ConstIterator &iterator) {
    return buffer == iterator.buffer;
}

template <typename Item>
bool Vector<Item>::ConstIterator::operator!=(const ConstIterator &iterator) {
    return buffer != iterator.buffer;
}
