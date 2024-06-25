#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <memory>
#include <QString>

class NewString {
 public:
  //конструкторы
  NewString();
  explicit NewString(const char* str);

  // конструктор копирования
  NewString(const NewString& secondStr);
  // конструктор перемещения
  NewString(NewString&& other) noexcept;

  NewString& operator=(const NewString& secondStr);
  NewString& operator=(const char* str);
  NewString& operator=(const QString& str);

  // деструктор
  ~NewString();

  size_t length() const;

  char& operator[](size_t index);

  char* begin() const;

  char* end() const;

  void* memcpy(void* s1, const void* s2, size_t n);

  void* memmove(void* s1, const void* s2, size_t n);

  char* strcpy(char* s1, const char* s2);

  char* strncpy(char* s1, const char* s2, size_t n);

  char* strcat(char* s1, const char* s2);

  char* strncat(char* s1, const char* s2, size_t n);

  int memcmp(const void* s1, const void* s2, size_t n);

  int strcmp(const char* s1, const char* s2);

  int strcoll(const char* s1, const char* s2);

  int strncmp(const char* s1, const char* s2, size_t n);

  size_t strxfrm(char* s1, const char* s2, size_t n);

  char* strtok(char* s1, const char* s2);

  void* memset(void* s, char c, size_t n);

  char* strerror(int errnum);

  char* strchr(const char* str, int c);

  size_t strlen(const char* s);

  friend std::ostream& operator<<(std::ostream& os, const NewString& str);

  std::unique_ptr<char[]> data;

 private:
  size_t size;
};

#endif  // STRING_H
