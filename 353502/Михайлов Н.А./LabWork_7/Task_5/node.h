#ifndef NODE_H
#define NODE_H


template <typename T>
class Node
{
public:
    int count = 0;
    T* data;

    Node();
    ~Node();
};

#endif // NODE_H
