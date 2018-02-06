#include <iostream>
#include <string>

#include "vector.h"

template class Vector<std::string>;
template class Vector<int>;
template class Vector<char>;

template Vector<int>::Vector<Vector<int>::Iterator>(Vector<int>::Iterator, Vector<int>::Iterator);
template void Vector<int>::assign<Vector<int>::Iterator>(Vector<int>::Iterator, Vector<int>::Iterator);
template void Vector<int>::insert<Vector<int>::Iterator>(Vector<int>::Iterator, Vector<int>::Iterator, Vector<int>::Iterator);

template <typename Item>
Vector<Item>::Vector() {
    this->capacity_ = 0;
    this->size_ = 0;
    this->buffer = nullptr;
}

template <typename Item>
Vector<Item>::Vector(size_t count, Item& value) {
    this->capacity_ = count;
    this->size_ = count;

    this->buffer = new Item[count];

    for (auto it = this->begin(); it != this->end(); it++)
        *it = value;
}

template <typename Item>
Vector<Item>::Vector(size_t count) {
    this->capacity_ = count;
    this->size_ = count;

    this->buffer = new Item[count];
}

template <typename Item> 
template <typename IteratorType> 
Vector<Item>::Vector(IteratorType first, IteratorType last) {
    ptrdiff_t count = last - first;

    this->size_ = count;
    this->capacity_ = count;

    this->buffer = new Item[count];

    for (auto it = this->begin(), it_ = first; it != this->end() && it_ != last; it++, it_++)
        *it = *it_;
}

template <typename Item>
Vector<Item>::Vector(const Vector<Item> &other) {
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;

    this->buffer = new Item[this->size_];

    for (auto it = this->begin(), it_ = other.cbegin(); it != this->end() && it_ != other.cend(); it++, it_++)
        *it = *it_;
}

template <typename Item>
Vector<Item>::~Vector() {
    delete[] this->buffer;
}

template <typename Item>
Vector<Item>& Vector<Item>::operator=(const Vector<Item> &other) {
    delete[] this->buffer;

    this->size_ = other.size_;
    this->capacity_ = other.capacity_;

    this->buffer = new Item[this->size_];

    for (auto it = this->begin(), it_ = other.cbegin(); it != this->end() && it_ != other.cend(); it++, it_++)
        *it = *it_;
}

template <typename Item>
void Vector<Item>::assign(size_t count, const Item& value) {
    this->clear();

    while (this->size_ < count)
        this->push_back(value);
}

template <typename Item>
template <typename IteratorType>
void Vector<Item>::assign(IteratorType first, IteratorType last) {
    this->clear();

    for (auto it = first; it != last; it++)
        this->push_back(*it);
}

template <typename Item>
Item& Vector<Item>::at(size_t index) {
    if (index < 0 || index >= this->size_)
        throw std::out_of_range("Index is out of range in Vector::at(size_t index)");

    return this->buffer[index];
}

template <typename Item>
const Item& Vector<Item>::at(size_t index) const {
    if (index < 0 || index >= this->size_)
        throw std::out_of_range("Index is out of range in Vector::at(size_t index)");

    return this->buffer[index];
}

template <typename Item>
Item& Vector<Item>::operator[](size_t index) {
    return this->buffer[index];
}

template <typename Item>
const Item& Vector<Item>::operator[](size_t index) const {
    return this->buffer[index];
}

template <typename Item>
Item& Vector<Item>::front() {
    return *this->begin();
}

template <typename Item>
const Item& Vector<Item>::front() const {
    return *this->cbegin();
}

template <typename Item>
Item& Vector<Item>::back() {
    return *(this->end() - 1);
}

template <typename Item>
const Item& Vector<Item>::back() const {
    return *(this->cend() - 1);
}

template <typename Item>
bool Vector<Item>::empty() const {
    return this->cbegin() == this->cend();
}

template <typename Item>
size_t Vector<Item>::size() const {
    return this->size_;
}

template <typename Item>
size_t Vector<Item>::capacity() const {
    return this->capacity_;
}

template <typename Item>
void Vector<Item>::reserve(int capacity, bool copy) {
    Item *new_buffer = new Item[capacity];
    this->capacity_ = capacity;

    if (new_buffer == nullptr) 
        throw std::bad_alloc();

    if (copy) {
        for (int index = 0; index < this->size_; index++)
            new_buffer[index] = this->buffer[index];

        if (this->buffer != nullptr)
            delete[] this->buffer;
    }

    this->buffer = new_buffer;
    this->capacity_ = capacity;
}


template <typename Item>
bool Vector<Item>::alloc_memory_if_needed()  {
    if (this->size_ == this->capacity_) {
        if (this->capacity_ == 0)
            reserve(1, false);
        else
            reserve(this->capacity_ * 2, true);

        return true;
    }

    return false;
}

template <typename Item>
void Vector<Item>::clear() {
    delete[] this->buffer;
    this->size_ = 0;

    this->buffer = new Item[this->capacity_];
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::insert(typename Vector<Item>::Iterator position, const Item& value) {
    if (this->empty()) {
        this->push_back(value);

        return this->begin();
    }

    this->size_++;
    this->alloc_memory_if_needed();

    for (auto it = this->end() - 1; it != position; it--) {
        *it = *(it - 1);
    }

    *position = value;
        std::cout << "INSERTED : " << *position << std::endl;

    return position;
}

template <typename Item>
void Vector<Item>::insert(typename Vector<Item>::Iterator position, size_t count, const Item& value) {
    while (count) {
        if (this->empty() && position == nullptr)
            position = this->insert(position, value);
        else
            this->insert(position, value);

        count--;
    }
}

template <typename Item>
template <typename IteratorType>
void Vector<Item>::insert(typename Vector<Item>::Iterator position, IteratorType first, IteratorType last) {
    for (auto it = first; it != last; it++)
        position = this->insert(position, *it);
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::erase(typename Vector<Item>::Iterator position) {
    for (auto it = position; it != this->end() - 1; it++)
        *it = *(it + 1);

    this->size_--;

    return position;
}

template <typename Item>
void Vector<Item>::push_back(const Item &item) {
    this->alloc_memory_if_needed();

    this->buffer[this->size_++] = item;
}

template <typename Item>
void Vector<Item>::pop_back() {
    this->alloc_memory_if_needed();

    if (this->size_ != 0)
        this->size_--;
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
    swap_(this->size_, other.size_);
    swap_(this->capacity_, other.capacity_);
}

template <typename Item>
void Vector<Item>::resize(size_t count, const Item &value) {
    while (count != this->size_) {
        if (count > this->size_) 
            this->push_back(value);
        else
            this->pop_back();
    }
}

template <typename Item>
bool Vector<Item>::operator==(const Vector &other) const {
    if (this->size_ != other.size_)
        return false;

    for (auto it = this->cbegin(), other_it = other.cbegin(); it != this->cend() && other_it != this->cend(); it++, other_it++)
       if (*it != *other_it)
          return false;

   return true;
} 

template <typename Item>
bool Vector<Item>::operator!=(const Vector &other) const {
    if (*this == other)
        return false;

    return true;
}

template <typename Item>
int Vector<Item>::Compare::execute(typename Vector<Item>::ConstIterator first_1, typename Vector<Item>::ConstIterator end_1, typename Vector<Item>::ConstIterator first_2, typename Vector<Item>::ConstIterator end_2) {
    auto it_1 = first_1;
    auto it_2 = first_2;

    for ( ; it_1 != end_1 && it_2 != end_2; it_1++, it_2++) {
        std::cout << *it_1 << " " << *it_2 << std::endl;

        if (*it_1 < *it_2)
            return -1;
        else if (*it_1 > *it_2)
            return 1;
    }

    if (it_1 == end_1 && it_2 != end_2)
        return -1;
    else if (it_1 != end_1 && it_2 == end_2)
        return 1;

    return 0;
}

template <typename Item>
bool Vector<Item>::operator<(const Vector &other) const {
    if (Compare().execute(this->cbegin(), this->cend(), other.cbegin(), other.cend()) < 0)
        return true;

    return false;
}

template <typename Item>
bool Vector<Item>::operator>(const Vector &other) const {
    if (Compare().execute(this->cbegin(), this->cend(), other.cbegin(), other.cend()) > 0)
        return true;

    return false;
}

template <typename Item>
bool Vector<Item>::operator<=(const Vector &other) const {
    if (Compare().execute(this->cbegin(), this->cend(), other.cbegin(), other.cend()) <= 0)
        return true;

    return false;
}

template <typename Item>
bool Vector<Item>::operator>=(const Vector &other) const {
    if (Compare().execute(this->cbegin(), this->cend(), other.cbegin(), other.cend()) >= 0)
        return true;

    return false;
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
    return Vector<Item>::Iterator(this->buffer + this->size_);
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
ptrdiff_t Vector<Item>::Iterator::operator-(const typename Vector<Item>::Iterator& iterator) {
    return this->buffer - iterator.buffer;
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
bool Vector<Item>::Iterator::operator==(const Iterator &iterator) const {
    return buffer == iterator.buffer;
}

template <typename Item>
bool Vector<Item>::Iterator::operator!=(const Iterator &iterator) const {
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
typename Vector<Item>::ConstIterator Vector<Item>::cbegin() const {
    return Vector<Item>::ConstIterator(this->buffer);
}

template <typename Item>
typename Vector<Item>::ConstIterator Vector<Item>::cend() const {
    return Vector<Item>::ConstIterator(this->buffer + this->size_);
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
ptrdiff_t Vector<Item>::ConstIterator::operator-(const typename Vector<Item>::ConstIterator& iterator) {
    return this->buffer - iterator.buffer;
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
const Item& Vector<Item>::ConstIterator::operator*() const {
    return *buffer;
}

template <typename Item>
const Item* Vector<Item>::ConstIterator::operator->() const {
    return buffer;
}

template <typename Item>
bool Vector<Item>::ConstIterator::operator==(const ConstIterator &iterator) const {
    return buffer == iterator.buffer;
}

template <typename Item>
bool Vector<Item>::ConstIterator::operator!=(const ConstIterator &iterator) const {
    return buffer != iterator.buffer;
}

template <typename Item>
typename Vector<Item>::Iterator Vector<Item>::find(const Item &item) {
    auto it = this->begin();

    for ( ; it != this->end() && *it != item; it++)

    return it;
}
