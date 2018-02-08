#include <iostream>

#include "vector.h"
#include "stack.h"
#include "tree.h"
#include "key_tree.h"
#include "misc.h"
#include "pair.h"
#include "map.h"

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& stream, const Map<Key, Value>& map) {
    for (auto it = map.cbegin(); it != map.cend(); it++) {
        stream << '[';

        stream << it->key;

        stream << ", " << it->value;

        stream << ']' << std::endl;
    }

    return stream;
}

int main() {
    Map<char, int> map;

    map.insert('a', 10);
    map.insert('b', 20);
    map.insert('c', 30);

    std::cout << map;

    return 0;
}

