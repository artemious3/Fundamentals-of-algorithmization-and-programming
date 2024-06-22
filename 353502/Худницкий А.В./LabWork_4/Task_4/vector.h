#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include "vectoriterator.h"

template<typename T>
class Vector {
public:
    Vector();
    explicit Vector(size_t size);
    Vector(size_t size, const T& value);
    ~Vector();

    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other) noexcept;
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other) noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    VectorIterator<T> begin() noexcept;
    const VectorIterator<T> cbegin() const noexcept;
    VectorIterator<T> end() noexcept;
    const VectorIterator<T> cend() const noexcept;

    T& at(size_t index);
    const T& at(size_t index) const;

    T& back();
    const T& back() const;

    T& front();
    const T& front() const;

    void assign(const T* first, const T* last);
    void assign(size_t count, const T& value);

    T* data() noexcept;
    const T* data() const noexcept;

    void resize(size_t count, const T& value);
    void reserve(size_t new_capacity);
    void emplace_back(const T& value);
    void pop_back();
    void push_back(const T& value);
    void clear() noexcept;
    void insert(size_t pos, const T& value);
    void insert(size_t pos, size_t count, const T& value);
    void erase(size_t pos);
    void erase(size_t first, size_t last);

    size_t max_size() const noexcept;

    T* rbegin() noexcept;
    const T* crbegin() const noexcept;
    T* rend() noexcept;
    const T* crend() const noexcept;

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void increase_capacity();
    void destroy_elements();
};

#endif // VECTOR_H
