#pragma once
#include <iostream>

// Generic LinkedList template class
template <typename T>
class LinkedList {
private:
    // Node structure
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // Constructor
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Copy constructor
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            append(current->data);
            current = current->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                append(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Destructor
    ~LinkedList() {
        clear();
    }

    // Add element at the end
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Add element at the beginning
    void prepend(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    // Insert at specific position
    void insertAt(int index, const T& value) {
        if (index < 0 || index > size) return;
        
        if (index == 0) {
            prepend(value);
            return;
        }
        
        if (index == size) {
            append(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    // Remove element by value (first occurrence)
    bool remove(const T& value) {
        if (head == nullptr) return false;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            size--;
            return true;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next;
                if (temp == tail) tail = current;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Remove at specific index
    bool removeAt(int index) {
        if (index < 0 || index >= size || head == nullptr) return false;

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            size--;
            return true;
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* temp = current->next;
        current->next = current->next->next;
        if (temp == tail) tail = current;
        delete temp;
        size--;
        return true;
    }

    // Search for element
    bool contains(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    // Get element at index
    T& get(int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& get(int index) const {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Get size
    int getSize() const {
        return size;
    }

    // Check if empty
    bool isEmpty() const {
        return size == 0;
    }

    // Clear all elements
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    // Display all elements
    void display() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Iterator class for traversal
    class Iterator {
    private:
        Node* current;
    
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    };

    // Begin iterator
    Iterator begin() {
        return Iterator(head);
    }

    // End iterator
    Iterator end() {
        return Iterator(nullptr);
    }

    // Const iterator
    class ConstIterator {
    private:
        const Node* current;
    
    public:
        ConstIterator(const Node* node) : current(node) {}

        const T& operator*() const {
            return current->data;
        }

        ConstIterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }
    };

    // Const begin iterator
    ConstIterator begin() const {
        return ConstIterator(head);
    }

    // Const end iterator
    ConstIterator end() const {
        return ConstIterator(nullptr);
    }
};
