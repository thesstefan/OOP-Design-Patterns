#pragma once

template <typename KeyType, typename ValueType>
class KeyTree {
    private:
        class Node {
            public:
                KeyType key;
                ValueType value;

                Node *parent;

                Node *left;
                Node *right;

                Node();
                Node(const KeyType &key, const ValueType &value);
                Node(const KeyType &key, const ValueType &value, Node *parent);
        };

        Node *root;

        void real_delete(Node *leaf);

        Node *real_insert(Node *leaf, Node *parent, const KeyType& key, const ValueType& value);
        Node *real_erase(Node *leaf, const KeyType& key);

        Node *real_search(Node *leaf, const KeyType& key) const;

        Node *min(Node *leaf) const;
        Node *max(Node *leaf) const;

        void real_print(Node *leaf) const;

    public:
        class Iterator {
            private:
                Node *current;

                void increment();
                void decrement();

            public:
                Iterator();
                Iterator(Node *node);
                Iterator(const Iterator &iterator);

                Iterator& operator=(const Iterator &iterator);

                Iterator operator++();
                Iterator operator++(int);

                Iterator operator--();
                Iterator operator--(int);

                Node &operator*();
                Node *operator->();

                bool operator==(const Iterator &iterator) const;
                bool operator!=(const Iterator &iterator) const;
        };

        class ConstIterator {
            private:
                Node *current;

                void increment();
                void decrement();

            public:
                ConstIterator();
                ConstIterator(Node *node);
                ConstIterator(const ConstIterator &iterator);

                ConstIterator& operator=(const ConstIterator &iterator);

                ConstIterator operator++();
                ConstIterator operator++(int);

                ConstIterator operator--();
                ConstIterator operator--(int);

                const Node &operator*() const;
                const Node *operator->() const;

                bool operator==(const ConstIterator &iterator) const;
                bool operator!=(const ConstIterator &iterator) const;
        };

        KeyTree();
        KeyTree(const KeyTree& other);
        
        KeyTree& operator=(const KeyTree& other);

        ~KeyTree();

        void insert(const KeyType &key, const ValueType &value);
        void erase(const KeyType &key);

        Node *search(const KeyType &key) const;

        void print() const;

        Iterator begin();
        Iterator end();

        ConstIterator cbegin() const;
        ConstIterator cend() const;
};

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::Node::Node() {
    this->key = KeyType();
    this->value = ValueType();

    this->parent = nullptr;

    this->left = nullptr;
    this->right = nullptr;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::Node::Node(const KeyType& key, const ValueType& value) {
    this->key = key;
    this->value = value;

    this->parent = nullptr;

    this->left = nullptr;
    this->right = nullptr;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::Node::Node(const KeyType& key, const ValueType& value, Node* parent) {
    this->key = key;
    this->value = value;

    this->parent = parent;

    this->left = nullptr;
    this->right = nullptr;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::KeyTree() {
    this->root = nullptr;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::KeyTree(const KeyTree &other) {
    this->root = nullptr;

    for (auto it = other.cbegin(); it != other.cend(); it++)
        this->insert(it->key, it->value);

}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>& KeyTree<KeyType, ValueType>::operator=(const KeyTree &other) {
    this->real_delete(this->root);

    this->root = nullptr;

    for (auto it = other.cbegin(); it != other.cend(); it++)
        this->insert(it->key, it->value);
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::real_delete(KeyTree<KeyType, ValueType>::Node *leaf) {
    if (leaf != nullptr) {
        this->real_delete(leaf->left);
        this->real_delete(leaf->right);

        delete leaf;
    }
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::~KeyTree() {
    this->real_delete(this->root);
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::real_insert(KeyTree<KeyType, ValueType>::Node *leaf, KeyTree<KeyType, ValueType>::Node *parent, const KeyType& key, const ValueType& value) {
    if (leaf == nullptr)
        leaf = new Node(key, value, parent);
    else if (key < leaf->key)
        leaf->left = real_insert(leaf->left, leaf, key, value);
    else if (key > leaf->key)
        leaf->right = real_insert(leaf->right, leaf, key, value);

    return leaf;
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    this->root = this->real_insert(this->root, this->root, key, value);
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::min(KeyTree<KeyType, ValueType>::Node *leaf) const {
    if (leaf == nullptr)
        return nullptr;
    else if (leaf->left == nullptr)
        return leaf;
    else 
        return min(leaf->left);
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::max(KeyTree<KeyType, ValueType>::Node *leaf) const {
    if (leaf == nullptr)
        return nullptr;
    else if (leaf->right == nullptr)
        return leaf;
    else
        return max(leaf->right);
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::real_erase(KeyTree<KeyType, ValueType>::Node *leaf, const KeyType& key) {
    if (leaf == nullptr)
        return nullptr;
    else if (key < leaf->key)
        leaf->left = real_erase(leaf->left, key);
    else if (key > leaf->key)
        leaf->right = real_erase(leaf->right, key);
    else if (leaf->left == nullptr && leaf->right == nullptr) {
        delete leaf;

        leaf = nullptr;
    } else if (leaf->right == nullptr) {
        auto parent = leaf->parent;
        auto left = leaf->left;

        delete leaf;

        leaf = left;
        leaf->parent = parent;
    } else if (leaf->left == nullptr) {
        auto parent = leaf->parent;
        auto right = leaf->right;

        delete leaf;

        leaf = right;
        leaf->parent = parent;
    } else {
        auto temp = max(leaf->left);
        auto parent = temp->parent;

        leaf->key = temp->key;
        leaf->value = temp->value;

        if (parent != leaf)
            parent->right = temp->left;
        else
            leaf->left = temp->left;

        delete temp;
        temp = nullptr;
    }

    return leaf;
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::erase(const KeyType& key) {
    this->root = this->real_erase(this->root, key);
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::real_search(KeyTree<KeyType, ValueType>::Node *leaf, const KeyType& key) const {
    if (leaf == nullptr || leaf->key == key)
        return leaf;

    if (key < leaf->key)
        return real_search(leaf->left, key);

    return real_search(leaf->right, key);
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::search(const KeyType& key) const {
    return this->real_search(this->root, key);
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::real_print(KeyTree<KeyType, ValueType>::Node *leaf) const {
    if (leaf != nullptr) {
        real_print(leaf->left);

        std::cout << '[' << leaf->key << ',' << leaf->value << ']' << std::endl;

        if (leaf->parent != nullptr)
            std::cout << "PARENT -> " << leaf->parent->key << std::endl;
        else 
            std::cout << "ROOT" << std::endl;

        std::cout << "LEFT -> ";

        if (leaf->left != nullptr)
            std::cout << leaf->left->key << std::endl;
        else 
            std::cout << "NOTHING" << std::endl;

        std::cout << "RIGHT -> ";

        if (leaf->right != nullptr)
            std::cout << leaf->right->key << std::endl;
        else 
            std::cout << "NOTHING" << std::endl;

        std::cout << std::endl;

        real_print(leaf->right);
    }
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::print() const {
    this->real_print(root);

    std::cout << std::endl;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::Iterator::Iterator() {
    this->current = nullptr;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::Iterator::Iterator(typename KeyTree<KeyType, ValueType>::Node *node) {
    this->current = node;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::Iterator::Iterator(const typename KeyTree<KeyType, ValueType>::Iterator &iterator) {
    this->current = iterator.current;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator& KeyTree<KeyType, ValueType>::Iterator::operator=(const Iterator &iterator) {
    this->current = iterator.current;
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::Iterator::increment() {
    if (this->current->right != nullptr) {
        this->current = this->current->right;

        while (this->current->left != nullptr)
            this->current = this->current->left;
    } else {
        auto node = this->current->parent;

        while (node && this->current == node->right) {
            this->current = node;

            node = node->parent;
        }

        if (this->current->right != node)
            this->current = node;
    }
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator KeyTree<KeyType, ValueType>::Iterator::operator++() {
    this->increment();

    return *this;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator KeyTree<KeyType, ValueType>::Iterator::operator++(int) {
    auto iterator = *this;

    this->increment();

    return iterator;
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::Iterator::decrement() {
    if (this->current->parent->parent == this->current)
        this->current = this->current->right;
    else if (this->current->left != nullptr) {
        auto node = this->current->left;

        while (node->right != nullptr)
            node = node->right;

        this->current = node;
    } else {
        auto node = this->current->parent;

        while (this->current == node->left) {
            this->current = node;
            node = node->parent;
        }

        this->current = node;
    }
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator KeyTree<KeyType, ValueType>::Iterator::operator--() {
    this->decrement();

    return *this;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator KeyTree<KeyType, ValueType>::Iterator::operator--(int) {
    auto iterator = *this;

    this->decrement();

    return iterator;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node& KeyTree<KeyType, ValueType>::Iterator::operator*() {
    return *this->current;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::Iterator::operator->() {
    return this->current;
}

template <typename KeyType, typename ValueType>
bool KeyTree<KeyType, ValueType>::Iterator::operator==(const Iterator& iterator) const {
    return this->current == iterator.current;
}

template <typename KeyType, typename ValueType>
bool KeyTree<KeyType, ValueType>::Iterator::operator!=(const Iterator& iterator) const {
    return this->current != iterator.current;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator KeyTree<KeyType, ValueType>::begin() {
    return KeyTree<KeyType, ValueType>::Iterator(this->min(this->root));
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::Iterator KeyTree<KeyType, ValueType>::end() {
    return KeyTree<KeyType, ValueType>::Iterator(nullptr);
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::ConstIterator::ConstIterator() {
    this->current = nullptr;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::ConstIterator::ConstIterator(typename KeyTree<KeyType, ValueType>::Node *node) {
    this->current = node;
}

template <typename KeyType, typename ValueType>
KeyTree<KeyType, ValueType>::ConstIterator::ConstIterator(const typename KeyTree<KeyType, ValueType>::ConstIterator &iterator) {
    this->current = iterator.current;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator& KeyTree<KeyType, ValueType>::ConstIterator::operator=(const typename KeyTree<KeyType, ValueType>::ConstIterator &iterator) {
    this->current = iterator.current;
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::ConstIterator::increment() {
    if (this->current->right != nullptr) {
        this->current = this->current->right;

        while (this->current->left != nullptr)
            this->current = this->current->left;
    } else {
        auto node = this->current->parent;

        while (node && this->current == node->right) {
            this->current = node;

            node = node->parent;
        }

        if (this->current->right != node)
            this->current = node;
    }
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator KeyTree<KeyType, ValueType>::ConstIterator::operator++() {
    this->increment();

    return *this;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator KeyTree<KeyType, ValueType>::ConstIterator::operator++(int) {
    auto iterator = *this;

    this->increment();

    return iterator;
}

template <typename KeyType, typename ValueType>
void KeyTree<KeyType, ValueType>::ConstIterator::decrement() {
    if (this->current->parent->parent == this->current)
        this->current = this->current->right;
    else if (this->current->left != nullptr) {
        auto node = this->current->left;

        while (node->right != nullptr)
            node = node->right;

        this->current = node;
    } else {
        auto node = this->current->parent;

        while (this->current == node->left) {
            this->current = node;
            node = node->parent;
        }

        this->current = node;
    }
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator KeyTree<KeyType, ValueType>::ConstIterator::operator--() {
    this->decrement();

    return *this;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator KeyTree<KeyType, ValueType>::ConstIterator::operator--(int) {
    auto iterator = *this;

    this->decrement();

    return iterator;
}

template <typename KeyType, typename ValueType>
const typename KeyTree<KeyType, ValueType>::Node& KeyTree<KeyType, ValueType>::ConstIterator::operator*() const {
    return *this->current;
}

template <typename KeyType, typename ValueType>
const typename KeyTree<KeyType, ValueType>::Node* KeyTree<KeyType, ValueType>::ConstIterator::operator->() const {
    return this->current;
}

template <typename KeyType, typename ValueType>
bool KeyTree<KeyType, ValueType>::ConstIterator::operator==(const ConstIterator& iterator) const {
    return this->current == iterator.current;
}

template <typename KeyType, typename ValueType>
bool KeyTree<KeyType, ValueType>::ConstIterator::operator!=(const ConstIterator& iterator) const {
    return this->current != iterator.current;
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator KeyTree<KeyType, ValueType>::cbegin() const {
    return KeyTree<KeyType, ValueType>::ConstIterator(this->min(this->root));
}

template <typename KeyType, typename ValueType>
typename KeyTree<KeyType, ValueType>::ConstIterator KeyTree<KeyType, ValueType>::cend() const {
    return KeyTree<KeyType, ValueType>::ConstIterator(nullptr);
}
