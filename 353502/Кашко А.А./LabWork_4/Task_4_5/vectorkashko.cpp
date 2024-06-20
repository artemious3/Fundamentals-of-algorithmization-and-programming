#include "vectorkashko.h"
/*#include <algorithm> // Подключение для std::copy

template<typename T>
vectorKashko<T>::vectorKashko() : m_data(nullptr), m_size(0), m_capacity(0) {}

template<typename T>
vectorKashko<T>::vectorKashko(std::size_t size) : m_size(size), m_capacity(size) {
    m_data = new T[size];
}

template<typename T>
vectorKashko<T>::vectorKashko(std::initializer_list<T> init) : vectorKashko(init.size()) {
    std::copy(init.begin(), init.end(), m_data);
}

template<typename T>
vectorKashko<T>::~vectorKashko() {
    delete[] m_data;
}

template<typename T>
void vectorKashko<T>::assign(std::initializer_list<T> init) {
    clear();
    reserve(init.size());
    std::copy(init.begin(), init.end(), m_data);
    m_size = init.size();
}

template<typename T>
T& vectorKashko<T>::at(std::size_t pos) {
    if (pos >= m_size) throw std::out_of_range("Index out of range");
    return m_data[pos];
}

template<typename T>
const T& vectorKashko<T>::at(std::size_t pos) const {
    if (pos >= m_size) throw std::out_of_range("Index out of range");
    return m_data[pos];
}

template<typename T>
T& vectorKashko<T>::back() {
    if (empty()) throw std::out_of_range("Vector is empty");
    return m_data[m_size - 1];
}

template<typename T>
const T& vectorKashko<T>::back() const {
    if (empty()) throw std::out_of_range("Vector is empty");
    return m_data[m_size - 1];
}

template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::begin() {
    return Iterator(m_data);
}

template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::cbegin() const {
    return Iterator(m_data);
}

template<typename T>
void vectorKashko<T>::clear() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template<typename T>
T* vectorKashko<T>::data() {
    return m_data;
}

template<typename T>
void vectorKashko<T>::emplace(Iterator pos, T&& value) {
    auto index = pos - begin();
    if (m_size >= m_capacity) reserve(m_capacity ? m_capacity * 2 : 1);
    for (auto i = m_size; i > index; --i) m_data[i] = std::move(m_data[i - 1]);
    m_data[index] = std::move(value);
    ++m_size;
}

template<typename T>
void vectorKashko<T>::emplace_back(T&& value) {
    if (m_size >= m_capacity) reserve(m_capacity ? m_capacity * 2 : 1);
    m_data[m_size++] = std::move(value);
}

template<typename T>
bool vectorKashko<T>::empty() const {
    return m_size == 0;
}

template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::end() {
    return Iterator(m_data + m_size);
}

template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::cend() const {
    return Iterator(m_data + m_size);
}

template<typename T>
void vectorKashko<T>::erase(Iterator pos) {
    auto index = pos - begin();
    for (auto i = index; i < m_size - 1; ++i) m_data[i] = std::move(m_data[i + 1]);
    --m_size;
}

template<typename T>
T& vectorKashko<T>::front() {
    if (empty()) throw std::out_of_range("Vector is empty");
    return m_data[0];
}

template<typename T>
const T& vectorKashko<T>::front() const {
    if (empty()) throw std::out_of_range("Vector is empty");
    return m_data[0];
}

template<typename T>
void vectorKashko<T>::insert(Iterator pos, const T& value) {
    emplace(pos, T(value));
}

template<typename T>
std::size_t vectorKashko<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
void vectorKashko<T>::pop_back() {
    if (empty()) throw std::out_of_range("Vector is empty");
    --m_size;
}

template<typename T>
void vectorKashko<T>::push_back(const T& value) {
    if (m_size >= m_capacity) reserve(m_capacity ? m_capacity * 2 : 1);
    m_data[m_size++] = value;
}

template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::rbegin() {
    return Iterator(m_data + m_size - 1);
}

template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::rend() {
    return Iterator(m_data - 1);
}

template<typename T>
void vectorKashko<T>::reserve(std::size_t new_cap) {
    if (new_cap > m_capacity) reallocate(new_cap);
}

template<typename T>
void vectorKashko<T>::resize(std::size_t new_size) {
    if (new_size > m_capacity) reserve(new_size);
    m_size = new_size;
}

template<typename T>
std::size_t vectorKashko<T>::size() const {
    return m_size;
}

template<typename T>
void vectorKashko<T>::swap(vectorKashko& other) {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
}

template<typename T>
std::size_t vectorKashko<T>::capacity() const {
    return m_capacity;
}

template<typename T>
void vectorKashko<T>::reallocate(std::size_t new_cap) {
    T* new_data = new T[new_cap];
    for (std::size_t i = 0; i < m_size; ++i) new_data[i] = std::move(m_data[i]);
    delete[] m_data;
    m_data = new_data;
    m_capacity = new_cap;
}*/
