#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hashtable = new HashTableChild<QString>(97);

    hashtable->print(ui->listWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listUpdate()
{
    hashtable->print(ui->listWidget);
}

void MainWindow::on_insertButton_clicked()
{
    hashtable->insert(ui->insertKey->value(), ui->insertValue->text());
    listUpdate();
}


void MainWindow::on_removeButton_clicked()
{
    hashtable->remove(ui->insertKey->value());
    listUpdate();

    ui->getValue->clear();
}


void MainWindow::on_getButton_clicked()
{
    ui->getValue->setText(hashtable->get(ui->insertKey->value()));
    if(ui->getValue->text() == "dog") ui->getValue->setText("Not founded");
}


void MainWindow::on_removeEvenKeys_clicked()
{
    Item<QString> maxItem = hashtable->findMaxKeyItem();
    ui->getValue->setText(maxItem.value);
    listUpdate();
}


void MainWindow::on_insertButton_2_clicked()
{
    hashtable->clear();

    for(int i = 0; i < ui->countGenerate->value(); i++)
    {
        int key = rand() % 100;
        QString str;

        for(int j = 0; j < rand() % 10 + 1; j++)
        {
            str += QString::number(rand() % 19 + 17);
        }

        hashtable->insert(key, str);
    }

    listUpdate();
}
