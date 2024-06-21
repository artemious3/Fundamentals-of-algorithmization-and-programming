#include <iostream>

void hanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1) {
        std::cout << "Переместить кольцо 1 с " << from_rod << " на " << to_rod << std::endl;
        return;
    }

    hanoi(n - 1, from_rod, aux_rod, to_rod);
    std::cout << "Переместить кольцо " << n << " с " << from_rod << " на " << to_rod << std::endl;
    hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main()
{
    int n = 5;
    std::cout << "Количество колец: " << n << std::endl;

    if (n <= 0) {
        std::cout << "Количество колец должно быть больше 0." << std::endl;
        return 1;
    }

    hanoi(n, 'A', 'B', 'C');

    return 0;
}
