#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include <cmath>
#include <QRegularExpression>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключение сигналов от кнопок к соответствующим слотам
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortArray);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchElement);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция для бинарного возведения в степень
int binpow(int digit, int power, int mod) {
    int result = 1;
    digit %= mod;
    while (power > 0) {
        if (power % 2 == 1) {
            result = (result * digit) % mod;
        }
        digit = (digit * digit) % mod;
        power /= 2;
    }
    return result;
}

// Функция для вывода массива в виде текста
void MainWindow::printArray(const vector<int>& arr, int step) {
    // Формирование строки для текущего шага сортировки
    QString arrayStr = QString::number(step) + " шаг: ";
    for (int val : arr) {
        arrayStr += QString::number(val) + " ";
    }
    arrayStr += "\n";

    // Добавление строки к существующему тексту в QLabel
    ui->outputLable->setText(ui->outputLable->text() + arrayStr);
}

// Функция для бинарного поиска позиции вставки
int MainWindow::binarySearch(const vector<int>& arr, int val, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == val)
            return mid + 1; // Возвращаем индекс позиции вставки (плюс один, т.к. вставка после mid)
        else if (arr[mid] < val)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low; // Возвращаем индекс позиции вставки
}

// Функция для интерполяционной сортировки
void MainWindow::interpolationSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int val = arr[i];
        int pos = binarySearch(arr, val, 0, i - 1); // Находим позицию вставки элемента val

        // Сдвигаем элементы вправо, чтобы освободить место для вставки
        for (int j = i - 1; j >= pos; j--) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = val; // Вставляем элемент на найденную позицию

        // Выводим массив после каждого шага сортировки
        printArray(arr, i);
    }
}

// Функция для проверки корректности ввода
bool MainWindow::validateInput(const QString &input) {
    QRegularExpression re("^\\d+( \\d+)*$"); // Регулярное выражение для проверки формата "1 2 3 4 ..."
    return re.match(input).hasMatch();
}

// Обработчик для кнопки сортировки
void MainWindow::sortArray() {
    // Очищаем QLabel перед каждой сортировкой
    ui->outputLable->clear();

    // Считываем текст из QTextEdit и разбиваем на числа
    QString input = ui->arrayInput->toPlainText();

    // Проверка корректности ввода
    if (!validateInput(input)) {
        ui->errorLabel->setText("Некорректный ввод данных");
        return;
    }

    QStringList inputList = input.split(" ", Qt::SkipEmptyParts);
    vector<int> arr;

    // Преобразуем строки в числа и добавляем в вектор
    for (const QString& str : inputList) {
        arr.push_back(str.toInt());
    }

    // Вызываем функцию сортировки
    interpolationSort(arr);

    // Очистить сообщение об ошибке
    ui->errorLabel->clear();
}

// Обработчик для кнопки поиска и вычисления
void MainWindow::searchElement() {
    // Считываем текст из QTextEdit и разбиваем на числа
    QString input = ui->arrayInput->toPlainText();

    // Проверка корректности ввода
    if (!validateInput(input)) {
        ui->errorLabel->setText("Некорректный ввод данных");
        return;
    }

    QStringList inputList = input.split(" ", Qt::SkipEmptyParts);
    vector<int> arr;

    for (const QString& str : inputList) {
        arr.push_back(str.toInt());
    }

    // Считываем элемент для поиска
    int elementToFind = ui->elementInput->toPlainText().toInt();

    // Ищем элемент в массиве
    auto it = std::find(arr.begin(), arr.end(), elementToFind);

    // Если элемент найден, вычисляем индекс в степени длины массива по модулю
    if (it != arr.end()) {
        int index = distance(arr.begin(), it); // Вычисляем индекс элемента
        int arrayLength = arr.size(); // Длина массива
        int mod = 1000; // Модуль (можно изменить по вашему выбору)
        int result = binpow(index, arrayLength, mod); // Вычисляем результат
        ui->resultLabel->setText("Result: " + QString::number(result));
    } else {
        ui->resultLabel->setText("Element not found."); // Если элемент не найден
    }

    // Очистить сообщение об ошибке
    ui->errorLabel->clear();
}

// Функция для интерполяционной сортировки с использованием интерполяционного поиска, который не даёт гарантии возвращения верной позиции
/*void MainWindow::interpolationSort(vector<int>& arr) {
    int n = arr.size();
    bool a = false;
    for (int i = 1; i < n; i++) {
        int val = arr[i];
        int low = 0;
        int high = i - 1;

        // Используем интерполяционный поиск для нахождения правильной позиции
        while (low <= high && arr[low] != arr[high]) {
            int pos = low + ((val - arr[low]) * (high - low) / (arr[high] - arr[low]));

            // Ограничиваем pos в пределах [low, high]
            if (pos < low) pos = low;
            if (pos > high) pos = high;

            if (arr[pos] == val) {
                low = pos + 1;
                break;
            } else if (arr[pos] < val) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }

        // Если все элементы в диапазоне равны
        if (arr[low] == arr[high]) {
            if (arr[low] > val) {
                // Сдвигаем элементы
                for (int j = i - 1; j >= low; j--) {
                    arr[j + 1] = arr[j];
                }
                arr[low] = val;
            } else {
                // Если все элементы равны и меньше или равны val, просто вставляем в конец
                low = i;
                a = true;
            }
        } else {
            // Сдвигаем элементы
            for (int j = i - 1; j >= low; j--) {
                arr[j + 1] = arr[j];
            }

        }

        // Выводим массив после каждого шага (если требуется для отладки)
        printArray(arr, i);
    }
}*/
