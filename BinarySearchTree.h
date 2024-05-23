//
// Created by BiomedicLJZ on 5/5/2024.
//

#ifndef ARBOLES_BINARYSEARCHTREE_H
#define ARBOLES_BINARYSEARCHTREE_H
#include "BinaryTree.h"
#include <iostream>


class BinarySearchTree : public BinaryTree {
public:
    Node* search(Node* root, int value) {
        if (root == nullptr || root->value == value) {
            return root;
        }

        if (root->value < value) {
            return search(root->right, value);
        }

        return search(root->left, value);
    }

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

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->value) {
            root->left = deleteNode(root->left, value);
        } else if (value > root->value) {
            root->right = deleteNode(root->right, value);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }

        return root;
    }

    Node* minValueNode(Node* root) {
        Node* current = root;

        while (current && current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

};


#endif //ARBOLES_BINARYSEARCHTREE_H
