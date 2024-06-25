#ifndef VECTORKASHKO_H //
#define VECTORKASHKO_H //

#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <limits>

template<typename T>
class vectorKashko {
public:
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag; // Категория итератора
        using difference_type = std::ptrdiff_t; // Тип для арифметики итераторов
        using value_type = T; // Тип значения элементов
        using pointer = T*; // Указатель на элементы
        using reference = T&; // Ссылка на элементы

        // Конструктор итератора
        Iterator(pointer ptr) : m_ptr(ptr) {}

        // Оператор разыменования
        reference operator*() const { return *m_ptr; }
        // Оператор доступа к членам
        pointer operator->() { return m_ptr; }

        // Оператор префиксного инкремента
        Iterator& operator++() { m_ptr++; return *this; }
        // Оператор постфиксного инкремента
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        // Оператор префиксного декремента
        Iterator& operator--() { m_ptr--; return *this; }
        // Оператор постфиксного декремента
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        // Оператор вычитания итераторов
        difference_type operator-(const Iterator& other) const { return m_ptr - other.m_ptr; }
        // Оператор сложения итератора с целым числом
        Iterator operator+(difference_type n) const { return Iterator(m_ptr + n); }
        // Оператор вычитания целого числа из итератора
        Iterator operator-(difference_type n) const { return Iterator(m_ptr - n); }

        // Оператор равенства
        bool operator==(const Iterator& other) const { return m_ptr == other.m_ptr; }
        // Оператор неравенства
        bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }

    private:
        pointer m_ptr; // Указатель на элемент
    };

    // Конструкторы и деструктор
    vectorKashko(); // Конструктор по умолчанию
    explicit vectorKashko(std::size_t size); // Конструктор с заданным размером
    vectorKashko(std::initializer_list<T> init); // Конструктор с инициализатором
    ~vectorKashko(); // Деструктор

    // Методы-члены
    void assign(std::initializer_list<T> init);
    T& at(std::size_t pos);
    T& back();
    Iterator begin();
    Iterator cbegin() const;
    void clear();
    T* data();
    void emplace(Iterator pos, T&& value);
    void emplace_back(T&& value);
    bool empty() const;
    Iterator end();
    Iterator cend() const;
    void erase(Iterator pos);
    T& front();
    void insert(Iterator pos, const T& value);
    std::size_t max_size() const;
    void pop_back();
    void push_back(const T& value);
    Iterator rbegin();
    Iterator rend();
    void reserve(std::size_t new_cap);
    void resize(std::size_t new_size);
    std::size_t size() const;
    void swap(vectorKashko& other);
    std::size_t capacity() const;

private:
    T* m_data; // Указатель на внутренние данные
    std::size_t m_size; // Текущий размер вектора
    std::size_t m_capacity; // Текущая вместимость вектора

    // Вспомогательная функция для перераспределения памяти
    void reallocate(std::size_t new_cap);
};

// Конструктор по умолчанию
template<typename T>
vectorKashko<T>::vectorKashko() : m_data(nullptr), m_size(0), m_capacity(0) {}

// Конструктор с заданным размером
template<typename T>
vectorKashko<T>::vectorKashko(std::size_t size) : m_size(size), m_capacity(size) {
    m_data = new T[size]; // Выделяем память под элементы
}

// Конструктор с инициализатором
template<typename T>
vectorKashko<T>::vectorKashko(std::initializer_list<T> init) : vectorKashko(init.size()) {
    std::copy(init.begin(), init.end(), m_data); // Копируем элементы из списка инициализации
}

// Деструктор
template<typename T>
vectorKashko<T>::~vectorKashko() {
    delete[] m_data; // Освобождаем память
}

// Присвоение элементов из списка инициализации
template<typename T>
void vectorKashko<T>::assign(std::initializer_list<T> init) {
    clear(); // Очищаем текущие данные
    reserve(init.size()); // Резервируем память
    std::copy(init.begin(), init.end(), m_data); // Копируем элементы
    m_size = init.size(); // Устанавливаем новый размер
}

// Доступ к элементу с проверкой границ
template<typename T>
T& vectorKashko<T>::at(std::size_t pos) {
    if (pos >= m_size) throw std::out_of_range("Индекс вне диапазона"); // Проверка границ
    return m_data[pos];
}

// Доступ к последнему элементу
template<typename T>
T& vectorKashko<T>::back() {
    if (empty()) throw std::out_of_range("Вектор пуст"); // Проверка на пустоту
    return m_data[m_size - 1];
}

// Возвращает итератор на начало
template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::begin() {
    return Iterator(m_data);
}

// Возвращает константный итератор на начало
template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::cbegin() const {
    return Iterator(m_data);
}

// Очищает вектор
template<typename T>
void vectorKashko<T>::clear() {
    delete[] m_data; // Освобождаем память
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

// Возвращает указатель на внутренние данные
template<typename T>
T* vectorKashko<T>::data() {
    return m_data;
}

// Вставка элемента на позицию с перемещением
template<typename T>
void vectorKashko<T>::emplace(Iterator pos, T&& value) {
    auto index = pos - begin(); // Вычисляем индекс позиции
    if (m_size >= m_capacity) reserve(m_capacity ? m_capacity * 2 : 1); // Резервируем память при необходимости
    for (auto i = m_size; i > index; --i) m_data[i] = std::move(m_data[i - 1]); // Сдвигаем элементы вправо
    m_data[index] = std::move(value); // Вставляем новый элемент
    ++m_size; // Увеличиваем размер
}

// Вставка элемента в конец с перемещением
template<typename T>
void vectorKashko<T>::emplace_back(T&& value) {
    if (m_size >= m_capacity) reserve(m_capacity ? m_capacity * 2 : 1); // Резервируем память при необходимости
    m_data[m_size++] = std::move(value); // Вставляем новый элемент и увеличиваем размер
}

// Проверка на пустоту
template<typename T>
bool vectorKashko<T>::empty() const {
    return m_size == 0;
}

// Возвращает итератор на конец
template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::end() {
    return Iterator(m_data + m_size);
}

// Возвращает константный итератор на конец
template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::cend() const {
    return Iterator(m_data + m_size);
}

// Удаление элемента на позиции
template<typename T>
void vectorKashko<T>::erase(Iterator pos) {
    auto index = pos - begin(); // Вычисляем индекс позиции
    for (auto i = index; i < m_size - 1; ++i) m_data[i] = std::move(m_data[i + 1]); // Сдвигаем элементы влево
    --m_size; // Уменьшаем размер
}

// Доступ к первому элементу
template<typename T>
T& vectorKashko<T>::front() {
    if (empty()) throw std::out_of_range("Вектор пуст"); // Проверка на пустоту
    return m_data[0];
}

// Вставка элемента на позицию
template<typename T>
void vectorKashko<T>::insert(Iterator pos, const T& value) {
    emplace(pos, T(value)); // Вставляем элемент с использованием перемещения
}

// Возвращает максимальный возможный размер
template<typename T>
std::size_t vectorKashko<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

// Удаление последнего элемента
template<typename T>
void vectorKashko<T>::pop_back() {
    if (empty()) throw std::out_of_range("Вектор пуст"); // Проверка на пустоту
    --m_size; // Уменьшаем размер
}

// Добавление элемента в конец
template<typename T>
void vectorKashko<T>::push_back(const T& value) {
    if (m_size >= m_capacity) reserve(m_capacity ? m_capacity * 2 : 1); // Резервируем память при необходимости
    m_data[m_size++] = value; // Вставляем новый элемент и увеличиваем размер
}

// Возвращает итератор на начало в обратном порядке
template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::rbegin() {
    return Iterator(m_data + m_size - 1);
}

// Возвращает итератор на конец в обратном порядке
template<typename T>
typename vectorKashko<T>::Iterator vectorKashko<T>::rend() {
    return Iterator(m_data - 1);
}

// Резервирование памяти
template<typename T>
void vectorKashko<T>::reserve(std::size_t new_cap) {
    if (new_cap > m_capacity) reallocate(new_cap); // Перераспределяем память, если новый объем больше текущего
}

// Изменение размера
template<typename T>
void vectorKashko<T>::resize(std::size_t new_size) {
    if (new_size > m_capacity) reserve(new_size); // Резервируем память при необходимости
    m_size = new_size; // Устанавливаем новый размер
}

// Возвращает текущий размер
template<typename T>
std::size_t vectorKashko<T>::size() const {
    return m_size;
}

// Обмен содержимым с другим вектором
template<typename T>
void vectorKashko<T>::swap(vectorKashko& other) {
    std::swap(m_data, other.m_data); // Обмениваемся указателями на данные
    std::swap(m_size, other.m_size); // Обмениваемся размерами
    std::swap(m_capacity, other.m_capacity); // Обмениваемся вместимостью
}

// Возвращает текущую вместимость
template<typename T>
std::size_t vectorKashko<T>::capacity() const {
    return m_capacity;
}

// Вспомогательная функция для перераспределения памяти
template<typename T>
void vectorKashko<T>::reallocate(std::size_t new_cap) {
    T* new_data = new T[new_cap]; // Выделяем новую память
    for (std::size_t i = 0; i < m_size; ++i) new_data[i] = std::move(m_data[i]); // Перемещаем старые элементы в новую память
    delete[] m_data; // Освобождаем старую память
    m_data = new_data; // Обновляем указатель на данные
    m_capacity = new_cap; // Обновляем вместимость
}

#endif // VECTORKASHKO_H // Завершаем директиву условной компиляции
