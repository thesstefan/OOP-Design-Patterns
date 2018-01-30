#include "stack.h"

template class Stack<int>;

typedef unsigned int size_type;

template <typename Type, typename Container>
Stack<Type, Container>::Stack() {
    this->container = new Container();
}

template <typename Type, typename Container>
Stack<Type, Container>::Stack(const Stack& other) {
    delete this->container;

    this->container = other.container;
}

template <typename Type, typename Container>
Stack<Type, Container>::~Stack() {
    delete this->container;
}

template <typename Type, typename Container>
Stack<Type, Container>& Stack<Type, Container>::operator=(const Stack<Type, Container>& other) {
    delete this->container;

    this->container = other.container;

    return *this;
}

template <typename Type, typename Container>
bool Stack<Type, Container>::empty() const {
    return this->container->empty();
}

template <typename Type, typename Container>
size_type Stack<Type, Container>::size() const {
    return this->container->size();
}

template <typename Type, typename Container>
void Stack<Type, Container>::push(const Type& value) {
    this->container->push_back(value);
}

template <typename Type, typename Container>
void Stack<Type, Container>::pop() {
    this->container->pop_back();
}

template <typename Type, typename Container>
Type& Stack<Type, Container>::top() {
    return this->container->back();
}

template <typename Type, typename Container>
const Type& Stack<Type, Container>::top() const {
    return this->container->back();
}
