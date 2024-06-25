#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->table->setColumnWidth(0, BIG_COLUMN_WIDTH);

  for (int i = 1; i < COLUMN_COUNT; ++i) {
    ui->table->setColumnWidth(i, SMALL_COLUMN_WIDTH);
  }

  setFixedSize(WINDOW_LENGTH, WINDOW_WIDTH);
  ui->participantNumberSpin->setRange(0, 0);
  ui->personForFindNumberSpin->setRange(0, 0);
  ui->personForDeleteNumberSpin->setRange(0, 0);

  ui->addButton->hide();
  ui->changeButton->hide();
  ui->participantNumberSpin->hide();
  ui->participantNumberLabel->hide();

  ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow() {
  for (int i = couples.size() - 1; i >= 0; --i) {
    ui->table->removeRow(i);
    couples.removeLast();
  }
  delete ui;
}

void MainWindow::on_addRadioButton_clicked() {
  ui->customLabel->setText("ДОБАВИТЬ:");
  ui->addButton->show();
  ui->changeButton->hide();
  ui->participantNumberSpin->hide();
  ui->participantNumberLabel->hide();
}

void MainWindow::on_changeRadioButton_clicked() {
  ui->addButton->hide();
  ui->customLabel->setText("ИЗМЕНИТЬ:");
  ui->changeButton->show();
  ui->participantNumberSpin->show();
  ui->participantNumberLabel->show();
}

void MainWindow::on_OpenAction_triggered() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open file...", "/home/kat/QT/Lab2/text_data", "*.txt");
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
    return;
  }

  //удаление таблицы, если открывается другой файл
  int row = ui->table->rowCount();
  if (row != 0) {
    for (int i = couples.size() - 1; i >= 0; --i) {
      ui->table->removeRow(i);
      couples.removeLast();
    }
  }

  QTextStream in(&file);
  QString content = in.readAll(), isError = "";
  QStringList testContent = content.split('/');

  for (int i = 0; i < testContent.size(); ++i) {
    CoupleMaker* testCouple = new CoupleMaker;
    isError = helperParticipant.FileOpener(testCouple, testContent[i]);
    if (!isError.isEmpty()) {
      QMessageBox::critical(this, "Ошибка", isError + QString::number(i + 1));
      isError.clear();
      continue;
    } else {
      couples.append(*testCouple);
    }
  }

  file.close();
  addToTable(couples);
}

void MainWindow::on_SaveAction_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
      this, "Сохранить файл как...", "/home/kat/QT/Lab2/text_data", "*.txt");

  if (!fileName.isEmpty()) {
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {
      QTextStream stream(&file);
      for (int i = 0; i < couples.size(); ++i) {
        bool isNotFirst = i == 0 ? false : true;
        stream << helperParticipant.ConvertCoupleIntoText(couples[i],
                                                          isNotFirst)
               << "\n";
      }
      file.close();
      QMessageBox::information(this, "Сохранение",
                               "Данные были успешно сохранены в файл!");

    } else {
      QMessageBox::critical(this, "Ошибка",
                            "Файл не может быть открыт для записи!");
    }
  }
}

void MainWindow::addToTable() {
  QTableWidgetItem* item;
  int row = ui->table->rowCount();

  ui->table->insertRow(row);

  item = new QTableWidgetItem(helperParticipant.getFIO(couples.last()));
  ui->table->setItem(row, FIRST_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getSex(couples.last()));
  ui->table->setItem(row, SECOND_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getAge(couples.last()));
  ui->table->setItem(row, THIRD_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getHigh(couples.last()));
  ui->table->setItem(row, FORTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getWeight(couples.last()));
  ui->table->setItem(row, FIFTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getPartAge(couples.last()));
  ui->table->setItem(row, SIXTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getPartHigh(couples.last()));
  ui->table->setItem(row, SEVENTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getPartWeight(couples.last()));
  ui->table->setItem(row, EIGHTH_COLUMN, item);

  //установка максимального значения спинбоксам
  ui->participantNumberSpin->setMaximum(couples.size());
  ui->personForFindNumberSpin->setMaximum(couples.size());
  ui->personForDeleteNumberSpin->setMaximum(couples.size());
}

void MainWindow::addToTable(const QList<CoupleMaker>& people) {
  QTableWidgetItem* item;
  int row = ui->table->rowCount();

  for (const CoupleMaker& person : people) {
    ui->table->insertRow(row);

    item = new QTableWidgetItem(helperParticipant.getFIO(person));
    ui->table->setItem(row, FIRST_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getSex(person));
    ui->table->setItem(row, SECOND_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getAge(person));
    ui->table->setItem(row, THIRD_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getHigh(person));
    ui->table->setItem(row, FORTH_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getWeight(person));
    ui->table->setItem(row, FIFTH_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getPartAge(person));
    ui->table->setItem(row, SIXTH_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getPartHigh(person));
    ui->table->setItem(row, SEVENTH_COLUMN, item);

    item = new QTableWidgetItem(helperParticipant.getPartWeight(person));
    ui->table->setItem(row, EIGHTH_COLUMN, item);

    row = ui->table->rowCount();
  }

  //установка максимального значения спинбоксам
  ui->participantNumberSpin->setMaximum(couples.size());
  ui->personForFindNumberSpin->setMaximum(couples.size());
  ui->personForDeleteNumberSpin->setMaximum(couples.size());
}

void MainWindow::changeTable(const CoupleMaker& person, int index) {
  QTableWidgetItem* item;

  item = new QTableWidgetItem(helperParticipant.getFIO(person));
  ui->table->setItem(index, FIRST_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getSex(person));
  ui->table->setItem(index, SECOND_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getAge(person));
  ui->table->setItem(index, THIRD_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getHigh(person));
  ui->table->setItem(index, FORTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getWeight(person));
  ui->table->setItem(index, FIFTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getPartAge(person));
  ui->table->setItem(index, SIXTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getPartHigh(person));
  ui->table->setItem(index, SEVENTH_COLUMN, item);

  item = new QTableWidgetItem(helperParticipant.getPartWeight(person));
  ui->table->setItem(index, EIGHTH_COLUMN, item);
}

void MainWindow::on_deleteButton_clicked() {
  int index = ui->personForDeleteNumberSpin->value();

  if (index == 0) {
    QMessageBox::warning(this, "Ошибка", "Нет человека под номером 0!!!");
    return;
  }

  ui->table->removeRow(index - 1);
  couples.removeAt(index - 1);

  //установка максимального значения спинбоксамs
  ui->participantNumberSpin->setMaximum(couples.size());
  ui->personForDeleteNumberSpin->setMaximum(couples.size());
  ui->personForFindNumberSpin->setMaximum(couples.size());
}

void MainWindow::on_addButton_clicked() {
  CoupleMaker coupleForAdd;
  QString textForSet = "";

  textForSet += ui->fioEdit->toPlainText();

  if (ui->manRadioButton->isChecked()) {
    textForSet += "/Мужской/";
  }

  if (ui->womanRadioButton->isChecked()) {
    textForSet += "/Женский/";
  }
  textForSet += QString::number(ui->ageSpin->value()) + '/' +
                QString::number(ui->highSpin->value()) + '/' +
                QString::number(ui->wheightSpin->value()) + '/' +
                QString::number(ui->ageMinSpin->value()) + '-' +
                QString::number(ui->ageMaxSpin->value()) + '/' +
                QString::number(ui->highMinSpin->value()) + '-' +
                QString::number(ui->highMaxSpin->value()) + '/' +
                QString::number(ui->weightMinSpin->value()) + '-' +
                QString::number(ui->weightMaxSpin->value());

  coupleForAdd = helperParticipant.setData(coupleForAdd, textForSet);
  couples.append(coupleForAdd);
  addToTable();
}

void MainWindow::on_findButton_clicked() {
  listOfPartners.clearList();

  int index = ui->personForFindNumberSpin->value() - 1;
  if (index == -1) {
    QMessageBox::critical(this, "Ошибка", "Нет человека под номером 0!!!");
  } else {
    QString sex = couples[index].getSex(couples[index]);
    QList<CoupleMaker>* partners =
        helperParticipant.MakeList(couples, couples[index], sex);

    if (ui->sortCheckBox2->isChecked()) {
      helperParticipant.SortByAge(partners);
    }
    listOfPartners.addToList(partners, couples[index]);
    listOfPartners.show();
  }
}

void MainWindow::on_changeButton_clicked() {
  int index = ui->participantNumberSpin->value() - 1;

  if (index == -1) {
    QMessageBox::critical(this, "Ошибка", "Нет человека под номером 0!!!");
    return;
  }

  CoupleMaker coupleForChange;
  QString textForSet = "";

  textForSet += ui->fioEdit->toPlainText();

  if (ui->manRadioButton->isChecked()) {
    textForSet += "/Мужской/";
  }

  if (ui->womanRadioButton->isChecked()) {
    textForSet += "/Женский/";
  }
  textForSet += QString::number(ui->ageSpin->value()) + '/' +
                QString::number(ui->highSpin->value()) + '/' +
                QString::number(ui->wheightSpin->value()) + '/' +
                QString::number(ui->ageMinSpin->value()) + '-' +
                QString::number(ui->ageMaxSpin->value()) + '/' +
                QString::number(ui->highMinSpin->value()) + '-' +
                QString::number(ui->highMaxSpin->value()) + '/' +
                QString::number(ui->weightMinSpin->value()) + '-' +
                QString::number(ui->weightMaxSpin->value());

  coupleForChange = helperParticipant.setData(coupleForChange, textForSet);
  couples[index] = coupleForChange;
  changeTable(coupleForChange, index);
}

void MainWindow::on_calcPosibblePairsButton_clicked() {
  listOfPartners.clearList();
  QList<CoupleMaker>*women = new QList<CoupleMaker>,
  *men = new QList<CoupleMaker>;

  QList<QList<CoupleMaker>> allPairs;

  helperParticipant.Make2Lists(couples, women, men);

  if (ui->forManRadioButton->isChecked()) {
    for (const CoupleMaker& man : *men) {
      allPairs.append(*helperParticipant.MakeList(couples, man, "Мужской"));
    }
    listOfPartners.addToTotalList(*men, allPairs);
  }
  if (ui->forWomanRadioButton->isChecked()) {
    for (const CoupleMaker& woman : *women) {
      allPairs.append(*helperParticipant.MakeList(couples, woman, "Женский"));
    }
    listOfPartners.addToTotalList(*women, allPairs);
  }
  listOfPartners.show();
}
