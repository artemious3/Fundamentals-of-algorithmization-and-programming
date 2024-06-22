#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>

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

void countElements(const QString &path, int &foldersCount, int &filesCount, Ui::MainWindow *ui) {
    QDir dir(path);

    QFileInfoList entriesIntoFile = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    for (const QFileInfo &entry : entriesIntoFile) {
        if (entry.isDir()) {
            foldersCount++;
            ui->textEdit->append("[Folder] " + entry.fileName() + "\n");
            countElements(entry.filePath(), foldersCount, filesCount, ui);
        } else if (entry.isFile()) {
            filesCount++;
            ui->textEdit->append("[File] " + entry.fileName() + "\n");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString path = "/home/";
    ui->lineEdit_3->setText(path);

    int foldersCount = 0;
    int filesCount = 0;

    countElements(path, foldersCount, filesCount, ui);

    QString foldersCountString = QString::number(foldersCount);
    ui->lineEdit_2->setText(foldersCountString);

    QString filesCountString = QString::number(filesCount);
    ui->lineEdit->setText(filesCountString);

}
