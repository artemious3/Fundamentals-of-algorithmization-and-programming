#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(350, 650);
  ui->enterSizeLabel->hide();
  ui->arraySizeSpinBox->hide();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_checkPunctsButton_clicked() {

  Form* form = new Form();
  form->show();
}

void MainWindow::on_action_3_triggered() {
  close();
}

void MainWindow::on_chooseButtojn_clicked() {
  ui->textBrowser->clear();
  int index = ui->spinBox->value();

  switch (index) {
    case 1:
      connect(ui->textEdit, &QTextEdit::textChanged, this,
              &MainWindow::textSaving);
      break;
    case 2:
      readTextFromFile("ШауроЛаб20.txt");
      break;
    case 3:
      ui->inLabel->setText("Введите числовой массив\n через пробел");
      ui->enterSizeLabel->show();
      ui->arraySizeSpinBox->show();
      connect(ui->textEdit, &QTextEdit::textChanged, this,
              &MainWindow::arrSaving);
      break;
    case 4:
      readArrayFromFile();
      break;
    case 5:
      ui->inLabel->setText("Введите структуру 'Планета'");
      connect(ui->textEdit, &QTextEdit::textChanged, this,
              &MainWindow::structSaving);
      break;

    case 6:
      readTextFromFile("ШауроЛаб20_1.txt");
      break;

    case 7:
      ui->inLabel->setText("Введите структуру 'Планета'");
      connect(ui->textEdit, &QTextEdit::textChanged, this,
              &MainWindow::saveToBinary);
      break;
    case 8:
      readFromBinary();
      break;
    case 9:
      ui->inLabel->setText("Введите предложение");
      connect(ui->textEdit, &QTextEdit::textChanged, this,
              &MainWindow::sentSaving);
      break;
    case 10:
      readTextFromFile("ШауроЛаб20_3.txt");
    case 11:
      close();
      break;
  }
}

// прописать ифами файлнейм зависящий от спинбокс
void MainWindow::textSaving() {

  QString text = ui->textEdit->toPlainText();

  if (!text.contains('\n')) {
    return;
  }

  QFile file("ШауроЛаб20.txt");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Cannot open file for writing");
    return;
  }

  QTextStream out(&file);

  for (QChar ch : text) {
    out << ch;
  }

  file.close();
  QMessageBox::information(this, "Success", "Text saved to ШауроЛаб20.txt");

  ui->textEdit->clear();
  disconnect(ui->textEdit, &QTextEdit::textChanged, this,
             &MainWindow::textSaving);
}

void MainWindow::arrSaving() {

  QString input = ui->textEdit->toPlainText();

  if (input.isEmpty()) {
    return;
  }
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
    QMessageBox::critical(this, "Ошибка!", "Некорректный числовой формат!");
    return;
  }

  if (ui->arraySizeSpinBox->value() != stringList.size()) {
    return;
  }

  QFile file("ШауроЛаб20_0.txt");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Cannot open file for writing");
    return;
  }

  QTextStream out(&file);
  int16_t* array = new int16_t[stringList.size()];

  for (int i = 0; i < stringList.size(); ++i) {
    array[i] = stringList[i].toInt();
    out << stringList[i] << ")";
  }

  file.close();
  QMessageBox::information(this, "Success", "Text saved to ШауроЛаб20_0.txt");

  ui->textEdit->clear();
  ui->arraySizeSpinBox->setValue(0);

  disconnect(ui->textEdit, &QTextEdit::textChanged, this,
             &MainWindow::arrSaving);

  ui->enterSizeLabel->hide();
  ui->arraySizeSpinBox->hide();
  ui->inLabel->setText("ВВОД");
}

void MainWindow::structSaving() {
  QString input = ui->textEdit->toPlainText();
  ui->inLabel->setText("Введите структуру");

  if (input.count("\n") != 8) {
    return;
  }

  QStringList stringList = input.split('\n', QString::SkipEmptyParts);
  bool isCorrectInput = true;

  stringList[1].toInt(&isCorrectInput);
  stringList[2].toDouble(&isCorrectInput);
  stringList[3].toFloat(&isCorrectInput);

  if (!isCorrectInput) {
    QMessageBox::critical(this, "Ошибка!", "Некорректный числовой формат!");
    ui->textEdit->clear();
    return;
  }

  QFile file("ШауроЛаб20_1.txt");
  if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    QTextStream out(&file);

    for (auto str : stringList) {
      out << str << '|';
    }
    out << '\n';
    file.close();
    QMessageBox::information(this, "Success", "Text saved to ШауроЛаб20_1.txt");
    ui->textEdit->clear();
    disconnect(ui->textEdit, &QTextEdit::textChanged, this,
               &MainWindow::structSaving);
  }
}

void MainWindow::saveToBinary() {
  QString text = ui->textEdit->toPlainText();

  if (text.count("\n") != 8) {
    return;
  }

  QStringList stringList = text.split('\n', QString::SkipEmptyParts);
  bool isCorrectInput = true;

  stringList[1].toInt(&isCorrectInput);
  stringList[2].toDouble(&isCorrectInput);
  stringList[3].toFloat(&isCorrectInput);

  if (!isCorrectInput) {
    QMessageBox::critical(this, "Ошибка!", "Некорректный числовой формат!");
    ui->textEdit->clear();
    return;
  }

  QFile file("ШауроЛаб20_2.bin");

  if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
    QMessageBox::warning(this, "Error", "Cannot open file for writing");
    return;
  }

  for (QChar ch : text) {
    wchar_t wchar = ch.unicode();
    file.write(reinterpret_cast<const char*>(&wchar), sizeof(wchar));
  }

  file.close();
  QMessageBox::information(this, "Success", "Text saved to ШауроЛаб20_2.bin");
  ui->textEdit->clear();
  disconnect(ui->textEdit, &QTextEdit::textChanged, this,
             &MainWindow::saveToBinary);
}

void MainWindow::sentSaving() {
  QString text = ui->textEdit->toPlainText();

  if (!text.contains('\n') &&
      (!text.contains('.') || !text.contains('!') || !text.contains('?'))) {
    return;
  }

  QFile file("ШауроЛаб20_3.txt");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Cannot open file for writing");
    return;
  }

  QTextStream out(&file);
  out << text;

  file.close();
  QMessageBox::information(this, "Success", "Text saved to ШауроЛаб20_3.txt");

  ui->textEdit->clear();
  disconnect(ui->textEdit, &QTextEdit::textChanged, this,
             &MainWindow::sentSaving);
}

void MainWindow::readFromBinary() {
  QFile file("ШауроЛаб20_2.bin");
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, "Error", "Cannot open file for reading");
    return;
  }

  QString textData;
  wchar_t buffer;

  while (!file.atEnd()) {
    qint64 bytesRead =
        file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
    if (bytesRead == -1) {
      QMessageBox::warning(this, "Error", "Error reading from file");
      file.close();
      return;
    }

    if (QChar(buffer) == '\n') {
      textData.append(';');
    }
    textData.append(QChar(buffer));
  }

  file.close();
  ui->textBrowser->setText(textData);
}

void MainWindow::readTextFromFile(QString filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Cannot open file for reading");
    return;
  }

  QTextStream in(&file);
  QString text;

  QChar ch;
  while (!in.atEnd()) {
    in >> ch;
    text.append(ch);
  }

  file.close();

  // Устанавливаем текст в textBrowser
  ui->textBrowser->setText(text);
}

void MainWindow::readArrayFromFile() {
  QFile file("ШауроЛаб20_0.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Cannot open file for reading");
    return;
  }

  QTextStream in(&file);
  QString text;

  QChar ch;
  while (!in.atEnd()) {
    in >> ch;
    ch = ch == ')' ? ' ' : ch;
    text.append(ch);
  }

  file.close();
  ui->textBrowser->setText(text);
  disconnect(ui->textEdit, &QTextEdit::textChanged, this,
             &MainWindow::structSaving);
}

void MainWindow::readStructFromFile() {

  QFile file("ШауроЛаб20_1.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::warning(this, "Error", "Cannot open file for reading");
    return;
  }

  QTextStream in(&file);
  QString text;

  QChar ch;
  while (!in.atEnd()) {
    in >> ch;
    text.append(ch);
  }

  file.close();

  // Устанавливаем текст в textBrowser
  ui->textBrowser->setText(text);
}
