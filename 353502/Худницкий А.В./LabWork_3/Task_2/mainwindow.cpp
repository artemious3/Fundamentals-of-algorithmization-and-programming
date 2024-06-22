#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int ackermann(int mInt, int nInt) {
    if (mInt == 0) {
        return nInt + 1;
    } else if (mInt > 0 && nInt == 0) {
        return ackermann(mInt - 1, 1);
    } else if (mInt > 0 && nInt > 0) {
        return ackermann(mInt - 1, ackermann(mInt, nInt - 1));
    }
    return -1;
}

void MainWindow::on_pushButton_clicked()
{
    QString mString = ui->lineEdit_2->text();
    int mInt = mString.toInt();
    QString nString = ui->lineEdit->text();
    int nInt = mString.toInt();
    int A = ackermann(mInt, nInt);;
    QString AString = QString::number(A);
    ui->lineEdit_3->setText(AString);
}
