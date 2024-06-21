#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(800, 350);

  const char* exampleText = "The quick brown fox jumps over the lazy dog.";
  const char* str = "Hello, world!";

  text = exampleText;
  secondStr = str;

  ui->textEdit->setText(exampleText);
  ui->secondEdit->setText(str);
  ui->spinBox->setMaximum(secondStr.length());

  std::cout << text;
  connect(ui->textEdit, &QTextEdit::textChanged, this,
          &MainWindow::changeMainText);
  connect(ui->secondEdit, &QTextEdit::textChanged, this,
          &MainWindow::changeSecondText);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_lengthButton_clicked() {
  QMessageBox::information(this, "INFO",
                           QString("Длина строки: %1").arg(text.length() + 1));
}

void MainWindow::changeMainText() {
  QString newText = ui->textEdit->toPlainText();
  text = newText;
}

void MainWindow::changeSecondText() {

  QString newText = ui->secondEdit->toPlainText();
  secondStr = newText;
  ui->spinBox->setMaximum(secondStr.length());
}

void MainWindow::on_beginButton_clicked() {
  QMessageBox::information(
      this, "INFO", QString("begin() указывает на '%1'").arg(*text.begin()));
}

void MainWindow::on_endButton_clicked() {
  QMessageBox::information(
      this, "INFO", QString("end() указывает на '%1'").arg(*(text.end() - 1)));
}

void MainWindow::on_memcpyButtonButton_clicked() {

  void* str = text.begin();
  const char* source = secondStr.begin();

  text.memcpy(str, source, secondStr.length());
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_memmoveButton_clicked() {
  void* str = text.begin();
  const char* source = secondStr.begin();

  text.memmove(str, source, secondStr.length());
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_strcpyButton_clicked() {

  char* str = text.begin();
  const char* source = secondStr.begin();

  text.strcpy(str, source);
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_strncpyButton_clicked() {
  char* str = text.begin();
  const char* source = secondStr.begin();

  text.strncpy(str, source, ui->spinBox->value());
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_strcatButton_clicked() {
  char* str1 = text.begin();
  const char* str2 = secondStr.begin();

  text.strcat(str1, str2);
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_strncatButton_clicked() {
  char* str1 = text.begin();
  const char* str2 = secondStr.begin();

  text.strncat(str1, str2, ui->spinBox->value());
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_memcmpButton_clicked() {
  char* str1 = text.begin();
  const char* str2 = secondStr.begin();

  int a = text.memcmp(str1, str2, ui->spinBox->value());
  QMessageBox::information(this, "INFO",
                           a == 0 ? "Строки равны"
                           : a == -1 ? "Строка 1 меньше строки 2"
                                     : "Строка 1 больше строки 2");
}

void MainWindow::on_strcmpButton_clicked() {
  char* str1 = text.begin();
  const char* str2 = secondStr.begin();

  int a = text.strcmp(str1, str2);
  QMessageBox::information(this, "INFO", QString("Разница: %1").arg(a));
}

void MainWindow::on_strncmpButton_clicked() {
  char* str1 = text.begin();
  const char* str2 = secondStr.begin();

  int a = text.strncmp(str1, str2, ui->spinBox->value());
  QMessageBox::information(this, "INFO", QString("Разница: %1").arg(a));
}

void MainWindow::on_strcollButton_clicked() {
  char* str1 = text.begin();
  const char* str2 = secondStr.begin();

  int a = text.strcoll(str1, str2);
  QMessageBox::information(this, "INFO",
                           a == 0 ? "Строки равны по локали"
                           : a == -1 ? "Строка 1 меньше строки 2 по локали"
                                     : "Строка 1 больше строки 2 по локали");
}

void MainWindow::on_strxfrmButton_clicked() {
  char* str = text.begin();
  const char* source = secondStr.begin();

  int a = text.strxfrm(str, source, ui->spinBox->value());
  QMessageBox::information(this, "INFO",
                           QString("Для записи необходимо %1 байт").arg(a));
}

void MainWindow::on_strtokButton_clicked() {
  QMessageBox::information(this, "INFO", "По умолчанию - разделитель 'o, e'");

  char* str = text.begin();
  const char* delimiters = "oe";
  char* token = text.strtok(str, delimiters);
  QString message = "";

  while (token != nullptr) {
    message += token;
    message += '\n';
    token = text.strtok(nullptr, delimiters);
  }
  QMessageBox::information(this, "INFO", message);
}

void MainWindow::on_memsetButton_clicked() {
  char* str = text.begin();
  text.memset(str, 'h', ui->spinBox->value());
  ui->textEdit->setText(text.begin());
}

void MainWindow::on_strerrorButton_pressed() {
  ui->spinBox->setMaximum(3);
}

void MainWindow::on_strerrorButton_clicked() {
  char* message = text.strerror(ui->spinBox->value());
  QMessageBox::information(this, "INFO", QString("Ошибка: %1").arg(message));
}

void MainWindow::on_strcharButton_clicked() {
  QMessageBox::information(
      this, "INFO",
      QString("Найден элемент 'e': '%1'").arg(text.strchr(text.begin(), 'e')));
}

void MainWindow::on_strerrorButton_released()
{
      ui->spinBox->setMaximum(secondStr.length());
}
