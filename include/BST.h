#ifndef BST_H
#define BST_H
#include "Node.h"
#include <iostream>

class BST {
private:
    Node* root;
    Node* insert(Node* node, int value);
    Node* remove(Node* node, int value);
    Node* minValueNode(Node* node);
    bool find(Node* node, int value);
public:
    BST();
    ~BST();
    void insert(int value);
    void remove(int value);
    bool find(int value);
};

#endif
