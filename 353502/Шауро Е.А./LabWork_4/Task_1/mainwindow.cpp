#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(600, 450);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_sortButton_clicked() {
  QString input = ui->arrayInputTextEdit->toPlainText();
  QStringList stringList = input.split(" ", QString::SkipEmptyParts);

  // Проверка на некорректный ввод
  bool isCorrectInput = true;
  for (auto str : stringList) {
    if (!isCorrectInput) {
      break;
    }
    str.toInt(&isCorrectInput);
  }

  if (!isCorrectInput) {
    ui->incorrectInputLabel->setText("НЕКОРРЕКТНЫЙ ВВОД!");
    return;
  }

  // Сброс текста ошибки, если ввод корректен
  ui->incorrectInputLabel->clear();
  array.clear();
  for (auto str : stringList) {
    array.append(str.toInt());
  }

  QElapsedTimer timer;
  QVector<int> copyArr = array;

  // Heap Sort
  timer.start();
  heapSort(copyArr);
  qint64 heapTime = timer.nsecsElapsed() / msc;
  ui->heapTimeLabel->setText(QString::number(heapTime) + "ms");
  ui->heapSortedLabel->setText(toStr(copyArr));

  // Quick Sort
  copyArr = array;
  timer.start();
  quickSort(copyArr, 0, copyArr.size() - 1);
  qint64 quickTime = timer.nsecsElapsed() / msc;
  ui->quickTimeLabel->setText(QString::number(quickTime) + " ms");
  ui->quickSortedLabel->setText(toStr(copyArr));

  // Merge Sort
  copyArr = array;
  timer.start();
  mergeSort(copyArr, 0, copyArr.size() - 1);
  qint64 mergeTime = timer.nsecsElapsed() / msc;
  ui->mergeTimeLabel->setText(QString::number(mergeTime) + " ms");
  ui->mergeSortedLabel->setText(toStr(copyArr));

  sortedArray = copyArr;
}

QString MainWindow::toStr(const QVector<int>& arr) {
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
    ui->searchResultLabel->setText(
        "Результат поиска: " + QString::number(index) + " место в массиве");
  }
}

int MainWindow::binsearch(QVector<int>& arr, int digit) {

  int mid, low = 0;
  int high = arr.size() - 1;

  while (low <= high) {
    mid = low + (high - low) / 2;
    // Проверяем, совпадает ли средний элемент с искомым числом
    if (arr[mid] == digit) {
      return mid;
    }
    // Ищем в левой половине массива
    else if (arr[mid] > digit) {
      high = mid - 1;
    }
    // Ищем в правой половине массива
    else {
      low = mid + 1;
    }
  }
  return -1;
}

void MainWindow::heapify(QVector<int>& arr, int size, int i) {

  int largest = i;       // корень
  int left = 2 * i + 1;  // Ищем индексы левого и правого потомка текущего узла
  int right = 2 * i + 2;

  if (left < size && arr[left] > arr[largest]) {
    largest = left;
  }
  if (right < size && arr[right] > arr[largest]) {
    largest = right;
  }
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    heapify(arr, size, largest);
  }
}

void MainWindow::heapSort(QVector<int>& arr) {
  int size = arr.size();
  for (int i = size / 2 - 1; i >= 0; i--) {  // Построение кучи
    heapify(arr, size, i);
  }

  for (int i = size - 1; i >= 0; i--) {  // Извлечение элементов из кучи
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void MainWindow::quickSort(QVector<int>& arr, int low, int high) {
  if (low < high) {
    // Индекс разбиения
    int index = partition(arr, low, high);

    quickSort(arr, low, index - 1);
    quickSort(arr, index + 1, high);
  }
}

int MainWindow::partition(QVector<int>& arr, int low, int high) {

  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }

  std::swap(arr[i + 1], arr[high]);
  return (i + 1);
}

void MainWindow::mergeSort(QVector<int>& arr, int low, int high) {
  if (low < high) {
    int mid = low + (high - low) / 2;  // Находим средний элемент
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    // Объединяем отсортированные части
    merge(arr, low, mid, high);
  }
}

void MainWindow::merge(QVector<int>& arr, int low, int mid, int high) {

  int size1 = mid - low + 1;
  int size2 = high - mid;
  // Создаем временные подмассивы
  QVector<int> L(size1), R(size2);

  for (int i = 0; i < size1; i++) {
    L[i] = arr[low + i];
  }
  for (int j = 0; j < size2; j++) {
    R[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = low;
  while (i < size1 && j < size2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  while (i < size1) {
    arr[k++] = L[i++];
  }

  while (j < size2) {
    arr[k++] = R[j++];
  }
}

void MainWindow::on_pushButton_clicked() {
  QString text = ui->arrayInputTextEdit->toPlainText();
  int rand = QRandomGenerator::global()->bounded(100);
  ui->arrayInputTextEdit->setText(text + " " + QString::number(rand));
}
