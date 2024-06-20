#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Обработчик нажатия на кнопку
void MainWindow::on_pushButton_clicked()
{
    // Открывает диалоговое окно для выбора директории
    sourceDir = QFileDialog::getExistingDirectory(this,
                                                  tr("Открыть директорию"),
                                                  "",
                                                  QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);

    //создаём объект класса QDir, который представляет собой выбранную директорию, путь которой сохранён в sourceDir
    QDir dir(sourceDir);

    // Проверяет существование выбранной директории
    if (dir.exists()) {
        ui->textBrowser->clear(); // Очищает содержимое текстового браузера
        ui->textBrowser->setText(
            dir.dirName()); // Устанавливает имя текущей директории в текстовом браузере
        ui->label->setText(QString::number(countDirs(dir))); // Устанавливает количество папок
        ui->label_2->setText(
            QString::number(countFiles(dir, "|- "))); // Устанавливает количество файлов
    } else {
        QMessageBox::critical(this,
                              "Ошибка",
                              "Такой директории не существует!"); // Выводит сообщение об ошибке
    }
}

// Рекурсивно считает количество папок в директории и ее поддиректориях
int MainWindow::countDirs(QDir dir)
{
    int counter = 0;
    dir.setFilter(QDir::AllDirs
                  | QDir::NoDotAndDotDot); // Устанавливает фильтр для директорий, исключая . и ..
    QFileInfoList list = dir.entryInfoList(); // Получает список файлов и папок в директории
    counter += list.size();

    for (const auto &newDir : list) {
        QDir tempDir(newDir.absoluteFilePath());
        counter += countDirs(tempDir); // Рекурсивный вызов для подсчета папок в поддиректориях
    }

    return counter;
}

int MainWindow::countFiles(QDir dir, QString prefix)
{
    int counter = 0;
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // Фильтр только для файлов
    QFileInfoList list = dir.entryInfoList(); // Список файлов в текущей директории

    // Обработка файлов в текущей директории
    for (const auto &fileInfo : list) {
        if (fileInfo.isFile()) {
            ui->textBrowser->append(
                prefix + fileInfo.fileName()); // Добавление имени файла в текстовый браузер
            counter++;
        }
    }

    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot); // Фильтр для всех папок
    QFileInfoList dirList = dir.entryInfoList(); // Список всех папок в текущей директории

    // Обработка папок в текущей директории
    for (const auto &newDir : dirList) {
        ui->textBrowser->append(prefix + newDir.fileName()
                                + "/"); // Добавление имени папки в текстовый браузер с обозначением
        //counter++;                      // Увеличение счетчика для папок
        QDir tempDir(newDir.absoluteFilePath());
        counter += countFiles(tempDir,
                              "    " + prefix); // Рекурсивный вызов для подсчета файлов в подпапках
    }

    return counter;
}
