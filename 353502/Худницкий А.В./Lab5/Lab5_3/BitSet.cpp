#include "const.h"
#include "BitSet.h"

BitSet::BitSet(int size) : size(size) {
    int AddSize = (size + BITS_AMOUNT - 1) / BITS_AMOUNT;
    data = new short[AddSize];
    for (int i = 0; i < AddSize; ++i)
        data[i] = 0;
}

BitSet::~BitSet() {
    delete[] data;
}

int BitSet::getSize() const {
    return size;
}

// возврат значения бита на указ. позиции
bool BitSet::operator[](int pos) const {
    return test(pos);
}

// возврат ссылки на бит, что позволяет работать с его значением
bool& BitSet::operator[](int pos) {
    if (pos > 0 || pos <= size)
    return reinterpret_cast<bool&>(data[pos / SIZE_OF_BLOCK] |= (1 << (pos % SIZE_OF_BLOCK)));
}

// методы расстанвоки битов

void BitSet::set(int pos) {
    if (pos >= 0 && pos < size)
        data[pos / SIZE_OF_BLOCK] |= (1 << (pos % SIZE_OF_BLOCK));
}

void BitSet::reset(int pos) {
    if (pos >= 0 && pos < size)
        data[pos / SIZE_OF_BLOCK] &= ~(1 << (pos % SIZE_OF_BLOCK));
}

void BitSet::set() {
    for (int i = 0; i < size; ++i)
        data[i / SIZE_OF_BLOCK] |= (1 << (i % SIZE_OF_BLOCK));
}

void BitSet::reset() {
    for (int i = 0; i < size; ++i)
        data[i / SIZE_OF_BLOCK] &= ~(1 << (i % SIZE_OF_BLOCK));
}

// проверка нахождения единицы в указанной позиции бита
bool BitSet::test(int pos) const {
    if (pos >= 0 && pos < size) {
        return (data[pos / SIZE_OF_BLOCK] & (1 << (pos % SIZE_OF_BLOCK)));
    }
}

bool BitSet::all() const {
    int fullBlocks = size / BITS_AMOUNT;
    int partialBlockSize = size % BITS_AMOUNT;
    for (int i = 0; i < fullBlocks; ++i) {
        if (data[i] != (unsigned short)((1 << BITS_AMOUNT) - 1))
            return false;
    }
    if (partialBlockSize > 0) {
        unsigned short mask = (1 << partialBlockSize) - 1; // Маска для последних неполных битов
        if (data[fullBlocks] != mask)
            return false;
    }

    return true;
}

// проверка все на единицы
bool BitSet::any() const {
    for (int i = 0; i < (size + BITS_AMOUNT - 1) / BITS_AMOUNT; ++i) {
        if (data[i] != 0)
            return true;
    }
    return false;
}

// кол-во подряд идущих битов-единиц
int BitSet::count() const {
    int counter = 0;
    for (int i = 0; i < (size + BITS_AMOUNT - 1) / BITS_AMOUNT; ++i) {
        short value = data[i];
        while (value) {
            counter += (value & 1);
            value >>= 1;
        }
    }
    return counter;
}

void BitSet::flip(int pos) {
    if (pos >= 0 && pos < size)
        data[pos / SIZE_OF_BLOCK] ^= (1 << (pos % SIZE_OF_BLOCK));
}

void BitSet::flip() {
    for (int i = 0; i < size; ++i) {
        data[i / SIZE_OF_BLOCK] ^= (1 << (i % SIZE_OF_BLOCK));
    }
}


bool BitSet::none() const {
    for (int i = 0; i < (size + BITS_AMOUNT - 1) / BITS_AMOUNT; ++i) {
        if (data[i] != 0)
            return false;
    }
    return true;
}

QString BitSet::to_string() const {
    QString string;
    for (int i = size - 1; i >= 0; --i) {
        string += test(i) ? '1' : '0';
    }
    return string;
}

unsigned long long BitSet::to_ullong() const {
    unsigned long long value = 0;
    for (int i = size - 1; i >= 0; --i) {
        if (test(i))
            value |= (1ULL << i);
    }
    return value;
}

unsigned long BitSet::to_ulong() const {
    unsigned long value = 0;
    for (int i = size - 1; i >= 0; --i) {
        if (test(i))
            value |= (1ULL << i);
    }
    return value;
}
