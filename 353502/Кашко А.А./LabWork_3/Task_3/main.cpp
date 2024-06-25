#include <cmath>
#include <iostream>

int reverseNumber(int num, int reversed = 0)
{
    if (num == 0) {
        return reversed;
    }
    return reverseNumber(num / 10, reversed * 10 + num % 10);
}

int main()
{
    int num = 978;
    std::cout << "Число: " << num << std::endl;

    if (num <= 0 || num % 10 == 0) {
        std::cout << "Число должно быть положительным и не содержать нулей." << std::endl;
        return 1;
    }

    int reversed = reverseNumber(num);
    std::cout << "Обратное число: " << reversed << std::endl;

    return 0;
}
