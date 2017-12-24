#include <iostream>

#include "iterator.h"
#include "vector.h"

int main() {
    Vector<int> *vector = new Vector<int>(10);
    VectorIterator<int> iterator = VectorIterator<int>(vector);

    vector->push_back(10);
    vector->push_back(21);

//    vector->print(iterator);

    return 0;
}
