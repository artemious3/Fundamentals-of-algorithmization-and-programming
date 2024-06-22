#include "BitSet.h"
#include <QDebug>

int main() {
    BitSet bitset(16);
    bitset.set(0);
    bitset.set(5);



    qDebug() << "Объект после установки битов: " << bitset.to_string();

    bitset[0] = true;
    qDebug() << "Объект после установки битов: " << bitset.to_string();
    bitset.reset(5);
    qDebug() << "Объект после сброса бита: " << bitset.to_string();

    qDebug() << "Проверка 0-го бита: " << bitset.test(0);
    qDebug() << "Проверка 3-го бита: " << bitset.test(3);

    bitset.flip(0);
    qDebug() << "Объект после переключения бита: " << bitset.to_string();

    qDebug() << bitset.all();

    qDebug() << bitset.any();

    qDebug() << "Количество установленных битов: " << bitset.count();

    qDebug() << "Ни один бит не установлен: " << bitset.none();

    qDebug() << "BitSet в виде строки: " << bitset.to_string();
    qDebug() << "BitSet в виде unsigned long long: " << bitset.to_ullong();
    qDebug() << "BitSet в виде unsigned long: " << bitset.to_ulong();

    return 0;
}
