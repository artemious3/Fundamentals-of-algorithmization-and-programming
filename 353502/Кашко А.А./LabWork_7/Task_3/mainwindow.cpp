#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QInputDialog>

// Конструктор класса MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , hashTable(nullptr) {
    ui->setupUi(this);

    ui->printHashTableButton->hide(); // Скрываем кнопку для вывода хеш-таблицы
}

// Деструктор класса MainWindow
MainWindow::~MainWindow() {
    delete ui; // Освобождаем память, выделенную для пользовательского интерфейса
    if (hashTable) {
        delete hashTable; // Удаляем хеш-таблицу, если она была создана
    }
}

// Слот для создания хеш-таблицы
void MainWindow::on_createHashTableButton_clicked() {
    ui->printHashTableButton->show(); // Показываем кнопку для вывода хеш-таблицы

    if (hashTable) {
        delete hashTable; // Удаляем старую хеш-таблицу, если она была создана
    }

    int size = 10; // Размер хеш-таблицы
    hashTable = new DerivedHashTable(size); // Создаем новую хеш-таблицу производного класса

    // Заполнение случайными значениями
    for (int i = 0; i < 20; ++i) {
        int key = QRandomGenerator::global()->bounded(100); // Генерируем случайный ключ
        int value = QRandomGenerator::global()->bounded(1000); // Генерируем случайное значение
        hashTable->insert(key, value); // Вставляем элемент в хеш-таблицу
    }
}

// Слот для вставки элемента в хеш-таблицу
void MainWindow::on_insertElementButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана."); // Выводим сообщение об ошибке
        return;
    }

    bool ok;
    int key = QInputDialog::getInt(this, tr("Вставка элемента"),
                                   tr("Введите ключ:"), 0, 0, 100, 1, &ok); // Ввод ключа
    if (ok) {
        int value = QInputDialog::getInt(this, tr("Вставка элемента"),
                                         tr("Введите значение:"), 0, 0, 1000, 1, &ok); // Ввод значения
        if (ok) {
            hashTable->insert(key, value); // Вставляем элемент в хеш-таблицу
            ui->textEdit->setText(hashTable->print()); // Выводим содержимое хеш-таблицы
        }
    }
}

// Слот для поиска стека с максимальным значением
void MainWindow::on_findMaxStackButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана."); // Выводим сообщение об ошибке
        return;
    }

    int maxStackIndex = hashTable->findMaxStack(); // Находим индекс стека с максимальным значением
    if (maxStackIndex != -1) {
        ui->textEdit->append("\nСтек с максимальным значением находится в индексе: " + QString::number(maxStackIndex)); // Выводим результат
    } else {
        ui->textEdit->append("\nХеш-таблица пуста."); // Выводим сообщение о пустой хеш-таблице
    }
}

// Слот для вывода содержимого хеш-таблицы
void MainWindow::on_printHashTableButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана."); // Выводим сообщение об ошибке
        return;
    }

    ui->textEdit->setText(hashTable->print()); // Выводим содержимое хеш-таблицы
}

// Слот для удаления элемента из хеш-таблицы
void MainWindow::on_removeElementButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана."); // Выводим сообщение об ошибке
        return;
    }

    bool ok;
    int key = QInputDialog::getInt(this, tr("Удаление элемента"),
                               tr("Введите ключ:"), 0, 0, 100, 1, &ok); // Ввод ключа
    if (ok) {
        int value = QInputDialog::getInt(this, tr("Удаление элемента"),
                                         tr("Введите значение:"), 0, 0, 1000, 1, &ok); // Ввод значения
        if (ok) {
            hashTable->remove(key, value); // Удаляем элемент из хеш-таблицы
            ui->textEdit->setText(hashTable->print()); // Выводим содержимое хеш-таблицы
        }
    }
}

void MainWindow::on_findButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана.");
        return;
    }

    bool ok;
    int key = QInputDialog::getInt(this, tr("Поиск элемента"),
                                   tr("Введите ключ для поиска:"), 0, 0, 100, 1, &ok);
    if (ok) {
        int result = hashTable->find(key);
        if (result != -1) {
            ui->textEdit->append("\nНайденное значение: " + QString::number(result));
        } else {
            ui->textEdit->append("\nЭлемент с указанным ключом не найден.");
        }
    }
}

void MainWindow::on_isEmptyButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана.");
        return;
    }

    if (hashTable->isEmpty()) {
        ui->textEdit->append("\nХеш-таблица пуста.");
    } else {
        ui->textEdit->append("\nХеш-таблица не пуста.");
    }
}

void MainWindow::on_sizeButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана.");
        return;
    }

    int tableSize = hashTable->size();
    ui->textEdit->append("\nРазмер хеш-таблицы: " + QString::number(tableSize));
}

void MainWindow::on_clearButton_clicked() {
    if (!hashTable) {
        ui->textEdit->setText("Хеш-таблица не создана.");
        return;
    }

    hashTable->clear();
    ui->textEdit->setText("Хеш-таблица очищена.");
}
