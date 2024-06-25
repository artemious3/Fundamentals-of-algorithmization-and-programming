#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(800, 550);
  setWindowTitle("Планеты");

  Planet_initByStr = {"Земля", 6371,  4.54,         365.25f,
                      'T',     false, {"Кислород"}, {56.7, -85.3}};

  Planet_initByEachField.name = "Юпитер";
  Planet_initByEachField.radius = 69911;
  Planet_initByEachField.age = 4.6;
  Planet_initByEachField.period = 4332.71f;
  Planet_initByEachField.type = 'G';
  Planet_initByEachField.hasRings = true;
  const char* chemElement = "Bодород";
  strcpy(Planet_initByEachField.mainChemElement, chemElement);
  Planet_initByEachField.mainChemElement[MAX_LENGTH - 1] = '\0';
  Planet_initByEachField.maxAndMinTemp[0] = -145;
  Planet_initByEachField.maxAndMinTemp[1] = 20000;

  pointer->name = QString::fromStdString("Венера");
  pointer->radius = 6052;
  pointer->age = 4.503;
  pointer->period = 224.7f;
  pointer->type = 'T';
  pointer->hasRings = false;
  strcpy(pointer->mainChemElement, "Углекислый газ");
  pointer->maxAndMinTemp[0] = 465.0;
  pointer->maxAndMinTemp[1] = -70.0;

  ref.name = QString::fromStdString("Марс");
  ref.radius = 3389;
  ref.age = 4.603;
  ref.period = 687.0;
  ref.type = 'T';
  ref.hasRings = false;
  strcpy(ref.mainChemElement, "Диоксид углерода");
  ref.maxAndMinTemp[0] = 20.0;
  ref.maxAndMinTemp[1] = -153.0;
}

MainWindow::~MainWindow() {
  delete ui;
}

QString MainWindow::toMyStr(Planet pl) {
  if (pl.name.isEmpty()) {
    QMessageBox::information(this, "Внимание",
                             "Структура не инициализирована!");
    return "";
  }
  QString result = pl.name + "\n" + QString::number(pl.radius) + " км\n" +
                   QString::number(pl.age) + " млрд.лет\n" +
                   QString::number(pl.period) + " суток\n" + pl.type +
                   " - тип \n" + (pl.hasRings ? "Есть кольца" : "Нет колец") +
                   "\n" + pl.mainChemElement + "\n" +
                   QString::number(pl.maxAndMinTemp[0]) + "°C, " +
                   QString::number(pl.maxAndMinTemp[1]) + "°C";
  return result;
}

QString MainWindow::toMyStr(MainWindow::Planet* pl) {
  if (pl->name.isEmpty()) {
    QMessageBox::information(this, "Внимание",
                             "Структура не инициализирована!");
    return "";
  }
  QString result = pl->name + "\n" + QString::number(pl->radius) + " км\n" +
                   QString::number(pl->age) + " млрд.лет\n" +
                   QString::number(pl->period) + " суток\n" + pl->type +
                   " - тип \n" + (pl->hasRings ? "Есть кольца" : "Нет колец") +
                   "\n" + pl->mainChemElement + "\n" +
                   QString::number(pl->maxAndMinTemp[0]) + "°C, " +
                   QString::number(pl->maxAndMinTemp[1]) + "°C";
  return result;
}

void MainWindow::on_addButton_clicked() {

  QString name = ui->nameTextEdit->toPlainText();

  if (name.isEmpty()) {
    QMessageBox::information(this, "Внимание", "Дайте название планете!");
  }

  int radius = ui->radiusSpinBox->value();
  double age = ui->ageSpinBox->value();
  float period = ui->periodSpinBox->value();
  QChar qtype = ui->comboBox->currentText().at(0);
  bool hasRings = ui->checkBox->isChecked();
  std::string text = ui->ElementTextEdit->toPlainText().toStdString();
  int minTemp = ui->minTempSpinBox->value();
  int maxTemp = ui->maxTempSpinBox->value();

  if (minTemp > maxTemp) {

    std::swap(minTemp, maxTemp);
  }

  int arr[] = {maxTemp, minTemp};

  Planet_initByUser = {name, radius, age, period, qtype, hasRings};

  for (int i = 0; i < 2; ++i) {
    Planet_initByUser.maxAndMinTemp[i] = arr[i];
  }

  int i = 0;
  while (text[i] != '\0') {
    Planet_initByUser.mainChemElement[i] = text[i];
    ++i;
  }

  QString textForSet = toMyStr(Planet_initByUser);
  ui->textBrowser->setText(textForSet);
}

void MainWindow::on_showButton_clicked() {

  QString text = "";
  if (ui->strRadio->isChecked()) {
    text = toMyStr(Planet_initByStr);
  }
  if (ui->fieldRadio->isChecked()) {
    text = toMyStr(Planet_initByEachField);
  }
  if (ui->userRadio->isChecked()) {
    text = toMyStr(Planet_initByUser);
  }
  if (ui->pointerRadio->isChecked()) {
    text = toMyStr(pointer);
  }
  if (ui->refRadio->isChecked()) {
    text = toMyStr(ref);
  }
  ui->textBrowser->setText(text);
}
