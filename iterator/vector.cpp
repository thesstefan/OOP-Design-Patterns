#include <iostream>

//#include "iterator.h"
#include "vector.h"

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
    delete[] buffer;
}

template <typename Item>
Item& Vector<Item>::operator[] (unsigned int index) {
    return buffer[index];
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

/*
template <typename Item>
void Vector<Item>::print(VectorIterator<Item> &iterator) {
    for (iterator.first(); iterator.is_done() != 0; iterator.next())
        std::cout << iterator.current_item() << std::endl;
}
*/
