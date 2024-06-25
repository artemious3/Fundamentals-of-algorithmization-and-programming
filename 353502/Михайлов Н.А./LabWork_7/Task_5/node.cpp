#include "node.h"
#include <cstdlib>

template <typename T>
Node<T>::Node()
{
    count = 0;
    data = (T*)malloc(sizeof(T) * 4);
}
