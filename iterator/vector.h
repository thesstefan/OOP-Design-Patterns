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
                Iterator();
                Iterator(Item *buffer);
                Iterator(const Iterator &iterator);

                Iterator& operator=(const Iterator &iterator);

                Iterator operator++();
                Iterator operator++(int x);

                Iterator operator--();
                Iterator operator--(int x);

                Iterator operator+(int x);
                Iterator operator-(int x);

                Iterator operator+=(int x);
                Iterator operator-=(int x);

                Item &operator*();
                Item *operator->();

                bool operator==(const Iterator &iterator);
                bool operator!=(const Iterator &iterator);
        };

        class ConstIterator {
            private:
                Item *buffer;

            public:
                ConstIterator();
                ConstIterator(Item *buffer);
                ConstIterator(const ConstIterator &iterator);

                ConstIterator& operator=(const ConstIterator &iterator);

                ConstIterator operator++();
                ConstIterator operator++(int);

                ConstIterator operator--();
                ConstIterator operator--(int x);

                ConstIterator operator+(int x);
                ConstIterator operator-(int x);

                ConstIterator operator+=(int x);
                ConstIterator operator-=(int x);

                const Item &operator*();
                const Item *operator->();

                bool operator==(const ConstIterator &iterator);
                bool operator!=(const ConstIterator &iterator);
        };


        Vector();
        Vector(unsigned int size);
        ~Vector();

        Vector &operator=(const Vector &other);
        void assign(unsigned int count, const Item &value);

        Item &operator[] (unsigned int index);
        Item& at(unsigned int index);

        Item& front();
        Item& back();

        bool empty() const;

        unsigned int get_size() const;
        unsigned int get_capacity() const;

        Iterator begin();
        Iterator end();

        ConstIterator cbegin();
        ConstIterator cend();

        bool alloc_memory_if_needed();
        void reserve(int capacity, bool copy);

        void clear();

        Iterator insert(Iterator position, const Item &value);
        Iterator erase(Iterator position);

        void push_back(const Item &item);
        void pop_back();

        void swap(Vector &other);
        void resize(unsigned int count, const Item &value);
};

#endif
