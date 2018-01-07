#include <iostream>

#include "vector.h"
#include "pair.h"
#include "map.h"

int main() {
    Map<char, int> *map = new Map<char, int>();

    map->insert(Pair<char, int>('a', 10));
    map->insert(Pair<char, int>('b', 50));
    map->insert(Pair<char, int>('a', 30));
    map->insert(Pair<char, int>('c', 20));

    std::cout << map->size() << std::endl;

    return 0;
}

