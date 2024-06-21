#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  sourceDir = QFileDialog::getExistingDirectory(
      this, tr("Открыть директорию"), "",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  QDir dir(sourceDir);

  if (dir.exists()) {
    ui->textBrowser->clear();
    ui->textBrowser->setText(dir.dirName());
    ui->label->setText(QString::number(countDirs(dir)));
    ui->label_2->setText(QString::number(countFiles(dir, "|- ")));
  } else {
    QMessageBox::critical(this, "Ошибка", "Такой директории не существует!");
  }
}

int MainWindow::countDirs(QDir dir, bool isDot) {

    if(isDot){
        dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        int counter;
        QFileInfoList list =
            dir.entryInfoList();  // список файлов и директорий в текущей директории.
        counter += list.size();
        return counter;
    }
  int counter = 0;
  dir.setFilter(QDir::AllDirs);
  QFileInfoList list =
      dir.entryInfoList();  // список файлов и директорий в текущей директории.
  counter += list.size();

  for (const auto& fileInfo : list) {
         QString fileName = fileInfo.fileName();
         QDir tempDir(fileInfo.absoluteFilePath());

         if (fileName.startsWith('.') || fileName == "." || fileName == "..") {
           counter += countDirs(tempDir, true);
         }

         counter += countDirs(tempDir); // Рекурсивно вызываем функцию для подсчета директорий в поддиректориях
     }

  return counter;
}

int MainWindow::countFiles(QDir dir, QString prefix) {
  int counter = 0;
  dir.setFilter(QDir::Files |
                QDir::NoDotAndDotDot);  // Фильтр только для файлов
  QFileInfoList list = dir.entryInfoList();

  for (const auto& fileInfo : list) {
    if (fileInfo.isFile()) {
      ui->textBrowser->append(
          prefix +
          fileInfo.fileName());  // Добавление имени файла в текстовый браузер
      counter++;
    }
  }

  dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);  // Фильтр для всех папок
  QFileInfoList dirList = dir.entryInfoList();

  // Обработка папок в текущей директории
  for (const auto& newDir : dirList) {
    ui->textBrowser->append(prefix + newDir.fileName() + "/");
    QDir tempDir(newDir.absoluteFilePath());
    counter += countFiles(tempDir, "    " + prefix);
  }

  return counter;
}
