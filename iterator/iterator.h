#ifndef ITERATOR_H
#define ITERATOR_H

#include "vector.h"

template <typename Item>
class Iterator {
    public:
        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool is_done() const = 0;
        virtual Item current_item() const = 0;
    protected:
        Iterator();
};

template <typename Item>
class VectorIterator : public Iterator<Item> {
    private:
        Vector<Item> *vector;
        int current;

    public:
        VectorIterator(Vector<Item> *vector);

        void first();
        void next();
        bool is_done() const;
        Item current_item() const;
};

#endif
