#ifndef NEWVECTOR_H
#define NEWVECTOR_H

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>

template <typename T>
class NewVector {

 public:
  class Iterator {

   public:
    using difference_type = std::ptrdiff_t;  // Тип для арифметики итераторов

    Iterator(T* ptr) : m_ptr(ptr) {}

    T& operator*() const { return *m_ptr; }

    T* operator->() { return m_ptr; }

    // Оператор вычитания итераторов
    difference_type operator-(const Iterator& other) const {
      return m_ptr - other.m_ptr;
    }

    Iterator operator+(difference_type n) const { return Iterator(m_ptr + n); }

    Iterator operator-(difference_type n) const { return Iterator(m_ptr - n); }

   private:
    T* m_ptr;
  };

  NewVector();
  explicit NewVector(std::size_t size);
  NewVector(std::initializer_list<T> init);
  ~NewVector();  // Деструктор

  void assign(std::initializer_list<T> init);
  T& at(std::size_t pos);
  T& back();
  Iterator begin();
  std::size_t capacity() const;  // Возвращает текущую вместимость
  Iterator cbegin() const;  // Возвращает константный итератор на начало
  void clear();
  T* data();
  void emplace(Iterator pos, T&& value);
  void emplace_back(T&& value);
  bool empty() const;
  Iterator end();
  void erase(Iterator pos);
  T& front();
  void insert(Iterator pos, const T& value);
  std::size_t max_size() const;
  void pop_back();
  void push_back(const T& value);
  Iterator rbegin();
  Iterator rend();
  void reserve(std::size_t new_cap);
  void resize(std::size_t newSize);
  std::size_t size() const;
  void swap(NewVector& other);

 private:
  T* m_data;  // Указатель на внутренние данные
  std::size_t m_size;
  std::size_t m_capacity;

  void reallocate(std::size_t new_cap);
};

template <typename T>
NewVector<T>::NewVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
NewVector<T>::NewVector(std::size_t size) : m_size(size), m_capacity(size) {
  m_data = new T[size];
}

template <typename T>
NewVector<T>::NewVector(std::initializer_list<T> init)
    : NewVector(init.size()) {
  std::copy(init.begin(), init.end(), m_data);
}

template <typename T>
NewVector<T>::~NewVector() {
  delete[] m_data;
}

template <typename T>
void NewVector<T>::assign(std::initializer_list<T> init) {
  clear();
  reserve(init.size());
  std::copy(init.begin(), init.end(), m_data);
  m_size = init.size();
}

template <typename T>
T& NewVector<T>::at(std::size_t pos) {
  if (pos >= m_size) {
    throw std::out_of_range("Индекс вне диапазона");
  }
  return m_data[pos];
}

template <typename T>
T& NewVector<T>::back() {
  if (empty()) {
    throw std::out_of_range("Вектор пуст");
  }
  return m_data[m_size - 1];
}

template <typename T>
typename NewVector<T>::Iterator NewVector<T>::begin() {
  return Iterator(m_data);
}

template <typename T>
typename NewVector<T>::Iterator NewVector<T>::cbegin() const {
  return Iterator(m_data);
}

template <typename T>
void NewVector<T>::clear() {
  delete[] m_data;
  m_data = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <typename T>
T* NewVector<T>::data() {
  return m_data;
}

template <typename T>
void NewVector<T>::emplace(Iterator pos, T&& value) {
  auto index = pos - begin();  // Вычисляем индекс позиции
  if (m_size >= m_capacity) {
    reserve(m_capacity ? m_capacity * 2 : 1);
  }
  for (auto i = m_size; i > index; --i) {
    m_data[i] = std::move(m_data[i - 1]);
  }
  m_data[index] = std::move(value);  // Вставляем новый элемент
  ++m_size;
}

template <typename T>
void NewVector<T>::emplace_back(T&& value) {
  if (m_size >= m_capacity) {
    reserve(m_capacity ? m_capacity * 2 : 1);
  }
  m_data[m_size++] =
      std::move(value);  // Вставляем новый элемент и увеличиваем размер
}

template <typename T>
bool NewVector<T>::empty() const {
  return m_size == 0;
}

template <typename T>
typename NewVector<T>::Iterator NewVector<T>::end() {
  return Iterator(m_data + m_size);
}

template <typename T>
void NewVector<T>::erase(Iterator pos) {
  if (empty()) {
    throw std::out_of_range("Вектор пуст");
  }
  auto index = pos - begin();
  for (auto i = index; i < m_size - 1; ++i) {
    m_data[i] = std::move(m_data[i + 1]);
  }
  --m_size;
}

template <typename T>
T& NewVector<T>::front() {
  if (empty()) {
    throw std::out_of_range("Вектор пуст");
  }
  return m_data[0];
}

template <typename T>
void NewVector<T>::insert(Iterator pos, const T& value) {
  emplace(pos, T(value));
}

template <typename T>
std::size_t NewVector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

// Удаление последнего элемента
template <typename T>
void NewVector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Вектор пуст");
  }
  --m_size;
}

template <typename T>
void NewVector<T>::push_back(const T& value) {
  if (m_size >= m_capacity) {
    reserve(m_capacity ? m_capacity * 2 : 1);
  }
  m_data[m_size++] = value;  // Вставляем новый элемент и увеличиваем размер
}


template <typename T>
typename NewVector<T>::Iterator NewVector<T>::rbegin() {
  return Iterator(m_data + m_size - 1);
}

template <typename T>
typename NewVector<T>::Iterator NewVector<T>::rend() {
  return Iterator(m_data - 1);
}

template <typename T>
void NewVector<T>::reserve(std::size_t newCap) {
  if (newCap > m_capacity) {
    reallocate(newCap);
  }
}

template <typename T>
void NewVector<T>::resize(std::size_t newSize) {
  if (newSize > m_capacity)
    reserve(newSize);  // Резервируем память при необходимости
  m_size = newSize;
}

// Возвращает текущий размер
template <typename T>
std::size_t NewVector<T>::size() const {
  return m_size;
}

template <typename T>
void NewVector<T>::swap(NewVector& other) {
  std::swap(m_data, other.m_data);  // Обмениваемся указателями на данные
  std::swap(m_size, other.m_size);
  std::swap(m_capacity, other.m_capacity);
}

template <typename T>
std::size_t NewVector<T>::capacity() const {
  return m_capacity;
}

template <typename T>
void NewVector<T>::reallocate(std::size_t new_cap) {
  T* new_data = new T[new_cap];
  for (std::size_t i = 0; i < m_size; ++i) {
    new_data[i] =
        std::move(m_data[i]);
  }
  delete[] m_data;
  m_data = new_data;
  m_capacity = new_cap;
}

#endif  // NEWVECTOR_H
