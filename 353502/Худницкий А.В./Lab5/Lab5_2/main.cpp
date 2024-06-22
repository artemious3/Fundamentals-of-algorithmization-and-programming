#include "MyString.h"
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

    MyString str1("Hello");
    MyString str2("World");
/*
    std::cout << "str1: " << str1.c_str() << std::endl;
    std::cout << "str2: " << str2.c_str() << std::endl;

    MyString str3 = str1;
    std::cout << "str3 (copy of str1): " << str3.c_str() << std::endl;

    str3 = str2;
    std::cout << "str3 (after assignment from str2): " << str3.c_str() << std::endl;

    char buffer[100] = "Hello";
    str1.strcat(buffer, " World");
    std::cout << "buffer after strcat: " << buffer << std::endl;

    char s1[] = "Test";
    char s2[] = "Test";
    std::cout << "memcmp: " << str1.memcmp(s1, s2, str1.strlen(s1)) << std::endl;

    str1.memset(s1, 'A', 2);
    std::cout << "memset: " << s1 << std::endl;

    std::cout << "strlen: " << str1.strlen("Hello World") << std::endl;

    char dest[100];
    str1.memcpy(dest, "Copy this", 10);
    std::cout << "memcpy: " << dest << std::endl;

    MyString str3("World");
    MyString str4("World");
    char dest[100];
    str1.memmove(str3, str4 , 5);
    std::cout << "memmove: " << dest << std::endl;

    /*std::cout << "strerror(2): " << str1.strerror(2) << std::endl;

    char str4[50];
    str1.strncpy(str4, "Shortened", 5);
    str4[5] = '\0';
    std::cout << "strncpy: " << str4 << std::endl;

    char str5[] = "Tokenize this string";
    char* token = str1.strtok(str5, " ");
    while (token != nullptr) {
        std::cout << "Token: " << token << std::endl;
        token = str1.strtok(nullptr, " ");
    }*/

    char s[] = "dgsalfghllasd";

    memmove(s + 20,s + 15, 11);

    std::cout << s;


}
