#ifndef VECTOR_H
#define VECTOR_H

//#include "iterator.h"

template <typename Item>
class Vector {
    private:
        unsigned int size;
        unsigned int capacity;

        Item *buffer;

    public:
        Vector();
        Vector(unsigned int size);
        ~Vector();

        Item &operator[] (unsigned int index);

        unsigned int get_capacity() const;
        unsigned int get_size() const;

        void reserve(int capacity, bool copy);

        void push_back(const Item &item);

//        void print(VectorIterator<Item> &iterator);
};

#endif
