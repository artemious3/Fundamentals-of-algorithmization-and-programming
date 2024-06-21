#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(750, 350);

    myBits = new Bits(10);
    ui->spinBox->setMaximum(myBits->getSize() - 1);
    ui->textBrowser->setText(myBits->to_string());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_getIndexButton_clicked()
{
    int index = ui->spinBox->value();
    QString text = myBits->get(index)? "Бит имеет значение True" : "Бит имеет значение False";
    QMessageBox::information(nullptr, "INFO", text);

}

void MainWindow::on_allButton_clicked()
{
    QString text = myBits->all()? "Все биты имеют значение True" : "Hе все биты имеют значение True";
    QMessageBox::information(nullptr, "INFO", text);

}

void MainWindow::on_anyButton_clicked()
{
    QString text = myBits->any()? "В последовательности есть бит со значением True" : "В последовательности нет бита со значением True";
    QMessageBox::information(nullptr, "INFO", text);
}

void MainWindow::on_countButton_clicked()
{
    int count = myBits->count();
    QString text = "Количество ненулевых бит: " + QString::number(count);
    QMessageBox::information(nullptr, "INFO", text);
}

void MainWindow::on_flipButton_clicked()
{
    myBits->flip();
    ui->textBrowser->setText(setRepresent());
}

void MainWindow::on_resetButton_clicked()
{
    myBits->reset();
    ui->textBrowser->setText(setRepresent());
}

void MainWindow::on_noneButton_clicked()
{
    QString text = myBits->none()? "В последовательности нет бита со значением True" : "В последовательности есть бит со значением True";
    QMessageBox::information(nullptr, "INFO", text);
}

void MainWindow::on_flipindexButton_clicked()
{
    int index = ui->spinBox->value();
    myBits->flip(index);
    ui->textBrowser->setText(setRepresent());
}

void MainWindow::on_setButton_clicked()
{
    myBits->set();
    ui->textBrowser->setText(setRepresent());
}

void MainWindow::on_set_indexButton_clicked()
{
    int index = ui->spinBox->value();
    myBits->set(index);
    ui->textBrowser->setText(setRepresent());
}

void MainWindow::on_getSizeButton_clicked()
{
    int size = myBits->getSize();
    QString text = "Размер: " + QString::number(size);
    QMessageBox::information(nullptr, "INFO", text);
}

void MainWindow::on_testButton_clicked()
{
    int index = ui->spinBox->value();
    QString text = myBits->get(index)? "Бит имеет значение True" : "Бит имеет значение False";
    QMessageBox::information(nullptr, "INFO", text);
}

QString MainWindow::setRepresent()
{
    if(ui->to_stringButton->isChecked()){
        return myBits->to_string();
    }
    if(ui->to_ulongButton->isChecked()){
        return QString::number(myBits->to_ulong());
    }
    if(ui->to_ullongButton->isChecked()){
        return QString::number(myBits->to_ullong());
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->setText(setRepresent());
}
