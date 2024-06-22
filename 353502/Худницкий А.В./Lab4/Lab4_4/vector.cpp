#include "vector.h"
#include "vectoriterator.h"
#include <limits>
#include <stdexcept>

template<typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template<typename T>
Vector<T>::Vector(size_t size) : m_size(size), m_capacity(size) {
    m_data = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = T();
    }
}

template<typename T>
Vector<T>::Vector(size_t size, const T& value) : m_size(size), m_capacity(size) {
    m_data = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = value;
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] m_data;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
    m_data = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Vector::operator[] - index out of range");
    }
    return m_data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Vector::operator[] - index out of range");
    }
    return m_data[index];
}

template<typename T>
size_t Vector<T>::size() const noexcept {
    return m_size;
}

template<typename T>
size_t Vector<T>::capacity() const noexcept {
    return m_capacity;
}

template<typename T>
bool Vector<T>::empty() const noexcept {
    return m_size == 0;
}

template<typename T>
void  Vector<T>::clear() noexcept {
    m_size = 0;
}

template<typename T>
VectorIterator<T> Vector<T>::begin() noexcept {
    return VectorIterator<T>(m_data);
}

template<typename T>
const VectorIterator<T> Vector<T>::cbegin() const noexcept {
    return VectorIterator<T>(m_data);
}

template<typename T>
VectorIterator<T> Vector<T>::end() noexcept {
    return VectorIterator<T>(m_data + m_size);
}

template<typename T>
const VectorIterator<T> Vector<T>::cend() const noexcept {
    return VectorIterator<T>(m_data + m_size);
}

template<typename T>
void Vector<T>::resize(size_t count, const T& value) {
    if (count <= m_size) {
        m_size = count;
    } else {
        reserve(count);
        for (size_t i = m_size; i < count; ++i) {
            m_data[i] = value;
        }
        m_size = count;
    }
}

template<typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > m_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
}

template<typename T>
void Vector<T>::emplace_back(const T& value) {
    if (m_size == m_capacity) {
        increase_capacity();
    }
    m_data[m_size++] = value;
}

template<typename T>
void Vector<T>::pop_back() {
    if (m_size > 0) {
        --m_size;
    }
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    emplace_back(value);
}

template<typename T>
void Vector<T>::insert(size_t pos, const T& value) {
    insert(pos, 1, value);
}

template<typename T>
void Vector<T>::insert(size_t pos, size_t count, const T& value) {
    if (pos > m_size) {
        return;
    }
    if (m_size + count > m_capacity) {
        reserve(m_size + count);
    }
    for (size_t i = m_size; i > pos; --i) {
        m_data[i + count - 1] = m_data[i - 1];
    }
    for (size_t i = pos; i < pos + count; ++i) {
        m_data[i] = value;
    }
    m_size += count;
}

template<typename T>
void Vector<T>::erase(size_t pos) {
    erase(pos, pos + 1);
}

template<typename T>
void Vector<T>::erase(size_t first, size_t last) {
    if (first >= m_size || first >= last) {
        return;
    }
    if (last > m_size) {
        last = m_size;
    }
    size_t count = last - first;
    for (size_t i = first; i < m_size - count; ++i) {
        m_data[i] = m_data[i + count];
    }
    m_size -= count;
}

template<typename T>
size_t Vector<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template<typename T>
T* Vector<T>::rbegin() noexcept {
    return m_data + m_size - 1;
}

template<typename T>
const T* Vector<T>::crbegin() const noexcept {
    return m_data + m_size - 1;
}

template<typename T>
T* Vector<T>::rend() noexcept {
    return m_data - 1;
}

template<typename T>
const T* Vector<T>::crend() const noexcept {
    return m_data - 1;
}

template<typename T>
void Vector<T>::increase_capacity() {
    size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
    reserve(new_capacity);
}

template<typename T>
void Vector<T>::destroy_elements() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template class Vector<int>;
template class Vector<double>;

