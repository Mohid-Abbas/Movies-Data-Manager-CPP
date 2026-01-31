#pragma once
#include "LinkedList.h"

// Queue implementation using LinkedList
template <typename T>
class Queue {
private:
    LinkedList<T> list;

public:
    // Constructor
    Queue() {}

    // Enqueue - add element to rear
    void enqueue(const T& value) {
        list.append(value);
    }

    // Dequeue - remove element from front
    T dequeue() {
        if (isEmpty()) {
            throw "Queue is empty!";
        }
        T value = list.get(0);
        list.removeAt(0);
        return value;
    }

    // Peek - view front element without removing
    T& front() {
        if (isEmpty()) {
            throw "Queue is empty!";
        }
        return list.get(0);
    }

    const T& front() const {
        if (isEmpty()) {
            throw "Queue is empty!";
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

    // Clear queue
    void clear() {
        list.clear();
    }
};
