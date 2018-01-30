#ifndef TREE_H
#define TREE_H

template <typename Type>
class Tree {
    private:
        class Node {
            public:
                Type value;

                Node *left;
                Node *right;

                Node(Type value);
        };

        Node *root;

        void real_delete(Node *leaf);

        Node *real_insert(Node *leaf, Type value);
        Node *real_erase(Node *leaf, Type value);

        Node *real_search(Node *leaf, Type value);

        Node *min(Node *leaf);
        Node *max(Node *leaf);

        void real_print(Node *leaf);

    public:
        Tree();
        ~Tree();

        void insert(Type value);
        void erase(Type value);

        Node *search(Type value);

        void print();
};

#endif
