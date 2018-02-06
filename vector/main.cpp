#include <iostream>
#include <string>
#include <vector>
#include "vector.h"

template <typename Type>
std::ostream& operator<<(std::ostream& stream, const Vector<Type>& vector) {
    stream.put('[');

    char comma[3] = {'\0', ' ', '\0'};

    for (auto it = vector.cbegin(); it != vector.cend(); it++) {
        stream << comma << *it;

        comma[0] = ',';
    }

    return stream << ']';
}

template <typename Type>
void func(const Vector<Type>& vector) {
    std::cout << vector.back() << std::endl;
}

int main() {
    //TODO ERASE + INSERT
    Vector<int> vec;

    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);
    vec.insert(vec.begin(), 10);

    std::cout << vec << std::endl;

    return 0;
}
