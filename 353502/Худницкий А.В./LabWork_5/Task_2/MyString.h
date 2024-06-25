#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef>
#include <memory>

class MyString {
public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    char* c_str() const;
    int length() const;

    void* memcpy(void* s1, const void* s2, int n);
    void* memmove(void* s1, const void* s2, int n);
    char* strcpy(char* s1, const char* s2);
    char* strncpy(char* s1, const char* s2, int n);
    char* strcat(char* s1, const char* s2);
    char* strncat(char* s1, const char* s2, int n);
    int memcmp(const void* s1, const void* s2, int n);
    int strcmp(const char* s1, const char* s2);
    int strcoll(const char* s1, const char* s2);
    int strncmp(const char* s1, const char* s2, int n);
    int strxfrm(char* s1, const char* s2, int n);
    char* strtok(char* s1, const char* s2);
    void* memset(void* s, int c, int n);
    char* strerror(int errnum);
    int strlen(const char* s);

private:
    std::unique_ptr<char[]> data;
    int len;
};

#endif // MYSTRING_H
