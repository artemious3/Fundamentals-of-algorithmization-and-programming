#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);

    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::click_add);
    connect(ui->delete_button, &QPushButton::clicked, this, &MainWindow::click_delete);
    connect(ui->finde_pushbotton, &QPushButton::clicked, this, &MainWindow::click_finde);
}

void MainWindow::click_add(){
    bst.insert(ui->add->value());
    ui->textEdit->setText(bst.print());
}

void MainWindow::click_delete(){
    bst.deleteNode(ui->Delete->value());
    ui->textEdit->setText(bst.print());
}

void MainWindow::click_finde(){
    if(bst.search(ui->finde->value())){
        QMessageBox::information(nullptr, "Information", "Элемент найден");
    }
    else {
        QMessageBox::information(nullptr, "Information", "Элемент не найден");
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
