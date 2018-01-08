#include "vector.h"
#include "pair.h"

template <typename Key, typename Value>
class Map {
    protected:
        Vector<Key> *keys;
        Vector<Value> *values;

    public:
        class Iterator {
            private:
                typename Vector<Key>::Iterator key_it;
                typename Vector<Value>::Iterator val_it;

            public:
                Iterator();
                Iterator(typename Vector<Key>::Iterator key_it, typename Vector<Value>::Iterator val_it);

                Iterator operator++();
                Iterator operator++(int);

                Pair<Key, Value> &operator*();
                Pair<Key, Value> *operator->();

                bool operator==(const Iterator &iterator);
                bool operator!=(const Iterator &iterator);
        };

        class ConstIterator {
            private:
                typename Vector<Key>::ConstIterator key_it;
                typename Vector<Value>::ConstIterator val_it;

            public:
                ConstIterator();
                ConstIterator(typename Vector<Key>::ConstIterator key_it, typename Vector<Value>::ConstIterator val_it);

                ConstIterator operator++();
                ConstIterator operator++(int);

                const Pair<Key, Value> &operator*();
                const Pair<Key, Value> *operator->();

                bool operator==(const ConstIterator &iterator);
                bool operator!=(const ConstIterator &iterator);
        };

        Iterator begin();
        Iterator end();

        ConstIterator cbegin();
        ConstIterator cend();

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
