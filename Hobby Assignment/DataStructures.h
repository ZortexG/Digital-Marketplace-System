#ifndef LINKED_DATA_STRUCTURES_H
#define LINKED_DATA_STRUCTURES_H

#include <iostream>
#include <string>
#include <stdexcept>

// --- Linked Stack (Malik Style) ---
template <class Type>
class linkedStackType {
private:
    struct nodeType {
        Type info;
        nodeType* link;
    };
    nodeType* stackTop;

public:
    linkedStackType() : stackTop(nullptr) {}

    bool isEmptyStack() const { return stackTop == nullptr; }

    void push(const Type& newElement) {
        nodeType* newNode = new nodeType;
        newNode->info = newElement;
        newNode->link = stackTop;
        stackTop = newNode;
    }

    Type top() const {
        if (stackTop == nullptr) throw std::runtime_error("Stack is empty");
        return stackTop->info;
    }

    void pop() {
        if (stackTop != nullptr) {
            nodeType* temp = stackTop;
            stackTop = stackTop->link;
            delete temp;
        }
    }
};

// --- Linked Queue (Malik Style) ---
template <class Type>
class linkedQueueType {
private:
    struct nodeType {
        Type info;
        nodeType* link;
    };
    nodeType *queueFront, *queueRear;

public:
    linkedQueueType() : queueFront(nullptr), queueRear(nullptr) {}

    bool isEmptyQueue() const { return queueFront == nullptr; }

    void addQueue(const Type& newElement) {
        nodeType* newNode = new nodeType;
        newNode->info = newElement;
        newNode->link = nullptr;
        if (queueFront == nullptr) {
            queueFront = newNode;
            queueRear = newNode;
        } else {
            queueRear->link = newNode;
            queueRear = newNode;
        }
    }

    void deleteQueue() {
        if (!isEmptyQueue()) {
            nodeType* temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
            if (queueFront == nullptr) queueRear = nullptr;
        }
    }

    Type front() const {
        if (queueFront == nullptr) throw std::runtime_error("Queue is empty");
        return queueFront->info;
    }
};

#endif
