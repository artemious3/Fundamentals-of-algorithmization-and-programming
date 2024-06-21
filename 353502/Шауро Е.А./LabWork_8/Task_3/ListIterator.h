#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "Node.h"

template <typename Key, typename Value>
class ListIterator {
public:
    explicit ListIterator(Node<Key, Value>* node) : current(node) {}

    Key key() const { return current->data.first; }

    Value value() const { return current->data.second; }

    ListIterator& operator++() {
        current = nextNode(current);
        return *this;
    }

    ListIterator& operator--() {
        current = prevNode(current);
        return *this;
    }

    bool operator!=(const ListIterator& other) const {
        return current != other.current;
    }

    Node<Key, Value>* operator*() const { return current; }

private:
    Node<Key, Value>* current;

    Node<Key, Value>* nextNode(Node<Key, Value>* node) {
        if (node->right) {
            node = node->right;
            while (node->left) {
                node = node->left;
            }
        } else {
            Node<Key, Value>* parent = node->parent;
            while (parent && node == parent->right) {
                node = parent;
                parent = parent->parent;
            }
            node = parent;
        }
        return node;
    }

    Node<Key, Value>* prevNode(Node<Key, Value>* node) {
        if (node->left) {
            node = node->left;
            while (node->right) {
                node = node->right;
            }
        } else {
            Node<Key, Value>* parent = node->parent;
            while (parent && node == parent->left) {
                node = parent;
                parent = parent->parent;
            }
            node = parent;
        }
        return node;
    }
};

#endif // LISTITERATOR_H
