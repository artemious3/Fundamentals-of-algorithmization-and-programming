#ifndef VECTORITERATOR_H
#define VECTORITERATOR_H

template<typename T>
class VectorIterator {
public:
    VectorIterator(T* ptr) : m_ptr(ptr) {}

    T& operator*() const {
        return *m_ptr;
    }

    VectorIterator<T>& operator++() {
        ++m_ptr;
        return *this;
    }

    bool operator!=(const VectorIterator<T>& other) const {
        return m_ptr != other.m_ptr;
    }

private:
    T* m_ptr;
};

#endif // VECTORITERATOR_H
