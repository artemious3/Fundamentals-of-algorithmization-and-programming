//    // Используем конструктор NewString для создания строки
//    const char str[] = "something";
//    NewString string(str);

//    // Выводим строку с использованием оператора <<
//    std::cout << "String: " << string << std::endl;

//    // Копируем строку с помощью конструктора копирования
//    NewString copiedString(string);
//    std::cout << "Copied String: " << copiedString << std::endl;

//    // Присваиваем новую строку
//    NewString anotherString;
//    anotherString = "another";
//    std::cout << "Another String: " << anotherString << std::endl;

//    // Сравниваем строки
//    int cmpResult = string.strcmp(string.data.get(), anotherString.data.get());
//    std::cout << "Comparison result (strcmp): " << cmpResult << std::endl;

//    // Сравнение первых n символов
//    int nCmpResult = string.strncmp(string.data.get(), anotherString.data.get(), 3);
//    std::cout << "Comparison result (strncmp): " << nCmpResult << std::endl;

//    // Конкатенация строк
//    char dest[50] = "Hello, ";
//    string.strcat(dest, "World!");
//    std::cout << "Concatenated String (strcat): " << dest << std::endl;

//    // Конкатенация строк с ограничением
//    char dest2[50] = "Hello, ";
//    string.strncat(dest2, "Beautiful World!", 9);
//    std::cout << "Concatenated String (strncat): " << dest2 << std::endl;

//    // Поиск символа в строке
//    const char* findChar = string.strchr(string.data.get(), 'e');
//    if (findChar) {
//        std::cout << "Character 'e' found in string: " << findChar << std::endl;
//    } else {
//        std::cout << "Character 'e' not found in string." << std::endl;
//    }

//    // Разделение строки
//    char strToTokenize[] = "Hello, how are you?";
//    const char* delimiters = " ,?";
//    char* token = string.strtok(strToTokenize, delimiters);
//    while (token != nullptr) {
//        std::cout << "Token: " << token << std::endl;
//        token = string.strtok(nullptr, delimiters);
//    }

//    // Ошибки
//    std::cout << "Error message: " << string.strerror(1) << std::endl;

//    // Использование memcpy и memmove
//    char src[] = "memmove can be very useful......";
//    char dest3[50];
//    string.memcpy(dest3, src, string.strlen(src) + 1);
//    std::cout << "Copied String (memcpy): " << dest3 << std::endl;

//    string.memmove(dest3 + 20, dest3 + 15, 11);
//    std::cout << "Moved String (memmove): " << dest3 << std::endl;

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
