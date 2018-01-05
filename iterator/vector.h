#ifndef VECTOR_H
#define VECTOR_H

template <typename Item>
class Vector {
    protected:
        unsigned int size;
        unsigned int capacity;

        Item *buffer;

    public:
        class Iterator {
            private:
                Item *buffer;

            public:
                Iterator(Item *buffer);

                Iterator operator++();
                Iterator operator++(int x);

                Item &operator*();
                Item *operator->();

                bool operator==(const Iterator &iterator);
                bool operator!=(const Iterator &iterator);
        };

        class ConstIterator {
            private:
                Item *buffer;

            public:
                ConstIterator(Item *buffer);

                ConstIterator operator++();
                ConstIterator operator++(int);

                const Item &operator*();
                const Item *operator->();

                bool operator==(const ConstIterator &iterator);
                bool operator!=(const ConstIterator &iterator);
        };


        Vector();
        Vector(unsigned int size);
        ~Vector();

        Item &operator[] (unsigned int index);

        Iterator begin();
        Iterator end();

        ConstIterator cbegin();
        ConstIterator cend();

        unsigned int get_capacity() const;
        unsigned int get_size() const;

        void reserve(int capacity, bool copy);

        void push_back(const Item &item);

//        void print(VectorIterator<Item> &iterator);
};

#endif
