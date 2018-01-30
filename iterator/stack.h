#include "vector.h"

typedef unsigned int size_type;

template <typename Type, typename Container = Vector<Type>>
class Stack {
    private:
        Container *container;

    public:
        Stack();
        Stack(const Stack& other);

        ~Stack();

        Stack& operator=(const Stack<Type, Container>& other);

        bool empty() const;
        size_type size() const;

        void push(const Type& value);
        void pop();

        Type& top();
        const Type& top() const;
};
