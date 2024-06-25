#include "ListHeap.h"

#include <queue>
#include <stdexcept>

template<typename T>
ListHeap<T>::ListHeap()
    : _root(nullptr)
    , _size(0)
{}

template<typename T>
ListHeap<T>::~ListHeap()
{
    clear();
}

template<typename T>
std::shared_ptr<typename ListHeap<T>::Node> ListHeap<T>::getLastNode()
{
    if (empty()) {
        return nullptr;
    }

    std::queue<std::shared_ptr<Node>> queue;
    queue.push(_root);
    std::shared_ptr<Node> lastNode;

    while (!queue.empty()) {
        lastNode = queue.front();
        queue.pop();

        if (lastNode->left) {
            queue.push(lastNode->left);
        }

        if (lastNode->right) {
            queue.push(lastNode->right);
        }
    }

    return lastNode;
}

template<typename T>
void ListHeap<T>::removeLastNode()
{
    if (empty()) {
        return;
    }

    auto lastNode = getLastNode();
    auto parent = lastNode->parent.lock();

    if (parent) {
        if (parent->left == lastNode) {
            parent->left = nullptr;
        } else if (parent->right == lastNode) {
            parent->right = nullptr;
        }
    }

    --_size;
}

template<typename T>
void ListHeap<T>::sift_up(std::shared_ptr<Node> node)
{
    while (node->parent.lock() && node->value > node->parent.lock()->value) {
        std::swap(node->value, node->parent.lock()->value);
        node = node->parent.lock();
    }
}

template<typename T>
void ListHeap<T>::sift_down(std::shared_ptr<Node> node)
{
    while (true) {
        auto left = node->left;
        auto right = node->right;
        auto largest = node;

        if (left && left->value > largest->value) {
            largest = left;
        }

        if (right && right->value > largest->value) {
            largest = right;
        }

        if (largest != node) {
            std::swap(node->value, largest->value);
            node = largest;
        } else {
            break;
        }
    }
}

template<typename T>
void ListHeap<T>::clear()
{
    _root.reset();
    _size = 0;
}

template<typename T>
void ListHeap<T>::push(T value)
{
    auto newNode = std::make_shared<Node>(value);
    if (empty()) {
        _root = newNode;
    } else {
        std::queue<std::shared_ptr<Node>> q;
        q.push(_root);
        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            if (!current->left) {
                current->left = newNode;
                newNode->parent = current;
                break;
            } else if (!current->right) {
                current->right = newNode;
                newNode->parent = current;
                break;
            } else {
                q.push(current->left);
                q.push(current->right);
            }
        }
    }
    ++_size;
    sift_up(newNode);
}

template<typename T>
T ListHeap<T>::pop()
{
    if (empty()) {
        throw std::out_of_range("Heap is empty");
    }

    T maxValue = _root->value;
    auto lastNode = getLastNode();
    if (_root == lastNode) {
        _root = nullptr;
        --_size;
    } else {
        _root->value = lastNode->value;
        removeLastNode();
        sift_down(_root);
    }

    return maxValue;
}

template<typename T>
T &ListHeap<T>::max()
{
    if (empty()) {
        throw std::out_of_range("Heap is empty");
    }

    return _root->value;
}

template<typename T>
size_t ListHeap<T>::size()
{
    return _size;
}

template<typename T>
bool ListHeap<T>::empty()
{
    return _size == 0;
}

template class ListHeap<int32_t>;
