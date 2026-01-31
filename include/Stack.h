#pragma once
#include "LinkedList.h"

// Stack implementation using LinkedList
template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    // Constructor
    Stack() {}

    // Push - add element to top
    void push(const T& value) {
        list.prepend(value);
    }

    // Pop - remove and return top element
    T pop() {
        if (isEmpty()) {
            throw "Stack is empty!";
        }
        T value = list.get(0);
        list.removeAt(0);
        return value;
    }

    // Peek - view top element without removing
    T& top() {
        if (isEmpty()) {
            throw "Stack is empty!";
        }
        return list.get(0);
    }

    const T& top() const {
        if (isEmpty()) {
            throw "Stack is empty!";
        }
        return list.get(0);
    }

    // Check if empty
    bool isEmpty() const {
        return list.isEmpty();
    }

    // Get size
    int getSize() const {
        return list.getSize();
    }

    // Clear stack
    void clear() {
        list.clear();
    }
};
