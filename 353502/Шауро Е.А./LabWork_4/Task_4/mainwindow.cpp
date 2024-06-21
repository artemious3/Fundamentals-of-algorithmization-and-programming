#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(720, 470);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_assignButton_clicked() {
  vector.assign({1, 2, 3, 4, 5, 6, 7, 8});
  QString text = "Назначены значения: {1, 2, 3, 4, 5, 6, 7, 8}";
  showMessage(text);
  updateBrowsers();
}

void MainWindow::on_atButton_clicked() {
  try {
    int value = vector.at(1);
    QString text = QString("Элемент по индексу 1: %1").arg(value);
    showMessage(text);
  } catch (const std::out_of_range& e) {
    QString text = "Индекс вне диапазона";
    showMessage(text);
  }
}

void MainWindow::on_backButton_clicked() {
  try {
    int value = vector.back();
    QString text = QString("Последний элемент: %1").arg(value);
    showMessage(text);
  } catch (const std::out_of_range& e) {
    QString text = "Вектор пуст";
    showMessage(text);
  }
}

void MainWindow::on_beginButton_clicked() {
  auto it = vector.begin();
  QString text = QString("Итератор begin указывает на: %1").arg(*it);
  showMessage(text);
}

void MainWindow::on_capacityButton_clicked() {
  QString text = QString("Емкость: %1").arg(vector.capacity());
  showMessage(text);
}

void MainWindow::on_reserveButton_clicked() {
  vector.reserve(5);
  QString text = "Зарезервировано место для 5 элементов";
  showMessage(text);
}

void MainWindow::on_cbeginButton_clicked() {
  auto it = vector.cbegin();
  QString text = QString("Константный итератор cbegin указывает на: %1").arg(*it);
  showMessage(text);
}

void MainWindow::on_clearButton_clicked() {
  vector.clear();
  QString text = "Вектор очищен";
  updateBrowsers();
  showMessage(text);
}

void MainWindow::on_dataButton_clicked() {
  auto data = vector.data();
  QString text = QString("Указатель на данные: %1")
                  .arg(reinterpret_cast<uintptr_t>(data));
  showMessage(text);
}

void MainWindow::on_emplaceButton_clicked() {
  vector.emplace(vector.begin() + 0, 24);
  QString text = "Добавлено значение 24 на позицию 0";
  updateBrowsers();
  showMessage(text);
}

void MainWindow::on_emplace_back_Button_clicked() {
  vector.emplace_back(100);
  QString text = "Добавлено значение 100 в конец";
  updateBrowsers();
  showMessage(text);
}

void MainWindow::on_resizeButton_clicked() {
  vector.resize(8);
  QString text = "Размер вектора изменен до 8 элементов";
  updateBrowsers();
  showMessage(text);
}

void MainWindow::on_emptyButton_clicked() {
  bool isEmpty = vector.empty();
  QString text = QString("Является ли вектор пустым? %1").arg(isEmpty ? "\nДа" : "\nНет");
  showMessage(text);
}

void MainWindow::on_eraseButton_clicked() {
  vector.erase(vector.begin());
  QString text = "Удален первый элемент";
  showMessage(text);
  updateBrowsers();
}

void MainWindow::on_frontButton_clicked() {
  try {
    int value = vector.front();
    QString text = QString("Первый элемент: %1").arg(value);
    showMessage(text);
  } catch (const std::out_of_range& e) {
        QString text = "Вектор пуст";
        showMessage(text);
  }
}

void MainWindow::on_insertButton_clicked() {
  vector.insert(vector.begin(), 30);
  QString text = "Добавлено значение 30 в начало";
  showMessage(text);
  updateBrowsers();
}

void MainWindow::on_sizeButton_clicked() {
  QString text = QString("Размер: %1").arg(vector.size());
  showMessage(text);
}

void MainWindow::on_max_size_Button_clicked() {
  QString text = QString("Максимальный размер: %1").arg(vector.max_size());
  showMessage(text);
}

void MainWindow::on_pop_back_Button_clicked() {
  try {
    vector.pop_back();
    QString text = "Удален последний элемент";
    showMessage(text);
    updateBrowsers();
  } catch (const std::out_of_range& e) {
    QString text = "Вектор пуст";
    showMessage(text);
  }
}

void MainWindow::on_push_back_Button_clicked() {
  vector.push_back(40);
  QString text = "Добавлено значение 40 в конец";
  showMessage(text);
  updateBrowsers();
}

void MainWindow::on_swapButton_clicked() {
  NewVector<int> other;
  other.assign({50, 60});
  vector.swap(other);
  QString text = "Вектор обменян с другим вектором {50, 60}";
  showMessage(text);
  updateBrowsers();
}

void MainWindow::setupUI() {
  tableWidgetInt = new QTableWidget(this);
  tableWidgetPair = new QTableWidget(this);

  QVBoxLayout* verticalLayout = new QVBoxLayout();
  verticalLayout->addWidget(tableWidgetInt);
  verticalLayout->addWidget(tableWidgetPair);

  QWidget* container = new QWidget();
  container->setLayout(verticalLayout);
  setCentralWidget(container);
}

void MainWindow::populateTables() {

    for(double i =0; i <= 9; ++i){
          intVector.push_back(i);
          pairVector.push_back(NewPair<int, double>(i, float(i/10 + i)));
    }

  tableWidgetInt->setRowCount(intVector.size());
  tableWidgetInt->setColumnCount(1);
  for (size_t i = 0; i < intVector.size(); ++i) {
    tableWidgetInt->setItem(
        i, 0, new QTableWidgetItem(QString::number(intVector.at(i))));
  }

  tableWidgetPair->setRowCount(pairVector.size());
  tableWidgetPair->setColumnCount(2);
  for (size_t i = 0; i < pairVector.size(); ++i) {
    tableWidgetPair->setItem(
        i, 0, new QTableWidgetItem(QString::number(pairVector.at(i).first)));
    tableWidgetPair->setItem(
        i, 1, new QTableWidgetItem(QString::number(pairVector.at(i).second)));
  }
}

void MainWindow::updateBrowsers() {
  int* data = vector.data();
  std::size_t size = vector.size();
  ui->vector_content_textBrowser->clear();

  // Выводим содержимое вектора в textBrowser
  for (std::size_t i = 0; i < size; ++i) {
    ui->vector_content_textBrowser->append(QString::number(data[i]));
  }
}

void MainWindow::showMessage(const QString& str) {
  QMessageBox::information(this, "INFO", str);
}

void MainWindow::on_actionPair_triggered()
{
    setupUI();
    populateTables();
}
