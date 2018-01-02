#include <iostream>

#include "iterator.h"
#include "vector.h"

int main() {
    Vector<int> *vector = new Vector<int>(10);
    VectorIterator<int> *iterator = new VectorIterator<int>(vector);

    vector->push_back(10);
    vector->push_back(21);
    vector->push_back(14);
    vector->push_back(16);
    vector->push_back(19);
    vector->push_back(116);

    for (iterator->first(); iterator->is_done() != true; iterator->next())
        std::cout << iterator->current_item() << std::endl;

    return 0;
}
