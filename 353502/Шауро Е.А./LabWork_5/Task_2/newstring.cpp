#include "newstring.h"
#include <cstring>

NewString::NewString() : data(nullptr), size(0) {}

NewString::NewString(const char* str) {
  size = strlen(str);
  data = std::unique_ptr<char[]>(new char[size + 1]);
  strncpy(
      data.get(), str,
      size);  //data.get() - указатель на управляемый std::unique_ptr объектом.
}

// Конструктор копирования
NewString::NewString(const NewString& secondStr) : size(secondStr.length()) {
  data = std::unique_ptr<char[]>(new char[size + 1]);
  strncpy(data.get(), secondStr.data.get(), size);
}

NewString::NewString(NewString&& other) noexcept
    : data(std::move(other.data)), size(std::move(other.size)) {
  other.data = nullptr;
  other.size = 0;
}

NewString& NewString::operator=(const NewString& secondStr) {
  if (this != &secondStr) {
    size = secondStr.size;
    data = std::unique_ptr<char[]>(new char[size + 1]);
    strncpy(data.get(), secondStr.data.get(), size);
  }
  return *this;
}

NewString& NewString::operator=(const char* str) {
  size_t newLength = strlen(str);
  std::unique_ptr<char[]> newData =
      std::unique_ptr<char[]>(new char[newLength + 1]);

  strncpy(newData.get(), str, newLength);
  data = std::move(newData);
  size = newLength;

  return *this;
}

NewString& NewString::operator=(const QString& str) {
  QByteArray byteArray = str.toUtf8();
  size_t newLength = byteArray.size();
  std::unique_ptr<char[]> newData =
      std::unique_ptr<char[]>(new char[newLength + 1]);

  strncpy(newData.get(), byteArray.constData(), newLength);
  newData[newLength] = '\0';

  data = std::move(newData);
  size = newLength;

  return *this;
}

NewString::~NewString() = default;

size_t NewString::length() const {
  return size;
}

char& NewString::operator[](size_t index) {
  return data[index];
}

char* NewString::begin() const {
  return data.get();
}

char* NewString::end() const {
  return data.get() + size;
}

void* NewString::memcpy(void* s1, const void* s2, size_t n) {
  if (s1 == nullptr || s2 == nullptr) {
    return s1;
  }
  char* place = static_cast<char*>(s1);  // привидение типа указателей
  const char* source = static_cast<const char*>(s2);

  size_t min_length = std::min(strlen(place), n);

  for (size_t i = 0; i < min_length; ++i) {
    place[i] = source[i];
  }

  return s1;
}

void* NewString::memmove(void* s1, const void* s2, size_t n) {
  if (s1 == nullptr || s2 == nullptr) {
    return s1;
  }
  char* place = static_cast<char*>(s1);
  const char* source = static_cast<const char*>(s2);

  // Проверяем, не перекрываются ли области памяти
  if (place <= source || place >= source + n) {
    memcpy(s1, s2, n);
  } else {

    for (size_t i = n; i > 0; --i) {
      place[i - 1] = source[i - 1];
    }
  }
  return s1;
}

char* NewString::strcpy(char* s1, const char* s2) {
  if (s1 == nullptr || s2 == nullptr) {
    return s1;
  }
  int i = 0;
  while (s2[i] != '\0') {
    ++i;
  }
  memcpy(s1, s2, i);
  s1[i] = '\0';
  return s1;
}

char* NewString::strncpy(char* s1, const char* s2, size_t size) {

  if (s1 == nullptr || s2 == nullptr) {
    return s1;
  }

  size_t i = 0;
  for (; i < size && s2[i] != '\0'; ++i) {
    s1[i] = s2[i];
  }

  for (; i < size; ++i) {
    s1[i] = '\0';
  }
  return s1;
}

// слияние двух строк
char* NewString::strcat(char* s1, const char* s2) {
  if (s1 == nullptr || s2 == nullptr) {
    return s1;
  }

  char* end = s1;
  while (*end != '\0') {
    ++end;
  }

  while (*s2 != '\0') {
    *end = *s2;
    ++end;
    ++s2;
  }
  *end = '\0';
  return s1;
}

char* NewString::strncat(char* s1, const char* s2, size_t n) {
  if (s1 == nullptr || s2 == nullptr) {
    return s1;
  }
  char* end = s1;
  while (*end != '\0') {
    ++end;
  }

  size_t i;
  for (i = 0; i < n && s2[i] != '\0'; ++i) {
    end[i] = s2[i];
  }

  end[i] = '\0';
  return s1;
}

int NewString::memcmp(const void* s1, const void* s2, size_t n) {
  const char* p1 = static_cast<const char*>(s1);
  const char* p2 = static_cast<const char*>(s2);

  for (size_t i = 0; i < n; ++i) {
    if (p1[i] < p2[i]) {
      return -1;
    } else if (p1[i] > p2[i]) {
      return 1;
    }
  }
  return 0;
}

int NewString::strcmp(const char* s1, const char* s2) {
  while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

int NewString::strncmp(const char* s1, const char* s2, size_t n) {
  while (n > 0) {
    // Если одна из строк закончилась, а другая еще нет, то это будет отражаться на значениях символов
    if (*s1 == '\0' || *s2 == '\0') {
      return *s1 - *s2;
    }
    // Сравниваем символы и переходим к следующим
    if (*s1 != *s2) {
      return *s1 - *s2;
    }
    s1++;
    s2++;
    n--;
  }
  return 0;
}

// сравнение строк в соответствии с локалью
int NewString::strcoll(const char* s1, const char* s2) {

  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }
    s1++;
    s2++;
  }

  if (*s1 == '\0' && *s2 == '\0') {
    return 0;
  } else if (*s1 == '\0') {
    return -1;
  } else {
    return 1;
  }
}

size_t NewString::strxfrm(char* s1, const char* s2, size_t n) {
  size_t s2_len = strlen(s2);

  if (n <= s2_len) {
    return s2_len;
  }

  strncpy(s1, s2, s2_len);
  return s2_len;
}

char* NewString::strchr(const char* str, int c) {
  while (*str != '\0') {
    if (*str == c) {
      return (char*)str;
    }
    ++str;
  }
  return nullptr;
}

char* NewString::strtok(char* s1, const char* s2) {
  static char* last = nullptr;
  char* start;
  const char* delimiters = s2;

  if (s1 != nullptr) {
    last = s1;
  }

  if (last == nullptr || *last == '\0') {
    return nullptr;
  }

  while (*last != '\0' && NewString::strchr(delimiters, *last) != nullptr) {
    last++;
  }

  if (*last == '\0') {
    last = nullptr;
    return nullptr;
  }
  start = last;

  while (*last != '\0' && NewString::strchr(delimiters, *last) == nullptr) {
    last++;
  }

  if (*last == '\0') {
    last = nullptr;
  } else {
    *last = '\0';
    last++;
  }

  return start;
}

void* NewString::memset(void* s, char c, size_t n) {
  unsigned char* p = static_cast<unsigned char*>(s);

  for (size_t i = 0; i < n; ++i) {
    p[i] = c;
  }
  return s;
}

char* NewString::strerror(int errnum) {
  static char* errorMessages[] = {
      "No error",
      "Operation not permitted",
      "No such file or directory",
      "Invalid argument",
  };

  if (errnum < 0 ||
      errnum >= sizeof(errorMessages) / sizeof(errorMessages[0])) {
    return "Unknown error";
  }
  return errorMessages[errnum];
}

size_t NewString::strlen(const char* s) {
  int count = 0;
  while (*s != '\0') {
    ++s;
    ++count;
  }
  return count;
}

std::ostream& operator<<(std::ostream& os, const NewString& str) {
  os << str.data.get();
  return os;
}
