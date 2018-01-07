#include "vector.h"
#include "pair.h"

template <typename Key, typename Value>
class Map {
    private:
        Vector<Key> *keys;
        Vector<Value> *values;

    public:
        /*
        class Iterator {
            private:
                Iterator(Key *key_buffer, Value *value_buffer);

                Iterator operator++();
                Iterator operator++(int);

                Value &operator*();
                Value *operator->();

                bool operator==(const Iterator &iterator);
                bool operator!=(const Iterator &iterator);
        };
        */

        Map();
        ~Map();

        bool empty() const;
        unsigned int size() const;

        bool find(const Key &key);
        bool insert(const Pair<Key, Value> &pair);
//        void erase(Iterator position);

//        unsigned int count(const Key &key) const;
//        Iterator find(const Key &key);
};
