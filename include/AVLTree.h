#pragma once
#include <iostream>

// AVL Tree implementation for storing movies
template <typename T>
class AVLTree {
private:
    // AVL Tree Node
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int size;

    // Get height of node
    int getHeight(Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Get balance factor
    int getBalance(Node* node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    // Update height of node
    void updateHeight(Node* node) {
        if (node != nullptr) {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        }
    }

    // Right rotation
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Insert helper (recursive)
    Node* insertHelper(Node* node, const T& value) {
        // Standard BST insertion
        if (node == nullptr) {
            size++;
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        } else {
            // Duplicate values not allowed
            return node;
        }

        // Update height
        updateHeight(node);

        // Get balance factor
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Find minimum value node
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Delete helper (recursive)
    Node* deleteHelper(Node* node, const T& value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            // Node to be deleted found
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
                size--;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteHelper(node->right, temp->data);
            }
        }

        if (node == nullptr) return node;

        // Update height
        updateHeight(node);

        // Get balance factor
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Search helper (recursive)
    Node* searchHelper(Node* node, const T& value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return searchHelper(node->left, value);
        }
        return searchHelper(node->right, value);
    }

    // In-order traversal helper
    void inOrderHelper(Node* node, void (*visit)(const T&)) const {
        if (node != nullptr) {
            inOrderHelper(node->left, visit);
            visit(node->data);
            inOrderHelper(node->right, visit);
        }
    }

    // Pre-order traversal helper
    void preOrderHelper(Node* node, void (*visit)(const T&)) const {
        if (node != nullptr) {
            visit(node->data);
            preOrderHelper(node->left, visit);
            preOrderHelper(node->right, visit);
        }
    }

    // Post-order traversal helper
    void postOrderHelper(Node* node, void (*visit)(const T&)) const {
        if (node != nullptr) {
            postOrderHelper(node->left, visit);
            postOrderHelper(node->right, visit);
            visit(node->data);
        }
    }

    // Clear helper (recursive)
    void clearHelper(Node* node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    // Copy helper (recursive)
    Node* copyHelper(Node* node) {
        if (node == nullptr) return nullptr;
        
        Node* newNode = new Node(node->data);
        newNode->height = node->height;
        newNode->left = copyHelper(node->left);
        newNode->right = copyHelper(node->right);
        return newNode;
    }

public:
    // Constructor
    AVLTree() : root(nullptr), size(0) {}

    // Copy constructor
    AVLTree(const AVLTree& other) : root(nullptr), size(0) {
        root = copyHelper(other.root);
        size = other.size;
    }

    // Assignment operator
    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            clear();
            root = copyHelper(other.root);
            size = other.size;
        }
        return *this;
    }

    // Destructor
    ~AVLTree() {
        clear();
    }

    // Insert value
    void insert(const T& value) {
        root = insertHelper(root, value);
    }

    // Delete value
    void remove(const T& value) {
        root = deleteHelper(root, value);
    }

    // Search for value
    bool search(const T& value) const {
        return searchHelper(root, value) != nullptr;
    }

    // Get pointer to data (for modification)
    T* find(const T& value) {
        Node* node = searchHelper(root, value);
        return node != nullptr ? &(node->data) : nullptr;
    }

    const T* find(const T& value) const {
        Node* node = searchHelper(root, value);
        return node != nullptr ? &(node->data) : nullptr;
    }

    // In-order traversal
    void inOrder(void (*visit)(const T&)) const {
        inOrderHelper(root, visit);
    }

    // Pre-order traversal
    void preOrder(void (*visit)(const T&)) const {
        preOrderHelper(root, visit);
    }

    // Post-order traversal
    void postOrder(void (*visit)(const T&)) const {
        postOrderHelper(root, visit);
    }

    // Get size
    int getSize() const {
        return size;
    }

    // Check if empty
    bool isEmpty() const {
        return root == nullptr;
    }

    // Clear tree
    void clear() {
        clearHelper(root);
        root = nullptr;
        size = 0;
    }

    // Get height of tree
    int getTreeHeight() const {
        return getHeight(root);
    }
};
