#include "bits.h"

// конструкторы. bits((size + type -1) / type, 0) означает выделение память ( + 63 для округления вверх) и обнуление вектора
Bits::Bits(int size) : type(8), bits((size + 7) / 8, 0), bit_size(size) {}

Bits::Bits(const Bits& other)
    : bits((other.bit_size + type - 1) / type, 0),
      bit_size(other.bit_size),
      type(8) {}

bool Bits::all() {
  for (const auto& bit : bits) {
    if (bit != ~0ULL) {
      return false;
    }
  }
  return true;
}

bool Bits::any() {
  for (const auto& bit : bits) {
    if (bit != 0ULL) {
      return true;
    }
  }
  return false;
}

int Bits::count() {
  int count = 0;
  for (auto bit : bits) {
    while (bit) {
      count += bit & 1;
      bit >>= 1;
    }
  }
  return count;
}

void Bits::flip() {
  int maxElement = bit_size / type;
  int lastBit = bit_size % type;

  for (int index = 0; index <= maxElement - 1; ++index) {
    for (int bit = 0; bit < type; ++bit) {
      bits[index] ^= (1ULL << bit);
    }
  }

  for (int i = 0; i < lastBit; ++i) {
    bits[maxElement] ^= (1ULL << i);
  }
}

void Bits::flip(int index) {
  checkIndex(index);
  size_t element = index / type;
  size_t bit = index % type;
  bits[element] ^= (1ULL << bit);  // 1ULL - единица
}

bool Bits::none() {
  return !any();
}

void Bits::reset() {
  std::fill(bits.begin(), bits.end(), 0);
}

void Bits::reset(int index) {
  checkIndex(index);
  size_t element = index / type;
  size_t bit = index % type;
  bits[element] &= ~(1ULL << bit);
}

int Bits::get(int index) {
  checkIndex(index);
  size_t element = index / type;
  size_t bit = index % type;
  return (bits[element] >> bit) & 1;
}

void Bits::set() {
  std::fill(bits.begin(), bits.end(), ~0ULL);
}

void Bits::set(int index) {
  checkIndex(index);
  size_t element = index / type;
  size_t bit = index % type;
  bits[element] |= (1ULL << bit);
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
  unsigned long long res = 0;
  for (int i = 0; i < bits.size(); ++i) {
    res = (res << 1) | bits[i];
  }
  return res;
}

unsigned long Bits::to_ulong() {

  unsigned long res = 0;
  for (int i = 0; i < bits.size(); ++i) {
    res = (res << 1) | bits[i];
  }
  return res;
}

bool Bits::operator[](size_t index) {
  checkIndex(index);
  size_t element = index / type;
  size_t bit = index % type;
  return (bits[element] & (1ULL << bit)) != 0;
}

void Bits::setType(int value) {
  type = value;
}
