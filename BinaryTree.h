//
// Created by BiomedicLJZ on 5/5/2024.
//

#ifndef ARBOLES_BINARYTREE_H
#define ARBOLES_BINARYTREE_H
#include <iostream>



class BinaryTree {
public:
    struct Node {
        int value;
        Node* left;
        Node* right;
    };

    Node* root;

    BinaryTree() : root(nullptr) {}

    Node* insertNode(Node* root, int value) {
        if (root == nullptr) {
            root = new Node();
            root->value = value;
            root->left = nullptr;
            root->right = nullptr;
            return root;
        }

        if (value < root->value) {
            root->left = insertNode(root->left, value);
        } else if (value > root->value) {
            root->right = insertNode(root->right, value);
        }

        return root;
    }

    void inorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderTraversal(root->left);
        std::cout << root->value << " ";
        inorderTraversal(root->right);
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
    void preOrderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        std::cout << root->value << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }

    void postOrderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        std::cout << root->value << " ";
    }

};


#endif //ARBOLES_BINARYTREE_H
