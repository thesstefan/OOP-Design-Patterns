#include <iostream>

#include "vector.h"

int main() {
    Vector<int> *vector = new Vector<int>(10);

    vector->push_back(10);
    vector->push_back(14);
    vector->push_back(20);

    for (Vector<int>::Iterator it = vector->begin(); it != vector->end(); it++)
        std::cout << *it << std::endl;

    for (auto p : vector)
        std::cout << p << std::endl;

    return 0;
}

