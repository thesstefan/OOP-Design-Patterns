#include <iostream>

template <typename Type>
class Tree {
    private:
        class Node {
            public:
                Type value;

                Node *left;
                Node *right;

                Node(Type value) {
                    this->value = value;

                    this->left = nullptr;
                    this->right = nullptr;
                }
        };

        Node *root;

        void delete_tree(Node *leaf) {
            if (leaf != nullptr) {
                this->delete_tree(leaf->left);
                this->delete_tree(leaf->right);

                delete leaf;
            }
        }

        void insert(Type value, Node *leaf) {
            if (value < leaf->value) {
                if (leaf->left != nullptr)
                    insert(value, leaf->left);
                else
                    leaf->left = new Node(value);
            } else {
                if (leaf->right != nullptr)
                    insert(value, leaf->right);
                else
                    leaf->right = new Node(value);
            }
        }

        Node *search(Type value, Node *leaf) {
            if (leaf != nullptr) {
                if (value == leaf->value)
                    return leaf;

                if (value < leaf->value)
                    return this->search(value, leaf->left);
                else
                    return this->search(value, leaf->right);
            } else
                return nullptr;
        }

    public:
        Tree() {
            this->root = nullptr;
        }

        ~Tree() {
            this->delete_tree(this->root);
        }

        void insert(Type value) {
            if (this->root != nullptr)
                this->insert(value, this->root);
            else
                this->root = new Node(value);
        }

        Node *search(Type value) {
            return this->search(value, this->root);
        }
};

int main() {
    Tree<int> *tree = new Tree<int>();

    tree->insert(100);

    auto node = tree->search(100);

    if (node == nullptr)
        std::cout << "NULL" << std::endl;
    else
        std::cout << node->value << std::endl;

    return 0;
}
