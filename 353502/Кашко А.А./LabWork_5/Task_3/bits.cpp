#include "bits.h"


// конструкторы. bits((size + type -1) / type, 0) означает выделение память ( + 63 для округления вверх) и обнуление вектора
Bits::Bits(int size) : type(64), bits((size + 63) / 64, 0), bit_size(size) {

}

Bits::Bits(const Bits& other)
    : bits((other.bit_size + type - 1) / type, 0), bit_size(other.bit_size), type(16) {}

bool Bits::all() {
    for (const auto& block : bits) {
        if (block != ~0ULL){ //Здесь ~0ULL представляет собой битовое отрицание нуля для 64-битного
            //типа данных (ULL обозначает unsigned long long).
            //Если block содержит все единицы, то битовое отрицание нуля приведет к значению,
            //где все биты установлены в 1, что и будет равно block.
            return false;
        }
    }
    return true;
}

bool Bits::any() {
    for (const auto& block : bits) {
        if (block != 0){
            return true;
        }
    }
    return false;
}

int Bits::count() {
    int count = 0;
    for (auto block : bits) {
        while (block) {
            count += block & 1;
            block >>= 1;
        }
    }
    return count;
}

void Bits::flip() {
    for (auto& block : bits) {
        block = ~block;
    }
}

void Bits::flip(int index) {
    checkIndex(index);
    size_t element = index / type;
    size_t bit = index % type;
    bits[element] ^= (1ULL << bit);/*    1ULL << bit: Это создает маску, в которой только один бит установлен в единицу,
 а все остальные биты равны нулю. Оператор << выполняет побитовый сдвиг влево на значение bit.
 Например, если bit равен 3, то результатом будет число, в котором третий бит считая справа
 установлен в 1 (00001000 в двоичном представлении).
    bits[element] ^= (1ULL << bit): Это операция исключающего ИЛИ с присваиванием (^=). Она выполняет побитовую операцию
 исключающего ИЛИ между значением bits[element] и маской, созданной выше. Это приводит к инвертированию бита по индексу bit в bits[element].*/
}

bool Bits::none() {
    return !any();
}

void Bits::reset() {
    std::fill(bits.begin(), bits.end(), 0);
}

void Bits::reset(int index) {
    checkIndex(index);
    size_t element = index / type; // Определяем индекс блока
    size_t bit = index % type; // Определяем смещение внутри блока
    bits[element] &= ~(1ULL << bit); // Устанавливаем бит в нуль, инвертируя маску и выполняя побитовое И с текущим значением
}

int Bits::get(int index) {
    checkIndex(index);
    size_t element = index / type;
    size_t bit = index % type;
    return (bits[element] >> bit) & 1; /*    bits[element] - это доступ к элементу массива bits,
 который представляет собой блок данных, содержащий биты. element - это индекс этого блока.
 >> bit - это операция сдвига вправо. Она сдвигает биты в значении bits[element] на bit позиций вправо.
 После этого самый младший бит, который мы хотим прочитать, будет находиться в крайнем правом (наименьшем) бите этого значения.
 & 1 - это побитовая операция "И" с маской, равной единице. Это применяется для извлечения наименьшего бита после сдвига.
 Если наименьший бит равен 1, результат будет 1, иначе - 0.*/
}

void Bits::set() {
    std::fill(bits.begin(), bits.end(), ~0ULL);
}

void Bits::set(int index) {
    checkIndex(index);
    size_t element = index / type; // Находим индекс элемента массива bits, в котором находится нужный бит
    size_t bit = index % type; // Находим смещение бита внутри этого элемента
    bits[element] |= (1ULL << bit);  // Устанавливаем бит в 1 путем побитовой операции ИЛИ с маской, сдвинутой в нужную позицию
}

void Bits::checkIndex(int index) {
    if (index >= bit_size) {
        throw std::out_of_range("Index out of range");
    }
}

bool Bits::test(int index) {
    return get(index);
}

size_t Bits::getSize() const {
    return bit_size;
}

QString Bits::to_string() {
    QString str;
    for (size_t i = 0; i < bit_size; ++i) {
        str.insert(0, get(i) ? '1' : '0');
    }
    return str;
}

unsigned long long Bits::to_ullong() {
    if (bit_size > type) {
        throw std::overflow_error(
            "BitSet too large to convert to unsigned long long");
    }
    return bits[0];
}

unsigned long Bits::to_ulong() {
    if (bit_size > type / 2) {
        throw std::overflow_error("BitSet too large to convert to unsigned long");
    }
    return static_cast<unsigned long>(bits[0]);
}

bool Bits::operator[](size_t index) {
    checkIndex(index);
    size_t element = index / type;
    size_t bit = index % type;
    return (bits[element] & (1ULL << bit)) != 0;
}

void Bits::setType(int value)
{
    type = value;
}
