#include "mainwindow.h"
#include "qtablewidget.h"
#include "ui_mainwindow.h"
#include "const.h"
#include "sick.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->table->setColumnWidth(0, BIG_COLUMN_WIDTH);

  for (int i = 1; i < COLUMN_COUNT; ++i) {
    ui->table->setColumnWidth(i, SMALL_COLUMN_WIDTH);
  }

  setFixedSize(WINDOW_LENGTH, WINDOW_WIDTH);
  ui->NumberSpin->setRange(0, 0);
  ui->AgeSpin_3->setRange(0, 0);
  ui->DiagnozSpin_2->setRange(0, 0);
}

MainWindow::~MainWindow() {
  for (int i = sicks.size() - 1; i >= 0; --i) {
    ui->table->removeRow(i);
    sicks.removeLast();
  }
}

void MainWindow::on_OpenAction_triggered() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open file...", "/home/alhudnitskii/Labs_QT/Lab2/text", "*.txt");
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(nullptr, "Ошибка.", "Не удалось открыть файл.");
    return;
}

  QTextStream in(&file);
  QString content = in.readAll(), isError = "";
  QStringList testContent = content.split('/');
  int counter = 1;

  for (int i = 0; i < (testContent.size() / 7) + 1; ++i) {
    isError = helpersick.FileOpener(sicks, testContent[i], counter);
    if (!isError.isEmpty()) {
      QMessageBox::critical(this, "Ошибка", isError + QString::number(i + 1));
      isError.clear();
      continue;
    } else {
      sicks.append(testContent[i]);
    }
  }

  file.close();
  //addToTable(sicks);
}

void MainWindow::on_SaveAction_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Сохранить файл как...", "/home/alhudnitskii/Labs_QT/Lab2/text", "*.txt");

  if (!fileName.isEmpty()) QFile file(fileName);

  if (file.open(QIODevice::WriteOnly)) {
      QTextStream stream(&file);
      for (int i = 0; i < sicks.size(); ++i) {
        bool isNotFirst = i == 0 ? false : true;
        stream << sicks.ConvertCoupleIntoText(sicks[i],
                                                          isNotFirst)
               << "\n";
      }
      file.close();
      QMessageBox::information(this, "Сохранение.",
                               "Данные были успешно сохранены в файл!");

    } else {
      QMessageBox::critical(this, "Ошибка.",
                            "Файл не может быть открыт для записи!");
    }
}
}



QString CoupleConvertCoupleIntoText (const Sick& sick, bool isNotFirst) {
  QString text = "";
  if (isNotFirst) {
    text += '/';
  }
  text += QString::number(sick.number) + '\n' +
          QString::number(sick.FIO) + '\n' +
          QString::number(sick.sex) + '\n' +
          QString::number(sick.age) + '\n' +
          QString::number(sick.diagnoz) + '\n' +
          QString::number(sick.admissionDate) + '\n' +
          QString::number(sick.extraxtDate);
  return text;
}

void MainWindow::addToTable() {
  QTableWidgetItem* item;
  int row = ui->table->rowCount();

  ui->table->insertRow(row);

  item = new QTableWidgetItem(helpersick.getNumber(sicks.last()));
  ui->table->setItem(row, 1, item);

  item = new QTableWidgetItem(helpersick.getFIO(sicks.last()));
  ui->table->setItem(row, 2, item);

  item = new QTableWidgetItem(helpersick.getSex(sicks.last()));
  ui->table->setItem(row, 3, item);

  item = new QTableWidgetItem(helpersick.getAge(sicks.last()));
  ui->table->setItem(row, 4, item);

  item = new QTableWidgetItem(helpersick.getDiagnoz(sicks.last()));
  ui->table->setItem(row, 5, item);

  item = new QTableWidgetItem(helpersick.getAdmissionDate(sicks.last()));
  ui->table->setItem(row, 6, item);

  item = new QTableWidgetItem(helpersick.getExtractDate(sicks.last()));
  ui->table->setItem(row, 8, item);

  ui->personForDeleteNumberSpin->setMaximum(sicks.size());
}

void MainWindow::addToTable(const QList<Sick>& people) {
  QTableWidgetItem* item;
  int row = ui->table->rowCount();

  for (const Sick& person : people) {
    ui->table->insertRow(row);

    item = new QTableWidgetItem(helpersick.getNumber(sicks.last()));
    ui->table->setItem(row, 1, item);

    item = new QTableWidgetItem(helpersick.getFIO(sicks.last()));
    ui->table->setItem(row, 2, item);

    item = new QTableWidgetItem(helpersick.getSex(sicks.last()));
    ui->table->setItem(row, 3, item);

    item = new QTableWidgetItem(helpersick.getAge(sicks.last()));
    ui->table->setItem(row, 4, item);

    item = new QTableWidgetItem(helpersick.getDiagnoz(sicks.last()));
    ui->table->setItem(row, 5, item);

    item = new QTableWidgetItem(helpersick.getAdmissionDate(sicks.last()));
    ui->table->setItem(row, 6, item);

    item = new QTableWidgetItem(helpersick.getExtractDate(sicks.last()));
    ui->table->setItem(row, 7, item);

    row = ui->table->rowCount();
  }

  ui->personForDeleteNumberSpin->setMaximum(sicks.size());
}

void MainWindow::changeTable(const Sick& person, int index) {
  QTableWidgetItem* item;
  int row = ui->table->rowCount();
  item = new QTableWidgetItem(helpersick.getNumber(sicks.last()));
  ui->table->setItem(row, 1, item);

  item = new QTableWidgetItem(helpersick.getFIO(sicks.last()));
  ui->table->setItem(row, 2, item);

  item = new QTableWidgetItem(helpersick.getSex(sicks.last()));
  ui->table->setItem(row, 3, item);

  item = new QTableWidgetItem(helpersick.getAge(sicks.last()));
  ui->table->setItem(row, 4, item);

  item = new QTableWidgetItem(helpersick.getDiagnoz(sicks.last()));
  ui->table->setItem(row, 5, item);

  item = new QTableWidgetItem(helpersick.getAdmissionDate(sicks.last()));
  ui->table->setItem(row, 6, item);

  item = new QTableWidgetItem(helpersick.getExtractDate(sicks.last()));
  ui->table->setItem(row, 7, item);
}

void MainWindow::on_deleteButton_clicked() {
  int index = ui->personForDeleteNumberSpin->value();

  if (index == 0) {
    QMessageBox::warning(this, "Ошибка", "Нет человека под номером 0!!!");
    return;
  }

  ui->table->removeRow(index - 1);
  sicks.removeAt(index - 1);

  ui->personForDeleteNumberSpin->setMaximum(sicks.size());
}

