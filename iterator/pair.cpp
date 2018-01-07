#include "pair.h"

template class Pair<int, int>;
template class Pair<char, int>;

template <typename Type_1, typename Type_2>
Pair<Type_1, Type_2>::Pair() {
    this->first = 0;
    this->second = 0;
}

template <typename Type_1, typename Type_2>
Pair<Type_1, Type_2>::Pair(const Type_1 &first, const Type_2 &second) {
    this->first = first;
    this->second = second;
}

template <typename Type_1, typename Type_2>
Pair<Type_1, Type_2>::Pair(const Pair<Type_1, Type_2> &pair) {
    this->first = pair.first;
    this->second = pair.second;
}

template <typename Type_1, typename Type_2>
bool Pair<Type_1, Type_2>::operator==(const Pair<Type_1, Type_2> &pair) {
    return this->first == pair.first && this->second == pair.second;
}
