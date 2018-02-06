#ifndef VECTOR_
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 4

template <typename Item>
class Vector {
    protected:
        size_t size_;
        size_t capacity_;

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

                ptrdiff_t operator-(const Iterator &iterator);

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

                ptrdiff_t operator-(const ConstIterator &iterator);

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
        Vector(size_t count, Item &value);
        Vector(size_t count);

        template <typename IteratorType>
        Vector(IteratorType first, IteratorType last);

        Vector(const Vector &other);

        ~Vector();

        Vector& operator=(const Vector &other);
        void assign(size_t count, const Item &value);

        template <typename IteratorType>
        void assign(IteratorType first, IteratorType last);

        Item &operator[](size_t index);
        const Item& operator[](size_t index) const;

        Item& at(size_t index);
        const Item& at(size_t index) const;

        Item& front();
        const Item& front() const;

        Item& back();
        const Item& back() const;

        bool empty() const;

        size_t size() const;
        size_t capacity() const;

        Iterator begin();
        Iterator end();

        ConstIterator cbegin() const;
        ConstIterator cend() const;

        bool alloc_memory_if_needed();
        void reserve(int capacity, bool copy);

        Iterator find(const Item &item);

        void clear();

        Iterator insert(Iterator position, const Item &value);
        void insert(Iterator position, size_t count, const Item& value);

        template <typename IteratorType>
        void insert(Iterator position, IteratorType first, IteratorType last);

        Iterator erase(Iterator position);

        void push_back(const Item &item);
        void pop_back();

        void swap(Vector &other);
        void resize(size_t count, const Item &value);

        bool operator==(const Vector &other) const;
        bool operator!=(const Vector &other) const;
        bool operator<(const Vector &other) const;
        bool operator>(const Vector &other) const;
        bool operator>=(const Vector &other) const;
        bool operator<=(const Vector &other) const;
};

#endif
