#include <iostream>

#include "exception.h"
#include "vector.h"

template <typename Item>
void print(Vector<Item> &vector) {
    std::cout << "Size : " << vector.get_size() << std::endl;
    std::cout << "Capacity : " << vector.get_capacity() << std::endl;

    for (auto it = vector.begin(); it != vector.end(); it += 1)
        std::cout << *it << " ";

    std::cout << std::endl;
}

int main() {
    Vector<int> vector;
    Vector<int> vector_2;

    vector.push_back(10);
    vector.push_back(20);

    vector_2.push_back(10);
    vector_2.push_back(30);

    std::cout << std::boolalpha;
    std::cout << (vector <= vector_2) << std::endl;

    return 0;
}
