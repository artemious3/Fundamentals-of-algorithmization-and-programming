#include <cstring>
#include "MyString.h"

//создание  пустой строки
MyString::MyString() : data(nullptr), len(0) {}

//создание новой строки на основе с-строки
MyString::MyString(const char* s) {
    if (s) {
        len = strlen(s);
        data = std::make_unique<char[]>(len + 1);
        strcpy(data.get(), s);
    } else {
        len = 0;
        data = nullptr;
    }
}

// конструктор копирования
MyString::MyString(const MyString& other) {
    len = other.len;
    if (other.data) {
        data = std::make_unique<char[]>(len + 1);
        strcpy(data.get(), other.data.get());
    } else {
        data = nullptr;
    }
}

// оператор присваивания
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        len = other.len;
        if (other.data) {
            data = std::make_unique<char[]>(len + 1);
            strcpy(data.get(), other.data.get());
        } else {
            data = nullptr;
        }
    }
    return *this;
}

//деструктор
MyString::~MyString() {}

//возврат строки в формате С-строки
char* MyString::c_str() const {
    return data.get();
}

//возврат длины строки
int MyString::length() const {
    return len;
}

//метод копирует n байт из s1 в s2
void* MyString::memcpy(void* s1, const void* s2, int n) {
    char* dest = static_cast<char*>(s1);
    const char* src = static_cast<const char*>(s2);
    for (int i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
    return s1;
}

//метод безопасно копирует n байт из s1 в s2, поддерживая перекрытие областей
void* MyString::memmove(void* s1, const void* s2, int n) {
    char* dest = static_cast<char*>(s1);
    const char* src = static_cast<const char*>(s2);
    if (dest < src) {
        for (int i = 0; i < n; ++i) {
            dest[i] = src[i];
        }
    } else {
        for (int i = n; i-- > 0; ) {
            dest[i] = src[i];
        }
    }
    return s1;
}

//метод копирует s2 в s1
char* MyString::strcpy(char* s1, const char* s2) {
    char* dest = s1;
    while ((*dest++ = *s2++) != '\0');
    return s1;
}

//метод копирует n символов s2 в s1
char* MyString::strncpy(char* s1, const char* s2, int n) {
    char* dest = s1;
    int i;
    for (i = 0; i < n && s2[i] != '\0'; ++i) {
        dest[i] = s2[i];
    }
    for (; i < n; ++i) {
        dest[i] = '\0';
    }
    return s1;
}

//метод конкатенирует s2 к s1
char* MyString::strcat(char* s1, const char* s2) {
    char* dest = s1;
    while (*dest) ++dest;
    while ((*dest++ = *s2++) != '\0');
    return s1;
}

//метод конкатенирует n методов s2 к s1
char* MyString::strncat(char* s1, const char* s2, int n) {
    char* dest = s1;
    while (*dest) ++dest;
    for (int i = 0; i < n && s2[i] != '\0'; ++i) {
        dest[i] = s2[i];
    }
    dest[n] = '\0';
    return s1;
}

//метод сравнивает первые n областей 2 участков памяти
int MyString::memcmp(const void* s1, const void* s2, int n) {
    const unsigned char* p1 = static_cast<const unsigned char*>(s1);
    const unsigned char* p2 = static_cast<const unsigned char*>(s2);
    for (int i = 0; i < n; ++i) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

//метод сравнивает 2 строки
int MyString::strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

//метод сравнивает 2 строки с учетом локали
int MyString::strcoll(const char* s1, const char* s2) {
    return strcmp(s1, s2);
}

//метод до n символов двух строк
int MyString::strncmp(const char* s1, const char* s2, int n) {
    for (int i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; ++i) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
    }
    return 0;
}

//метод трансформирует строку s2 и копирует ее s1
int MyString::strxfrm(char* s1, const char* s2, int n) {
    int len = strlen(s2);
    if (n > len) {
        strcpy(s1, s2);
    } else if (n > 0) {
        strncpy(s1, s2, n - 1);
        s1[n - 1] = '\0';
    }
    return len;
}

//метод разбивает строку s1 на токены, разделенные символами из s2
char* MyString::strtok(char* s1, const char* s2) {
    static char* last = nullptr;
    if (s1) last = s1;
    if (!last) return nullptr;

    char* end = last;
    while (*end && strchr(s2, *end) == nullptr) ++end;

    if (*end) {
        *end++ = '\0';
        while (*end && strchr(s2, *end) != nullptr) ++end;
    }

    char* token = last;
    last = *end ? end : nullptr;
    return token;
}

//заменяет первые n байт области памяти s на c
void* MyString::memset(void* s, int c, int n) {
    unsigned char* p = static_cast<unsigned char*>(s);
    for (int i = 0; i < n; ++i) {
        p[i] = static_cast<unsigned char>(c);
    }
    return s;
}

//метод возвращает строку, описывающую номер ошибки
char* MyString::strerror(int errnum) {
    switch (errnum) {
        case 0: return (char*)"No error";
        case 1: return (char*)"Operation not permitted";
        case 2: return (char*)"No such file or directory";
        case 3: return (char*)"No such process";
        default: return (char*)"Unknown error";
    }
}

//возвращает длину c-строки
int MyString::strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') ++len;
    return len;
}
