# AVL Tree

An AVL Tree is a type of self-balancing binary search tree.
Its name comes from its creators, Georgy Adelson-Velsky and Evgenii Landis.

Self-balancing binary search trees are trees that automatically rearrange their nodes with the goal of maintaining O(log n) traversal complexity.
Normal binary search trees have a problem, suboptimally ordered insertions can create skewed trees.
This means that if data is inserted into the tree in a suboptimal order (like in perfecly ascending order, for example) the tree can end up with a worst-case scenario complexity of O(n) similar to a linked list; 
this because of the nature of its insertion mechanisms which traverse the tree normally until they find an empty space for a new node. 

The AVL tree achieves this by keeping track of the height of the subtrees for every node to ensure they stay balanced.

In our custom implementation of the AVL tree we begin with our compiler macros to define our library and include `<iostream>` for input/output operations.

```C++
#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
```

After this we define our `Node` structure:

```C++
struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};
```

This is the structure that forms each cell of our tree (called nodes), they contain pointers to the left and right child nodes, trees can only be traversed top-down; they also contain a value, this is tree will contain integer values, and a height value that registers the height of the node.

Next we declare our class and a printing method:

```C++
class AVLTree {
    public:
    void printTree() {
        printTree(root, 0, 10);
    }
private:
    Node* root;
```

`printTree()` has a parametric overload which will be discussed further along.
This one is simply a wrapper for the parametric `printTree()` method that passes in some default values, so we can call it without passing in parameters as well.

We also declare a private pointer to a `Node` object called root, that will serve as the first node of our tree.

Next we declare a method to get the height of a given node, so long as it isn't empty.

```C++
int getNodeHeight(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }
```

The following method is returns the highest number within the given parameters, for use in comparison of heights.

```C++
int maxHeight(int a, int b) {
        return (a > b)? a : b;
    }
```

It's worth noting that we are utilizing the ternary operator for this operation. This is a shorthand operator for an if, else statement that can be used to set a simple expression as a result of a certain boolean expression being truthy or not.
In this case it's being used to return our parameter `a` if it's bigger than our parameter `b` or to return `b` if else.

Next, our creation method, which will be used to add a new node to our tree.

```C++
Node* newNode(int value) {
        Node* node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return(node);
    }
```

The value is taken as a parameter and assigned to the value of our new node.
Since a new node will always be the root of the new subtree that it forms, its children are set to be null pointers and its height is set to 1.

After this we have our first rotation method.
In an AVL tree the rearrangement of our nodes is done through rotations.

```C++
Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;

        return x;
    }
```

In a right rotation we make the left node of our imbalanced node the root of our subtree, here we do this through our new pointer `x`.
Then make the right node of our new subtree's root, if it exists, the new left child.
Last we make our previous subtree's root the right child of our new one.
We also update our height values with the value of the highest branch.

We also have a left rotation:

```C++
Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

        return y;
    }
```

It's similar to our right rotation but flipped. We make our right sub-node our new root.
Then we make our previously left node and assigned it to the right of our new subtree's root.
Our previous root will become our new left child.
After all of this we again update our heights.

To calculate which node is imbalanced we use the following method:

```C++
int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return getNodeHeight(N->left) - getNodeHeight(N->right);
    }
```

It takes a node and then subtracts the height of the right node from the height of the left.
If the result is larger than 1 or smaller than -1 it means one side is too large.

Finally, we have our insert method:

```C++
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
```

It's pretty self-explanatory, it takes in our node and a value and does a set of comparisons.
To begin with a new node will be made if none is given (meaning there is no root); the following checks allow us to place our value in the right place according to its order.
Then the height is updated, and we commence checking our balancing.
If our balance is off we call the rotations according to the type of imbalance.

Following we have a method used to return the minimum value:

```C++
Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }
```

It simply loops through the left values until we don't have anymore.

After this we have our second to last private method, and another big one. The delete method.

```C++
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
```

The logic becomes rather complicated because deleting a node means rearranging our tree.
First, if the node given isn't null, we traverse our tree recursively to assign the children of the node we want to delete.
Once we have found our value we need to check if it has children, if so we can update our subtree's root with them, and then delete our current node.
After this we perform our balance checks same as in the insert method and perform the pertinent rotations.
Finally, we return the updated subtree's root.

Our last private method is used to delete all nodes in a tree.

```C++
void deleteTree(Node* node) {
        if (node == nullptr)
            return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }
```

Also self-explanatory, the method calls itself recursively and calls delete on each node.

Next, we have our public methods:

```C++
public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }
```

Amongst these we have our constructor and destructor.
They are basic and simply used to initialize our root and also call `deleteTree()` on its destructor to ensure our nodes are freed from memory to prevent leaks.

Next our insert and remove methods:

```C++
void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }
```

Are used, as the name implies, to insert and remove values utilizing the methods we already declared.

We also declare 3 methods of traversal:

```C++
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
```

`inorderTraversal` prints the left subtree, then the root, then the right subtree. This gives us the elements in ascending order.

`preorderTraversal` prints out the root, then the left subtree, then the right subtree. This gives us the elements in the actual order of the tree, meaning it can be useful for printing with the actual order or copying a tree.

`postorderTraversal` prints out the left subtree, then the right and last the root. This is useful when you want to access the children before the root, like for a different version of a delete method.

Last but not least we have the `printTree()` method

```C++
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
```

This method is another way of printing that has added spacing and line jumps to make it more readable.

The last line of our file simply ends the definition macro for our compiler
```C++
#endif // AVLTREE_H
```
