#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_sortButton_clicked() {
    QString input = ui->arrayInputTextEdit->toPlainText();
    // Разбиваем строку на список строк, используя пробел в качестве разделителя
    QStringList stringList = input.split(" ", Qt::SkipEmptyParts);

    // Проверка на некорректный ввод
    bool inputCorrect = true;
    for (const QString &str : stringList) {
        bool ok;
        str.toInt(&ok);
        if (!ok) {
            inputCorrect = false;
            break;
        }
    }

    if (!inputCorrect) {
        ui->incorrectInputLabel->setText("НЕКОРРЕКТНЫЙ ВВОД!");
        return;
    }

    // Сброс текста ошибки, если ввод корректен
    ui->incorrectInputLabel->clear();

    array.clear();
    for (const QString &str : stringList) {
        array.append(str.toInt());
    }

    QElapsedTimer timer;
    QVector<int> arrCopy = array;

    // Heap Sort
    timer.start();
    heapSort(arrCopy);
    qint64 heapTime = timer.nsecsElapsed() / 1000; // microseconds
    ui->heapTimeLabel->setText("Heap Sort Time: " + QString::number(heapTime) + " µs");
    ui->heapSortedLabel->setText("Heap Sorted Array: " + arrToString(arrCopy));

    // Quick Sort
    arrCopy = array;
    timer.start();
    quickSort(arrCopy, 0, arrCopy.size() - 1);
    qint64 quickTime = timer.nsecsElapsed() / 1000; // microseconds
    ui->quickTimeLabel->setText("Quick Sort Time: " + QString::number(quickTime) + " µs");
    ui->quickSortedLabel->setText("Quick Sorted Array: " + arrToString(arrCopy));

    // Merge Sort
    arrCopy = array;
    timer.start();
    mergeSort(arrCopy, 0, arrCopy.size() - 1);
    qint64 mergeTime = timer.nsecsElapsed() / 1000; // microseconds
    ui->mergeTimeLabel->setText("Merge Sort Time: " + QString::number(mergeTime) + " µs");
    ui->mergeSortedLabel->setText("Merge Sorted Array: " + arrToString(arrCopy));

    sortedArray = arrCopy;
}

QString MainWindow::arrToString(const QVector<int> &arr) {
    QString result;
    for (int i = 0; i < arr.size(); ++i) {
        result += QString::number(arr[i]);
        if (i != arr.size() - 1) {
            result += " ";
        }
    }
    return result;
}

void MainWindow::on_searchButton_clicked() {
    bool ok;
    int digit = ui->searchInputTextEdit->toPlainText().toInt(&ok);
    if (ok) {
        int index = binsearch(sortedArray, digit);
        ui->searchResultLabel->setText("Search Result: " + QString::number(index));
    }
}

int MainWindow::binsearch(QVector<int> &arr, int digit)
{
    // Начальный индекс поиска
    int low = 0;
    // Конечный индекс поиска
    int high = arr.size() - 1;

    while (low <= high) {
        // Находим средний индекс массива
        int mid = low + (high - low) / 2;

        // Проверяем, совпадает ли средний элемент с искомым числом
        if (arr[mid] == digit) {
            // Если элемент найден, возвращаем его индекс
            return mid;
        }
        // Если средний элемент больше искомого числа
        else if (arr[mid] > digit) {
            // Ищем в левой половине массива
            high = mid - 1;
        }
        // Если средний элемент меньше искомого числа
        else {
            // Ищем в правой половине массива
            low = mid + 1;
        }
    }
    // Если элемент не найден, возвращаем -1
    return -1;
}

void MainWindow::heapify(QVector<int> &arr, int n, int i) {
    // Инициализируем наибольший элемент как текущий узел
    int largest = i;
    // Ищем индексы левого и правого потомка текущего узла
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Если левый потомок существует и больше, чем текущий наибольший элемент
    if (left < n && arr[left] > arr[largest]) {
        // Обновляем индекс наибольшего элемента
        largest = left;
    }
    // Если правый потомок существует и больше, чем текущий наибольший элемент
    if (right < n && arr[right] > arr[largest]) {
        // Обновляем индекс наибольшего элемента
        largest = right;
    }
    // Если наибольший элемент не корень
    if (largest != i) {
        // Меняем местами текущий узел и наибольший элемент
        std::swap(arr[i], arr[largest]);
        // Рекурсивно вызываем heapify для поддерева
        heapify(arr, n, largest);
    }
}

void MainWindow::heapSort(QVector<int> &arr) {
    // Получаем размер массива
    int n = arr.size();
    // Построение кучи (первый проход вниз по дереву)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // Извлечение элементов из кучи (второй проход вверх по дереву)
    for (int i = n - 1; i >= 0; i--) {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);
        // Вызываем heapify для уменьшенной кучи
        heapify(arr, i, 0);
    }
}

void MainWindow::quickSort(QVector<int> &arr, int low, int high) {
    // Если есть более одного элемента для сортировки
    if (low < high) {
        // Получаем индекс разбиения
        int pi = partition(arr, low, high);
        // Рекурсивно сортируем элементы перед и после разбиения
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int MainWindow::partition(QVector<int> &arr, int low, int high) {
    // Выбираем последний элемент в качестве опорного
    int pivot = arr[high];
    // Инициализируем индекс меньшего элемента
    int i = (low - 1);
    // Перебираем все элементы
    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (arr[j] < pivot) {
            // Увеличиваем индекс меньшего элемента и меняем элементы местами
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    // Меняем местами опорный элемент и элемент, стоящий после меньших элементов
    std::swap(arr[i + 1], arr[high]);
    // Возвращаем индекс опорного элемента
    return (i + 1);
}

void MainWindow::mergeSort(QVector<int> &arr, int l, int r) {
    // Если есть более одного элемента для сортировки
    if (l < r) {
        // Находим средний элемент
        int m = l + (r - l) / 2;
        // Рекурсивно сортируем первую и вторую половины
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        // Объединяем отсортированные части
        merge(arr, l, m, r);
    }
}

void MainWindow::merge(QVector<int> &arr, int l, int m, int r) {
    // Получаем размеры временных подмассивов
    int n1 = m - l + 1;
    int n2 = r - m;
    // Создаем временные подмассивы
    QVector<int> L(n1), R(n2);

    // Копируем данные во временные подмассивы L[] и R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    // Сливаем временные подмассивы обратно в arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Копируем оставшиеся элементы L[], если таковые остались
    while (i < n1) {
        arr[k++] = L[i++];
    }
    // Копируем оставшиеся элементы R[], если таковые остались
    while (j < n2) {
        arr[k++] = R[j++];
    }
}
