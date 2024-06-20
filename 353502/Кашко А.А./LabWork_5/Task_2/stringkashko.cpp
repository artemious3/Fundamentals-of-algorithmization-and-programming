#include "stringkashko.h"

StringKashko::StringKashko() : data(nullptr), size(0) {}

StringKashko::StringKashko(const char* str) {
    size = strlen(str);
    /*    Здесь мы явно создаем объект с помощью new, который возвращает указатель на выделенную память.
    std::unique_ptr захватывает этот указатель и начинает управлять им.
    (с учетом символа завершения строки \0)*/
    data = std::unique_ptr<char[]>(new char[size + 1]);
    strcpy(
        data.get(),
        str);  //data.get() - метод, который используется для получения указателя на управляемый std::unique_ptr объектом.
}

// Конструктор копирования
StringKashko::StringKashko(const StringKashko& secondStr) : size(secondStr.length()) {
    data = std::unique_ptr<char[]>(new char[size + 1]);
    strcpy(data.get(), secondStr.data.get());
}

StringKashko& StringKashko::operator=(const StringKashko& secondStr) {
    if (this != &secondStr) {
        size = secondStr.size;
        data = std::unique_ptr<char[]>(new char[size + 1]);
        strcpy(data.get(), secondStr.data.get());
    }
    return *this;
}

StringKashko& StringKashko::operator=(const char* str) {
    // Определяем новую длину строки
    size_t newLength = strlen(str);

    // Создаем временный уникальный указатель, управляющий новым массивом char, размером newLength + 1
    // для хранения завершающего нулевого символа
    std::unique_ptr<char[]> newData =
        std::unique_ptr<char[]>(new char[newLength + 1]);

    // Копируем содержимое строки str в новый массив, управляемый newData
    strcpy(newData.get(), str);

    /*std::move

std::move — это функция, которая выполняет преобразование в rvalue-ссылку. Это не значит, что объект будет перемещен. Это просто разрешает использовать объект
в контексте перемещения.
Зачем это нужно?

Когда мы делаем data = std::move(newData);, мы перемещаем владение ресурса (динамического массива) от newData к data. После выполнения этой операции:

    data теперь владеет массивом, который был создан ранее.
    newData больше не владеет этим массивом и становится пустым (nullptr).

Почему нужно использовать std::move?

Стандартный присваивающий оператор для std::unique_ptr удален, чтобы предотвратить копирование (поскольку копирование уникального владения противоречит самой идее уникального владения). Поэтому, чтобы переместить ресурс из одного std::unique_ptr в другой, мы используем std::move.
Что происходит при data = std::move(newData);?

    Перемещение владения:
        До выполнения data = std::move(newData);, newData владеет динамическим массивом char.
        После выполнения data = std::move(newData);, data становится владельцем этого динамического массива.

    Состояние newData после перемещения:
        После перемещения newData становится пустым (то есть, его внутренний указатель устанавливается в nullptr).
        newData больше не владеет массивом и не управляет его жизненным циклом.*/
    data = std::move(newData);

    // Обновляем длину строки
    size = newLength;

    // Возвращаем текущий объект
    return *this;
}

StringKashko::~StringKashko() = default;

size_t StringKashko::length() const {
    return size;
}

char& StringKashko::operator[](size_t index) {
    return data[index];
}

StringKashko::iterator StringKashko::begin() const {
    return data.get();
}

StringKashko::iterator StringKashko::end() const {
    return data.get() + size;
}

void StringKashko::push_back(const char c) {}

void* StringKashko::memcpy(void* s1, const void* s2, size_t n) {
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }
    // Приводим указатели к типу char*, так как будем работать с побайтовым копированием
    char* place = static_cast<char*>(s1);
    const char* source = static_cast<const char*>(s2);

    // Копируем n байтов из источника в назначение
    for (size_t i = 0; i < n; ++i) {
        place[i] = source[i];
    }
    return s1;
}

/*Функция String::memmove служит для безопасного копирования блока памяти из одного места в другое,
 особенно в тех случаях, когда эти области памяти могут перекрываться. Это важно, так как при перекрытии
 областей памяти простое копирование (например, с помощью memcpy) может привести к некорректному результату
 из-за того, что часть данных может быть
перезаписа
на до того, как она будет скопирована.*/
void* StringKashko::memmove(void* s1, const void* s2, size_t n) {
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }
    // Приводим указатели к типу char*, так как будем работать с побайтовым копированием
    char* place = static_cast<char*>(s1);
    const char* source = static_cast<const char*>(s2);

    // Проверяем, не перекрываются ли области памяти
    if (place <= source || place >= source + n) {
        // Если place и source не перекрываются или place перед source, копируем данные с начала
        memcpy(s1, s2, n);
    } else {
        // Если dest находится внутри диапазона src, копируем данные с конца
        for (size_t i = n; i > 0; --i) {
            place[i - 1] = source[i - 1];
        }
    }
    return s1;  // Возвращаем указатель на начало place
}

char* StringKashko::strcpy(char* s1, const char* s2) {
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

char* StringKashko::strncpy(char* s1, const char* s2, size_t n) {
    // Проверяем, не являются ли указатели nullptr
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }

    size_t i = 0;
    // Копируем символы из s2 в s1 до тех пор, пока не достигнем конца s2 или не скопируем n символов
    for (; i < n && s2[i] != '\0'; ++i) {
        s1[i] = s2[i];
    }

    // Если достигли конца s2 раньше, чем n символов, заполняем оставшиеся байты в s1 нулями
    for (; i < n; ++i) {
        s1[i] = '\0';
    }

    // Возвращаем указатель на начало s1
    return s1;
}

char* StringKashko::strcat(char* s1, const char* s2) {
    // Проверяем, не являются ли указатели nullptr
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }

    // Находим конец первой строки (где '\0')
    char* end = s1;
    while (*end != '\0') {
        ++end;
    }

    // Копируем символы из s2 в s1 начиная с конца s1
    while (*s2 != '\0') {
        *end = *s2;
        ++end;
        ++s2;
    }

    // Добавляем нуль-терминатор в конец
    *end = '\0';

    // Возвращаем указатель на начало s1
    return s1;
}

char* StringKashko::strncat(char* s1, const char* s2, size_t n) {
    // Проверяем, не являются ли указатели nullptr
    if (s1 == nullptr || s2 == nullptr) {
        return s1;
    }

    // Находим конец первой строки (где '\0')
    char* dest = s1;
    while (*dest != '\0') {
        ++dest;
    }

    // Копируем символы из s2 в s1, пока не скопируем n символов или не достигнем конца s2
    size_t i;
    for (i = 0; i < n && s2[i] != '\0'; ++i) {
        dest[i] = s2[i];
    }

    // Добавляем нуль-терминатор в конец
    dest[i] = '\0';

    // Возвращаем указатель на начало s1
    return s1;
}

int StringKashko::memcmp(const void* s1, const void* s2, size_t n) {
    const char* p1 = static_cast<const char*>(s1);
    const char* p2 = static_cast<const char*>(s2);

    for (size_t i = 0; i < n; ++i) {
        if (p1[i] < p2[i]) {
            return -1;  // Возвращаем -1, если первый блок памяти меньше второго
        } else if (p1[i] > p2[i]) {
            return 1;  // Возвращаем 1, если первый блок памяти больше второго
        }
    }
    // Если все байты равны, возвращаем 0
    return 0;
}

int StringKashko::strcmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}

int StringKashko::strcoll(const char* s1, const char* s2) {

    while (*s1 != '\0' && *s2 != '\0') {
        // Побайтовое сравнение символов двух строк
        if (*s1 < *s2) {
            return -1;  // Если символ из первой строки меньше, возвращаем -1
        } else if (*s1 > *s2) {
            return 1;  // Если символ из второй строки меньше, возвращаем 1
        }
        s1++;  // Переходим к следующему символу в первой строке
        s2++;  // Переходим к следующему символу во второй строке
    }

    // Проверяем, завершились ли строки одновременно
    if (*s1 == '\0' && *s2 == '\0') {
        return 0;  // Строки полностью совпадают, возвращаем 0
    } else if (*s1 == '\0') {
        return -1;  // Строка s1 закончилась раньше, возвращаем -1
    } else {
        return 1;  // Строка s2 закончилась раньше, возвращаем 1
    }
}

int StringKashko::strncmp(const char* s1, const char* s2, size_t n) {
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
    return 0;  // Строки совпадают
}

size_t StringKashko::strxfrm(char* s1, const char* s2, size_t n) {
    size_t s2_len = strlen(s2);

    // Если длина преобразованной строки не умещается в буфер s1,
    // то возвращается длина, которая была бы необходима для записи строки
    if (n <= s2_len) {
        return s2_len;
    }

    // Просто копируем исходную строку в s1
    strcpy(s1, s2);

    return s2_len;
}

char* StringKashko::strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return (char*)str;
        }
        ++str;
    }
    return nullptr;
}

char* StringKashko::strtok(char* s1, const char* s2) {
    static char* last = nullptr;

    // Указатель на начало текущего токена
    char* token_start;

    // Указатель на строку разделителей
    const char* delimiters = s2;

    // Если передана новая строка, обновляем указатель last
    if (s1 != nullptr)
        last = s1;

    // Если last пуст или указывает на конец строки, возвращаем nullptr,
    // так как разбиение завершено
    if (last == nullptr || *last == '\0')
        return nullptr;

    // Пропускаем начальные символы, которые входят в набор разделителей
    while (*last != '\0' && StringKashko::strchr(delimiters, *last) != nullptr)
        last++;

    // Если достигнут конец строки, обновляем last и возвращаем nullptr,
    // так как разбиение завершено
    if (*last == '\0') {
        last = nullptr;
        return nullptr;
    }

    // Запоминаем указатель на начало текущего токена
    token_start = last;

    // Ищем следующий разделитель
    while (*last != '\0' && StringKashko::strchr(delimiters, *last) == nullptr)
        last++;

    // Если достигнут конец строки, обновляем last до nullptr
    // Иначе, заменяем найденный разделитель нулевым символом,
    // чтобы завершить текущий токен, и перемещаем указатель last к следующему символу
    if (*last == '\0') {
        last = nullptr;
    } else {
        *last = '\0';
        last++;
    }

    // Возвращаем указатель на начало текущего токена
    return token_start;
}

void* StringKashko::memset(void* s, int c, size_t n) {}

char* StringKashko::strerror(int errnum) {
    static char* errorMessages[] = {
        "No error",                   // 0
        "Operation not permitted",    // 1
        "No such file or directory",  // 2
        "Invalid argument",
    };

    // Проверяем, находится ли код ошибки в допустимом диапазоне
    if (errnum < 0 ||
        errnum >= sizeof(errorMessages) / sizeof(errorMessages[0])) {
        return "Unknown error";
    }

    // Возвращаем соответствующее сообщение об ошибке
    return errorMessages[errnum];
}

size_t StringKashko::strlen(const char* s) {
    int count = 0;
    while (*s != '\0') {
        ++s;
        ++count;
    }
    return count;
}

std::ostream& operator<<(std::ostream& os, const StringKashko& str)
{
    os << str.data.get();
    return os;
}
