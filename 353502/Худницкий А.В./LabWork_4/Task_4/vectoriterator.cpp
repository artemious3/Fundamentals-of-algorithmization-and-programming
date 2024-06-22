#include "vectoriterator.h""

template <typename T>
VectorIterator<T> Vector<T>::begin() {
    return VectorIterator<T>(m_data);
}

template <typename T>
VectorIterator<T> Vector<T>::end() {
    return VectorIterator<T>(m_data + m_size);
}
