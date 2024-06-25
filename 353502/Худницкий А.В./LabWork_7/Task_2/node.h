#ifndef NODE_H
#define NODE_H


template <typename T, typename U>
class Node {
public:
    Node();
    ~Node();
    Node(T key, U value);
    Node(Node const &node);

    T key;
    U value;
    Node<T, U> *left;
    Node<T, U> *right;
    int height;
    Node<T, U> *parent;
};

#endif // NODE_H
