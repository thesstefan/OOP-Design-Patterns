#include <iostream>

#include "vector.h"
#include "iterator.h"

template <typename Item>
VectorIterator<Item>::VectorIterator(Vector<Item> *vector) {
    this->vector = vector;
}

template <typename Item>
void VectorIterator<Item>::first() {
    this->current = 0;
}

template <typename Item>
void VectorIterator<Item>::next() {
    this->current++;
}

template <typename Item>
bool VectorIterator<Item>::is_done() const {
    return this->current >= this->vector->get_size();
}

template <typename Item>
Item VectorIterator<Item>::current_item() const {
    if (this->is_done())
        std::cout << "Iterator is out of bounds" << std::endl;

    return this->vector[this->current];
}
