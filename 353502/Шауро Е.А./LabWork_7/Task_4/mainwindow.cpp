#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
  delete mainTable;
  mainTable = nullptr;
}

void MainWindow::updateTable() {
  QStandardItemModel* model = new QStandardItemModel(ui->tableView);
  model->setColumnCount(2);
  model->setHorizontalHeaderLabels({"Index", "Value"});

  for (int i = 0; i < mainTable->size; ++i) {
    QStandardItem* indexItem = new QStandardItem(QString::number(i));
    QStandardItem* valueItem;

    // Проверка по значению ключа
    if (mainTable->getTable()[i] == -1) {
      valueItem = new QStandardItem("-");
    } else {
      valueItem = new QStandardItem(QString::number(mainTable->getTable()[i]));
    }

    model->setItem(i, 0, indexItem);
    model->setItem(i, 1, valueItem);
  }

  ui->tableView->setModel(model);
}

void MainWindow::on_createButton_clicked() {
  QString type = ui->typeComboBox->currentText();
  int capacity = ui->sizeComboBox->currentText().toInt();

  if (type == "Универсальное хеширование") {
    mainTable = new UniverseHT(capacity);
  }

  else if (type == "Модульное хеширование") {
    mainTable = new ModuleHT(capacity);
  }
  updateTable();
}

void MainWindow::on_findButton_clicked() {
  int key = ui->findKeySpinBox->value();
  QElapsedTimer timer;
  timer.start();
  int result = mainTable->searchByKey(key);
  qint64 elapsedTime = timer.nsecsElapsed();  // время в наносекундах

  QString output = QString("Результат поиска: %1\nВремя поиска: %2 наносекунд")
                       .arg(result == -1 ? "не найдено" : QString::number(result))
                       .arg(elapsedTime);

  if (UniverseHT* uni = dynamic_cast<UniverseHT*>(mainTable)) {
    ui->uniTextBrowser->setText(output);
  } else {
    ui->modTextBrowser->setText(output);
  }
}

void MainWindow::on_adButton_clicked() {

    if(mainTable->counter >= mainTable->size){
        QMessageBox::information(this, "INFO", "Создайте другую таблицу!");
        return;
    }
  int key = ui->keyAddSpinBox->value();
  mainTable->insert(key);
  updateTable();
}
