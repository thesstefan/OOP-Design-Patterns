#include <iostream>

#include "vector.h"

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
Item& Vector<Item>::operator[](unsigned int index) {
    return this->buffer[index];
}

template <typename Item>
unsigned int Vector<Item>::get_capacity() const {
    return this->capacity;
}

template <typename Item>
unsigned int Vector<Item>::get_size() const {
    return this->size;
}

template <typename Item>
void Vector<Item>::reserve(int capacity, bool copy) {
    Item *new_buffer = new Item[capacity];

    if (new_buffer == nullptr) 
        std::cout << "Vector reserve() : memory allocation failure" << std::endl;

    if (copy)
        for (int index = 0; index < this->size; index++) {
            new_buffer[index] = this->buffer[index];

            if (this->buffer != nullptr)
                delete[] this->buffer;

            this->buffer = new_buffer;
            this->capacity = capacity;
        }
}

template <typename Item>
void Vector<Item>::push_back(const Item &item) {
    if (this->size == this->capacity) 
        if (this->capacity == 0)
            reserve(1, false);
        else
            reserve(this->capacity * 2, true);

        this->buffer[this->size++] = item;
}

template <typename Item>
Vector<Item>::Iterator::Iterator() {
    this->buffer = nullptr;
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
Vector<Item>::Iterator::Iterator(Item *buffer) {
    this->buffer = buffer;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator++() {
    Iterator iterator = *this;

    this->buffer++;

    return iterator;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::Iterator::operator++(int) {
    this->buffer++;

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
typename Vector<Item>::ConstIterator Vector<Item>::cbegin() {
    return Vector<Item>::ConstIterator(this->buffer);
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::cend() {
    return Vector<Item>::ConstIterator(this->buffer + this->size);
}

template <typename Item>
Vector<Item>::ConstIterator::ConstIterator(Item *buffer) {
    this->buffer = buffer;
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
