#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <algorithm>
#include <cmath>
#include <vector>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

qint64 binpow(qint64 a, int n, int mod) {
  qint64 res = 1;
  while (n != 0) {
    if (n & 1) {  // Проверка на нечетность
      res = res * a % mod;
    }
    a = a * a % mod;
    n >>= 1;  // cдвиг на бит вправо (деление на 2)
  }
  return res;
}

void MainWindow::printArray(const QVector<int>& arr, int step) {

  QString arrayStr = QString::number(step) + " шаг: ";
  for (int val : arr) {
    arrayStr += QString::number(val) + " ";
  }
  arrayStr += "\n";
  ui->outputLable->setText(ui->outputLable->text() + arrayStr);
}

int MainWindow::binarySearch(const QVector<int>& arr, int val, int low,
                             int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] == val) {
      return mid + 1;
    } else if (arr[mid] < val) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return low;
}

void MainWindow::interpolationSort(QVector<int>& arr) {
  int n = arr.size();
  for (int i = 1; i < n; i++) {
    int val = arr[i];
    int pos = binarySearch(arr, val, 0, i - 1);

    for (int j = i - 1; j >= pos; j--) {
      arr[j + 1] = arr[j];
    }

    arr[pos] = val;
    printArray(arr, i);
  }
}

void MainWindow::on_pushButton_clicked() {
  QString text = ui->arrayInput->toPlainText();
  int rand = QRandomGenerator::global()->bounded(100);
  ui->arrayInput->setText(text + QString::number(rand) + " ");
}

void MainWindow::on_sortButton_clicked() {
  ui->outputLable->clear();
  QString input = ui->arrayInput->toPlainText();
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
    QMessageBox::information(this, "Ошибка!", "Некорректный ввод данных");
    return;
  }

  QStringList inputList = input.split(" ", QString::SkipEmptyParts);
  QVector<int> arr;

  for (const QString& str : inputList) {
    arr.push_back(str.toInt());
  }

  interpolationSort(arr);
}

void MainWindow::on_searchButton_clicked() {
  QString input = ui->arrayInput->toPlainText();
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
    QMessageBox::information(this, "Ошибка!", "Некорректный ввод данных");
    return;
  }

  QVector<int> arr;

  for (const QString& str : stringList) {
    arr.push_back(str.toInt());
  }

  // Считываем элемент для поиска
  int elementToFind = ui->elementInput->toPlainText().toInt();
  auto it = std::find(arr.begin(), arr.end(), elementToFind);

  if (it != arr.end()) {
    int index = binarySearch(arr, elementToFind, 0,
                             arr.size());  // Вычисляем индекс элемента

    int arrayLength = arr.size();
    int mod = 1000;
    int result = binpow(index, arrayLength, mod);  // Вычисляем результат
    ui->resultLabel->setText("Резульатат : " + QString::number(result));
  } else {
    ui->resultLabel->setText("Элемент не найден");
  }
}
