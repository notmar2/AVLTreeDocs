#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
    public:
    void printTree() {
        printTree(root, 0, 10);
    }
private:
    Node* root;

    int getNodeHeight(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int maxHeight(int a, int b) {
        return (a > b)? a : b;
    }

    Node* newNode(int value) {
        Node* node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return(node);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

        return y;
    }

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return getNodeHeight(N->left) - getNodeHeight(N->right);
    }

    Node* insertNode(Node* node, int value) {
        if (node == nullptr)
            return(newNode(value));

        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else
            return node;

        node->height = 1 + maxHeight(getNodeHeight(node->left), getNodeHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr)
            return root;

        if ( value < root->value )
            root->left = deleteNode(root->left, value);
        else if( value > root->value )
            root->right = deleteNode(root->right, value);
        else {
            if( (root->left == nullptr) || (root->right == nullptr) ) {
                Node *temp = root->left ? root->left : root->right;

                if(temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);

                root->value = temp->value;

                root->right = deleteNode(root->right, temp->value);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + maxHeight(getNodeHeight(root->left), getNodeHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteTree(Node* node) {
        if (node == nullptr)
            return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        std::cout << node->value << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        std::cout << node->value << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->value << " ";
    }
    void printTree(Node* root, int space = 0, int COUNT = 10) {
        if (root == nullptr) {
            return;
        }

        space += COUNT;
        printTree(root->right, space);

        std::cout << std::endl;

        for (int i = COUNT; i < space; i++) {
            std::cout << " ";
        }

        std::cout << root->value << "\n";

        printTree(root->left, space);
    }
};


#endif // AVLTREE_H
