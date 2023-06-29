#include "BST.h"

BST::BST() : root(nullptr) {}

BST::~BST() {
    delete root;
}

void BST::insert(int value) {
    root = insert(root, value);
}

void BST::remove(int value) {
    root = remove(root, value);
}

bool BST::find(int value) {
    return find(root, value);
}

Node* BST::insert(Node* node, int value) {
    if (node == nullptr) return new Node(value);
    if (value < node->data) node->left = insert(node->left, value);
    else if (value > node->data) node->right = insert(node->right, value);
    return node;
}

Node* BST::remove(Node* node, int value) {
    if (node == nullptr) return node;
    if (value < node->data) node->left = remove(node->left, value);
    else if (value > node->data) node->right = remove(node->right, value);
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }
    return node;
}

Node* BST::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) current = current->left;
    return current;
}

bool BST::find(Node* node, int value) {
    // Recursive find
    if (node == nullptr) {
        return false;
    }

    // Print node information
    std::cout << "Visiting Node: " << node->data << std::endl;

    if (value < node->data) {
        return find(node->left, value);
    } else if (value > node->data) {
        return find(node->right, value);
    }
    
    return true;
}
