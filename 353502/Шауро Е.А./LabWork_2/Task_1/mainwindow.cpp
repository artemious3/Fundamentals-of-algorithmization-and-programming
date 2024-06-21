#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  for (int i = 0; i < COLUMN_COUNT; ++i) {
    ui->table->setColumnWidth(i, COLUMN_WIDTH);
  }

  setFixedSize(WINDOW_LENGTH, WINDOW_WIDTH);
  birthdayDate.setDate(MY_BD_YEAR, MY_BD_MONTH, MY_BD_DAY);

  //установка спинбоксов на 0
  ui->updateNumSpin->setRange(0, 0);
  ui->deleteNumSpin->setRange(0, 0);
  ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow() {
  dateList.clear();
  delete ui->table;
  ui->table = nullptr;  // Обнуляем указатель
  delete ui;
}

void MainWindow::on_Openaction_triggered() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open file...", "/home/kat/QT/Lab2/text_data", "*.txt");
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(nullptr, "Error", "Failed to open the file.");
    return;
  }

  //удаление таблицы, если открывается другой файл
  if (wasFileOpen) {
    for (int i = dateList.size() - 1; i >= 0; --i) {
      ui->table->removeRow(i);
      dateList.removeLast();
    }
  }

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    QDate date = QDate::fromString(line, "yyyy-MM-dd");

    if (date.isValid()) {
      dateList.append(date);
    } else {
      QMessageBox::critical(nullptr, "Error", "Invalid date format: " + line);
    }
  }

  file.close();
  int row = ui->table->rowCount();

  //добавление записей из файла в таблицу
  for (int i = 0; i < dateList.size(); ++i, row = ui->table->rowCount()) {
    ui->table->insertRow(row);
    QTableWidgetItem* dateItem =
        new QTableWidgetItem(dateList[i].toString("yyyy-MM-dd"));
    ui->table->setItem(row, 0, dateItem);
  }

  //установка максимального значения спинбоксам
  ui->updateNumSpin->setMaximum(dateList.size());
  ui->deleteNumSpin->setMaximum(dateList.size());
  wasFileOpen = true;
}

void MainWindow::on_Saveasaction_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save file as...", "/home/kat/QT/Lab2/text_data", "*.txt");

  if (!fileName.isEmpty()) {
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {
      QTextStream stream(&file);
      for (const QDate& date : dateList) {
        stream << date.toString("yyyy-MM-dd") << "\n";
      }
      file.close();
      QMessageBox::information(this, "Saving",
                               "The data was successfully saved to a file");

    } else {
      QMessageBox::critical(this, "Error",
                            "The file could not be opened for writing.");
    }
  }
}

void MainWindow::on_NextDayButton_clicked() {
  QDate lastDate{LASTYEAR, LASTMONTH, LASTDAY};
  for (int i = 0; i < dateList.size(); ++i) {
    QDate nextDate = helperDate.NextDay(dateList[i]);
    ui->table->setItem(i, FIRST_COLUMN,
                       new QTableWidgetItem(nextDate.toString("yyyy-MM-dd")));

    if (dateList[i] == lastDate) {
      ui->table->setItem(i, FIRST_COLUMN, new QTableWidgetItem("No next date"));
    }
  }
}

void MainWindow::on_PreviosDayButton_clicked() {
  QDate firstDate{0001, 01, 01};
  for (int i = 0; i < dateList.size(); ++i) {
    QDate previosDate = helperDate.PreviosDay(dateList[i]);
    ui->table->setItem(
        i, SECOND_COLUMN,
        new QTableWidgetItem(previosDate.toString("yyyy-MM-dd")));

    if (dateList[i] == firstDate) {
      ui->table->setItem(i, SECOND_COLUMN,
                         new QTableWidgetItem("No previos date"));
    }
  }
}

void MainWindow::on_IsLeapButton_clicked() {
  QString resultString = "";

  for (int i = 0; i < dateList.size(); ++i) {
    bool isLeapYear = helperDate.IsLeap(dateList[i].year());
    resultString = isLeapYear ? "true" : "false";
    ui->table->setItem(i, THIRD_COLUMN,
                       new QTableWidgetItem(QString(resultString)));
  }
}

void MainWindow::on_WeekNumberButton_clicked() {
  for (int i = 0; i < dateList.size(); ++i) {
    int16_t weekNum = helperDate.WeekNumber(dateList[i]);
    ui->table->setItem(i, FORTH_COLUMN,
                       new QTableWidgetItem(QString::number(weekNum)));
  }
}

void MainWindow::on_DurationButton_clicked() {
  for (int i = 1; i < dateList.size(); ++i) {
    int64_t duration = helperDate.Duration(dateList[i - 1], dateList[i]);
    ui->table->setItem(i, FIFTH_COLUMN,
                       new QTableWidgetItem(QString::number(duration)));
  }

  ui->table->setItem(0, FIFTH_COLUMN, new QTableWidgetItem("No previos date"));
}

void MainWindow::on_selectButton_clicked() {
  QString stringDate = ui->enterBD->toPlainText();
  QDate dateOfBD = QDate::fromString(stringDate, "yyyy-MM-dd");

  if (dateOfBD.isValid()) {
    QMessageBox::information(
        this, "Data updated",
        "New birthday set\nPlease press button 'Days till BD' to see a result");
    birthdayDate = dateOfBD;
  } else {
    QMessageBox::warning(this, "Error",
                         "Incorrect format of the entered data!\nDefault "
                         "birthday applied: 2006-09-15");
    return;
  }
}

void MainWindow::on_DaysTillBDButton_clicked() {
  for (int i = 0; i < dateList.size(); ++i) {
    int days = helperDate.DaysTillMyBirthday(birthdayDate, dateList[i]);
    QString helperString = (days == 0 || days == DAYSINFOURYEARS) ? "This is your BD!"
                                                       : QString::number(days);
    ui->table->setItem(i, SIXTH_COLUMN, new QTableWidgetItem(helperString));
  }
}

void MainWindow::on_addButton_clicked() {
  QString stringDate = ui->enterAddDate->toPlainText();
  QDate dateForAdd = QDate::fromString(stringDate, "yyyy-MM-dd");

  if (!dateForAdd.isValid()) {
    QMessageBox::warning(
        this, "Error",
        "Incorrect format of the entered data!\nCurrent date was added");
    dateForAdd = helperDate.getCurDate();
  }

  dateList.append(dateForAdd);

  int row = ui->table->rowCount();
  ui->table->insertRow(row);
  ui->table->setItem(row, 0,
                     new QTableWidgetItem(dateForAdd.toString("yyyy-MM-dd")));

  //установка максимального значения спинбоксам
  ui->updateNumSpin->setMaximum(dateList.size());
  ui->deleteNumSpin->setMaximum(dateList.size());
}

void MainWindow::on_deleteButton_clicked() {
  int index = ui->deleteNumSpin->value();

  if (index == 0) {
    QMessageBox::warning(this, "Error", "There is no dates to delete");
    return;
  }

  ui->table->removeRow(index - 1);
  dateList.removeAt(index - 1);

  //установка максимального значения спинбоксам
  ui->updateNumSpin->setMaximum(dateList.size());
  ui->deleteNumSpin->setMaximum(dateList.size());
}

void MainWindow::on_updateButton_clicked() {
  int index = ui->updateNumSpin->value();

  if (index == 0) {
    QMessageBox::warning(this, "Error", "There is no dates to update");
    return;
  }

  QString stringDate = ui->enterUpdateDate->toPlainText();

  QDate dateForUpdate = QDate::fromString(stringDate, "yyyy-MM-dd");

  if (!dateForUpdate.isValid()) {
    QMessageBox::warning(this, "Error",
                         "Incorrect format of the entered data!");
    return;
  }

  dateList[index - 1] = dateForUpdate;
  ui->table->setItem(
      index - 1, 0, new QTableWidgetItem(dateForUpdate.toString("yyyy-MM-dd")));
  QMessageBox::information(
      this, "Data updated",
      "New date set\nPlease press buttons again to see a result");
}
