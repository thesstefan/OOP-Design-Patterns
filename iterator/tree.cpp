#include <iostream>

#include "tree.h"

template class Tree<int>;

template <typename Type>
Tree<Type>::Node::Node(Type value) {
    this->value = value;

    this->left = nullptr;
    this->right = nullptr;
}

template <typename Type>
Tree<Type>::Tree() {
    this->root = nullptr;
}

template <typename Type>
void Tree<Type>::real_delete(Tree<Type>::Node *leaf) {
    if (leaf != nullptr) {
        this->real_delete(leaf->left);
        this->real_delete(leaf->right);

        delete leaf;
    }
}

template <typename Type>
Tree<Type>::~Tree() {
    this->real_delete(this->root);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::real_insert(Tree<Type>::Node *leaf, Type value) {
    if (leaf == nullptr)
        leaf = new Node(value);
    else if (value < leaf->value)
        leaf->left = real_insert(leaf->left, value);
    else if (value > leaf->value)
        leaf->right = real_insert(leaf->right, value);

    return leaf;
}

template <typename Type>
void Tree<Type>::insert(Type value) {
    this->root = this->real_insert(this->root, value);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::min(Tree<Type>::Node *leaf) {
    if (leaf == nullptr)
        return nullptr;
    else if (leaf->left == nullptr)
        return leaf;
    else 
        return min(leaf->left);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::max(Tree<Type>::Node *leaf) {
    if (leaf == nullptr)
        return nullptr;
    else if (leaf->right == nullptr)
        return leaf;
    else
        return max(leaf->right);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::real_erase(Tree<Type>::Node *leaf, Type value) {
    if (leaf == nullptr)
        return nullptr;
    else if (value < leaf->value)
        leaf->left = real_erase(leaf->left, value);
    else if (value > leaf->value)
        leaf->right = real_erase(leaf->right, value);
    else if (leaf->left && leaf->right) {
        auto temp = min(leaf->right);

        leaf->value = temp->value;
        leaf->right = real_erase(leaf->right, leaf->value);
    } else {
        auto temp = leaf;

        if (leaf->left == nullptr)
            leaf = leaf->right;
        else if (leaf->right == nullptr)
            leaf = leaf->left;

        delete temp;
    }

    return leaf;
}

template <typename Type>
void Tree<Type>::erase(Type value) {
    this->root = this->real_erase(this->root, value);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::real_search(Tree<Type>::Node *leaf, Type value) {
    if (leaf == nullptr || leaf->value == value)
        return leaf;

    if (value < leaf->value)
        return real_search(leaf->left, value);

    return real_search(leaf->right, value);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::search(Type value) {
    return this->real_search(this->root, value);
}

template <typename Type>
void Tree<Type>::real_print(Tree<Type>::Node *leaf) {
    if (leaf != nullptr) {
        real_print(leaf->left);

        std::cout << leaf->value << " ";

        real_print(leaf->right);
    }
}

template <typename Type>
void Tree<Type>::print() {
    this->real_print(root);

    std::cout << std::endl;
}
