#include <iostream>

#include "vector.h"
#include "pair.h"
#include "map.h"

int main() {
    Map<char, int> *map = new Map<char, int>();

    map->insert(Pair<char, int>('a', 10));
    map->insert(Pair<char, int>('b', 50));
    map->insert(Pair<char, int>('c', 30));
    map->insert(Pair<char, int>('d', 30));
    map->insert(Pair<char, int>('e', 30));
    map->insert(Pair<char, int>('f', 30));
    map->insert(Pair<char, int>('g', 30));
    map->insert(Pair<char, int>('h', 20));

    for (auto it = map->begin(); it != map->end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    return 0;
}

