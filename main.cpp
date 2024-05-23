// main.cpp
#include <iostream>
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "BinaryTree.h"
#include <random>


int main() {
    BinarySearchTree *bst = new BinarySearchTree();
    bst->root = bst->insertNode(bst->root, 1000000);
    bst->insertNode(bst->root, 100000);
    bst->insertNode(bst->root, 80000);
    bst->insertNode(bst->root, 50000);
    bst->insertNode(bst->root, 34000);
    bst->insertNode(bst->root, 25323);
    bst->insertNode(bst->root, 16530);
    bst->insertNode(bst->root, 10000);
    bst->insertNode(bst->root, 5937);
    bst->insertNode(bst->root, 4444);
    bst->insertNode(bst->root, 4324);
    bst->insertNode(bst->root, 4000);
    bst->insertNode(bst->root, 3000);
    bst->insertNode(bst->root, 2000);
    bst->insertNode(bst->root, 1000);
    bst->insertNode(bst->root, 500);
    bst->insertNode(bst->root, 250);
    bst->insertNode(bst->root, 100);
    bst->insertNode(bst->root, 50);
    bst->insertNode(bst->root, 25);
    bst->insertNode(bst->root, 14);
    bst->insertNode(bst->root, 10);
    bst->insertNode(bst->root, 5);
    bst->insertNode(bst->root, 1);


    std::cout << "Inorder traversal of the given tree: ";
    bst->inorderTraversal(bst->root);

    std::cout << std::endl;
    bst->printTree(bst->root);

    AVLTree avl;

    for (int i = 0; i < 100; i++) {
         // Random number between 1 and 1000000
        int random = rand() % 1000000 + 1;
        avl.insert(random);
    }
    avl.printTree();
    return 0;
}
