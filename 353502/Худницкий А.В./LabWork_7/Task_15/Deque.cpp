#include "Deque.h"
#include <iostream>

Deque::Deque() : head(nullptr), tail(nullptr), size(0) {}

Deque::~Deque() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Deque::enqueue(int value) {
    Node* newNode = new Node(value);
    if(tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

int Deque::dequeue() {
    if (head == nullptr) {
        throw std::runtime_error("Deque is empty.");
    }
    Node* temp = head;
    int value = head->value;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
    size--;
    return value;
}

void Deque::swapMaxMin() {
    if (isEmpty()) {
        return;
    }

    Node* minNode = head;
    Node* maxNode = head;
    Node* currentNode = head;

    while(currentNode != nullptr) {
        if (currentNode->value < minNode->value) {
            minNode = currentNode;
        }
        if (currentNode->value > maxNode->value) {
            maxNode = currentNode;
        }
        currentNode = currentNode->next;
    }

    if (minNode != maxNode) {
        int temp = minNode->value;
        minNode->value = maxNode->value;
        maxNode->value = temp;
    }
}

bool Deque::isEmpty() {
    return size == 0;
}

void Deque::clear() {
    while(!isEmpty()) {
        dequeue();
    }
}

int Deque::getSize() {
    return size;
}

int Deque::peekFront() {
    if (isEmpty()) {
        throw std::runtime_error("Deque is empty.");
    }
    return head->value;
}

int Deque::peekBack() {
    if (isEmpty()) {
        throw std::runtime_error("Deque is empty.");
    }
    return tail->value;
}

void Deque::insertBefore(Node* node, int value) {
    if (node == nullptr) {
        enqueue(value);
    } else {
        Node* newNode = new Node(value);
        newNode->next = node;
        newNode->prev = node->prev;
        if (node->prev != nullptr) {
            node->prev->next = newNode;
        } else {
            head = newNode;
        }
        node->prev = newNode;
        size++;
    }
}

void Deque::insertAfter(Node* node, int value) {
    if (node == nullptr) {
        enqueue(value);
    } else {
        Node* newNode = new Node(value);
        newNode->prev = node;
        newNode->next = node->next;
        if (node -> next != nullptr) {
            node->next->prev = newNode;
        } else {
            tail = newNode;
        }
        node->next = newNode;
        size++;
    }
}

void Deque::remove(Node* node) {
    if (node == nullptr) {
        return;
    }
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    delete node;
    size--;
}

void Deque::resize(int newSize, int defaultValue) {
    while (size > newSize) {
        dequeue();
    }
    while(size < newSize) {
        enqueue(defaultValue);
    }
}

void Deque::push_back(int value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void Deque::push_front(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    size++;
}

int Deque::pop_back() {
    if (tail == nullptr) {
        throw std::runtime_error("Deque is empty.");
    }
    Node* temp = tail;
    int value = tail->value;
    tail = tail->prev;
    if (tail == nullptr) {
        head = nullptr;
    } else {
        tail->next = nullptr;
    }
    delete temp;
    size--;
    return value;
}

int Deque::pop_front() {
    if (head == nullptr) {
        throw std::runtime_error("Deque is empty.");
    }
    Node* temp = head;
    int value = head->value;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
    size--;
    return value;
}
