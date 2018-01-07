#ifndef PAIR_H
#define PAIR_H

template <typename Type_1, typename Type_2>
class Pair {
    public:
        Type_1 first;
        Type_2 second;

        Pair();
        Pair(const Type_1 &first, const Type_2 &second);
        Pair(const Pair<Type_1, Type_2> &pair);

        bool operator==(const Pair<Type_1, Type_2> &pair);
};

#endif 
