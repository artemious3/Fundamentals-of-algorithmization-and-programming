#ifndef STRINGKASHKO_H
#define STRINGKASHKO_H

#include <iostream>
#include <memory>

class StringKashko {
public:
    //конструкторы
    StringKashko();

    explicit StringKashko(const char* str);

    // конструктор копирования
    StringKashko(const StringKashko& secondStr);

    // перегрузки оператора присваивания
    StringKashko& operator=(const StringKashko& secondStr);
    StringKashko& operator=(const char* str);

    // деструктор
    ~StringKashko();

    size_t length() const;

    // объявление перегрузки оператора индексирования [] для класса. Этот оператор позволяет обращаться
    //к элементам объекта класса по индексу, как если бы он был массивом.
    char& operator[](size_t index);

    using iterator = char*;

    using const_iterator = const char*;

    iterator begin() const;

    iterator end() const;

    void push_back(const char c);

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

    void* memset(void* s, int c, size_t n);

    char* strerror(int errnum);

    char* strchr(const char* str, int c);

    size_t strlen(const char* s);

    /*    friend: Указывает, что функция operator<< является дружественной по отношению к классу String.
    std::ostream &operator<<: Это возвращаемое значение и имя функции. Возвращается ссылка на std::ostream,
    что позволяет цепочечный вывод (например, std::cout << str1 << str2).
    (std::ostream &os, const String &str): Аргументы функции. Первый аргумент — это ссылка на выходной поток,
    второй аргумент — это константная ссылка на объект класса String.
        Дружественная функция (friend function) — это функция, которая не является членом класса,
    но имеет доступ к его приватным и защищенным членам. Это означает, что дружественная функция может
    использовать внутренние данные и методы класса, к которым не был бы доступ обычный внешний код.*/
    friend std::ostream& operator<<(std::ostream& os, const StringKashko& str);

    // std::unique_ptr: Это шаблонный класс умного указателя, предоставляемый стандартной библиотекой C++
    //  (включен в заголовочный файл <memory>). Он управляет объектом через указатель и обеспечивает автоматическое
    //  удаление объекта, когда std::unique_ptr выходит из области видимости. В отличие от обычного указателя,
    //  std::unique_ptr не допускает копирования, что предотвращает проблемы с двойным удалением.
    //  char[]: Этот синтаксис указывает, что std::unique_ptr будет управлять динамически выделенным массивом объектов типа char
    std::unique_ptr<char[]> data;

private:
    size_t size;
};

#endif // STRINGKASHKO_H
