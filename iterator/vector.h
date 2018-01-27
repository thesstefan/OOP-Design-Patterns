#ifndef VECTOR_H
#define VECTOR_H

template <typename Item>
class Vector {
    typedef unsigned int size_type;

    protected:
        size_type size;
        size_type capacity;

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

                bool operator==(const Iterator &iterator) const;
                bool operator!=(const Iterator &iterator) const;
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

                const Item &operator*() const;
                const Item *operator->() const;

                bool operator==(const ConstIterator &iterator) const;
                bool operator!=(const ConstIterator &iterator) const;
        };

        class Compare {
            public:
                int execute(ConstIterator first_1, ConstIterator end_1, ConstIterator first_2, ConstIterator end_2);
        };

        Vector();
        Vector(size_type size);
        ~Vector();

        Vector& operator=(const Vector &other);
        void assign(size_type count, const Item &value);

        Item &operator[] (size_type index);
        Item& at(size_type index);

        Item& front();
        Item& back();

        bool empty() const;

        size_type get_size() const;
        size_type get_capacity() const;

        Iterator begin();
        Iterator end();

        ConstIterator cbegin() const;
        ConstIterator cend() const;

        bool alloc_memory_if_needed();
        void reserve(int capacity, bool copy);

        Iterator find(const Item &item);

        void clear();

        Iterator insert(Iterator position, const Item &value);
        Iterator erase(Iterator position);

        void push_back(const Item &item);
        void pop_back();

        void swap(Vector &other);
        void resize(size_type count, const Item &value);

        bool operator==(const Vector &other) const;
        bool operator!=(const Vector &other) const;
        bool operator<(const Vector &other) const;
        bool operator>(const Vector &other) const;
        bool operator>=(const Vector &other) const;
        bool operator<=(const Vector &other) const;
};

#endif
