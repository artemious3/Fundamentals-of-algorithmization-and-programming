#include <cstddef>
#include <utility>

template <typename T> class Dequeue {
    friend class InspectorGadget; // Дружественный класс для доступа к приватным членам

private:
    static const size_t INI_BLOCKS = 4; // Начальное количество блоков
    static const size_t BLOCK_SIZE = 4; // Размер блока

    struct Block {
        T els[BLOCK_SIZE]; // Структура блока для хранения элементов
    };

    void init(size_t count) {
        blocks_count = count; // Установка начального количества блоков
        blocks = new Block *[count]; // Выделение памяти под указатели на блоки
        for (int i = 0; i < count; i++) {
            blocks[i] = (Block *)new unsigned char[sizeof(Block)]; // Выделение памяти под блоки данных
        }

        _begin = 0; // Инициализация индекса начала
        _end = 0; // Инициализация индекса конца
    }

public:
    Dequeue() { init(INI_BLOCKS); } // Конструктор по умолчанию

    ~Dequeue() {
        clear(); // Очистка очереди
        delete[] (unsigned char *)blocks; // Освобождение памяти, выделенной для блоков
    }

    Dequeue(const Dequeue &d) {
        init(d.blocks_count); // Конструктор копирования

        for (size_t i = 0; i < d.size(); i++) {
            push_back(d[i]); // Копирование элементов из другой очереди
        }
    }

    Dequeue &operator=(const Dequeue &d) {
        clear(); // Очистка текущего состояния
        for (size_t i = 0; i < d.size(); i++) {
            push_back(d[i]); // Копирование элементов из другой очереди
        }

        return *this; // Возврат ссылки на текущий объект
    }

    Dequeue(Dequeue &&d) {
        blocks_count = d.blocks_count;
        blocks = d.blocks;
        _begin = d._begin;
        _end = d._end;

        d.init(INI_BLOCKS); // Перемещение конструктор
    }

    Dequeue &operator=(Dequeue &&d) {
        blocks_count = d.blocks_count;
        blocks = d.blocks;
        _begin = d._begin;
        _end = d._end;

        d.init(INI_BLOCKS); // Перемещение оператора присваивания

        return *this; // Возврат ссылки на текущий объект
    }

    T &at(size_t i) {
        i += _begin; // Учет смещения начала очереди
        if (i >= blocks_count * BLOCK_SIZE) // Обработка переполнения индекса
            i -= blocks_count * BLOCK_SIZE;
        return blocks[i / BLOCK_SIZE]->els[i % BLOCK_SIZE]; // Возврат элемента по индексу
    }

    const T &at(size_t i) const {
        i += _begin; // Учет смещения начала очереди
        if (i >= blocks_count * BLOCK_SIZE) // Обработка переполнения индекса
            i -= blocks_count * BLOCK_SIZE;

        return blocks[i / BLOCK_SIZE]->els[i % BLOCK_SIZE]; // Возврат элемента по индексу
    }

    T &operator[](size_t i) { return at(i); } // Перегрузка оператора []

    const T &operator[](size_t i) const { return at(i); } // Перегрузка оператора []

    void push_back(T el) {
        size_t end_pos = _end % BLOCK_SIZE; // Определение позиции в текущем блоке
        if (end_pos == BLOCK_SIZE - 1) { // Если достигнут конец текущего блока
            size_t begin_block = _begin / BLOCK_SIZE; // Номер блока, в котором начинается очередь
            size_t next_block = (_end / BLOCK_SIZE) + 1; // Номер следующего блока
            if (next_block >= blocks_count) // Если следующий блок находится за пределами массива
                next_block -= blocks_count;

            if (begin_block == next_block) // Если следующий блок совпадает с блоком начала очереди
                expand(); // Расширение массива блоков
        }

        new (&blocks[_end / BLOCK_SIZE]->els[_end % BLOCK_SIZE]) T(std::move(el)); // Вставка элемента в конец очереди

        _end++; // Увеличение индекса конца очереди
        if (_end >= blocks_count * BLOCK_SIZE) // Если индекс конца выходит за границы массива
            _end -= blocks_count * BLOCK_SIZE;
    }

    T pop_back() {
        if (_end == 0) { // Если очередь пуста
            _end = blocks_count * BLOCK_SIZE - 1; // Установка индекса конца в последний элемент
        } else {
            _end--; // Уменьшение индекса конца
        }

        T res = std::move(blocks[_end / BLOCK_SIZE]->els[_end % BLOCK_SIZE]); // Извлечение элемента из конца очереди
        blocks[_end / BLOCK_SIZE]->els[_end % BLOCK_SIZE].~T(); // Удаление элемента из блока

        return res; // Возврат извлеченного элемента
    }

    void push_front(T el) {
        size_t begin_pos = _begin % BLOCK_SIZE; // Определение позиции в текущем блоке
        if (begin_pos == 0) { // Если достигнуто начало текущего блока
            size_t end_block = _end / BLOCK_SIZE; // Номер блока, в котором находится конец очереди
            size_t next_block = (_begin / BLOCK_SIZE) - 1; // Номер предыдущего блока
            if (next_block < 0) // Если предыдущий блок находится за пределами массива
                next_block += blocks_count;

            if (end_block == next_block) // Если предыдущий блок совпадает с блоком конца очереди
        expand(); // Расширение массива блоков
        }

        if (_begin == 0) { // Если начало очереди достигло начала массива
            _begin = blocks_count * BLOCK_SIZE - 1; // Установка начала очереди в последний элемент
        } else {
            _begin--; // Уменьшение индекса начала
        }

        new (&blocks[_begin / BLOCK_SIZE]->els[_begin % BLOCK_SIZE]) T(std::move(el)); // Вставка элемента в начало очереди
    }

    T pop_front() {
        T res = std::move(blocks[_begin / BLOCK_SIZE]->els[_begin % BLOCK_SIZE]); // Извлечение элемента из начала очереди
        blocks[_begin / BLOCK_SIZE]->els[_begin % BLOCK_SIZE].~T(); // Удаление элемента из блока

        _begin++; // Увеличение индекса начала очереди
        if (_begin == blocks_count * BLOCK_SIZE) // Если индекс начала выходит за границы массива
            _begin = 0;

        return res; // Возврат извлеченного элемента
    }

    size_t size() const {
        if (_end >= _begin) // Если конец находится после начала
            return _end - _begin; // Размер очереди равен разнице между индексами
        else
            return blocks_count * BLOCK_SIZE + _end - _begin; // Иначе, размер равен сумме индексов и размеру блоков
    }

    bool empty() const { return _end == _begin; } // Проверка, пуста ли очередь

    void clear() {
        while (!empty()) // Пока очередь не пуста
            pop_back(); // Удаляем элементы из конца очереди
    }

private:
    void expand() {
        size_t new_count = blocks_count * 2; // Новое количество блоков
        Block **new_blocks = new Block *[new_count]; // Новый массив блоков

        size_t copy_block = _begin / BLOCK_SIZE; // Начальный блок для копирования
        size_t end_block = _end / BLOCK_SIZE; // Конечный блок для копирования

        for (size_t i = 0; i < blocks_count; i++) {
            new_blocks[i] = blocks[copy_block]; // Копирование блоков

            if (end_block == copy_block) { // Если достигнут конец копирования
                _end = i * BLOCK_SIZE + _end % BLOCK_SIZE; // Обновляем индекс конца
            }

            copy_block++;
            if (copy_block >= blocks_count) {
                copy_block -= blocks_count; // Обновляем индекс для копирования
            }
        }
        _begin %= BLOCK_SIZE; // Обновление индекса начала очереди

        for (size_t i = blocks_count; i < new_count; i++) {
            new_blocks[i] = (Block *)new unsigned char[sizeof(Block)]; // Выделение памяти для новых блоков
        }

        delete[] (unsigned char *)blocks; // Освобождение памяти старых блоков

        blocks_count = new_count; // Обновление количества блоков
        blocks = new_blocks; // Переопределение массива блоков
    }

    Block **blocks; // Массив указателей на блоки
    size_t blocks_count; // Количество блоков

    size_t _begin; // Индекс начала очереди
    size_t _end; // Индекс конца очереди

public:
    class Iterator {
        friend class Dequeue<T>; // Дружественный класс для доступа к приватным членам

    private:
        Dequeue<T> *parent; // Указатель на родительскую очередь
        size_t pos; // Текущая позиция итератора

        Iterator(Dequeue<T> *parent, size_t pos) : parent(parent), pos(pos) {}

    public:
        T &operator*() const { return parent->at(pos); }
        T *operator->() const { return &parent->at(pos); }

        Iterator &operator++() {
            pos++;
            return *this;
        }
        Iterator &operator--() {
            pos--;
            return *this;
        }
        Iterator operator++(int) {
            Iterator res = *this;
            pos++;
            return res;
        }
        Iterator operator--(int) {
            Iterator res = *this;
            pos--;
            return res;
        }

        bool operator==(const Iterator &other) const { return pos == other.pos; }
        bool operator!=(const Iterator &other) const { return pos != other.pos; }

        Iterator operator+=(size_t n) {
            pos += n;
            return *this;
        }
        Iterator operator-=(size_t n) {
            pos -= n;
            return *this;
        }
        Iterator operator+(size_t n) const {
            Iterator res = *this;
            res.pos += n;
            return res;
        }
        Iterator operator-(size_t n) const {
            Iterator res = *this;
            res.pos -= n;
            return res;
        }
    };

    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, size()); }
};

