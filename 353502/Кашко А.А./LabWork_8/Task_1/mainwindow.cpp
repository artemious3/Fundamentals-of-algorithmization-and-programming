#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "binarytree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tree = new BinaryTree<int>();
    tree->add(50);
    tree->add(30);
    tree->add(70);
    tree->add(20);
    tree->add(40);
    tree->add(60);
    tree->add(80);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tree;
}

void MainWindow::setupModelData(QStandardItemModel *model, Node<int> *node, QStandardItem *parentItem)
{
    if (!node)
        return;

    QStandardItem *item = new QStandardItem(QString::number(node->data));

    if (!parentItem)
        model->appendRow(item);
    else
        parentItem->appendRow(item);

    setupModelData(model, node->left, item);
    setupModelData(model, node->right, item);
}


void MainWindow::on_addButton_clicked()
{
    QString valueStr = ui->lineEdit->text();
    int value = valueStr.toInt();
    tree->add(value);
}

void MainWindow::on_removeButton_clicked()
{
    QString valueStr = ui->lineEdit->text();
    int value = valueStr.toInt();
    tree->remove(value);
}

void MainWindow::on_findButton_clicked()
{
    QString valueStr = ui->lineEdit->text();
    int value = valueStr.toInt();
    bool found = tree->find(value);
    if(found)
        ui->textEdit->append("Узел найден.");
    else
        ui->textEdit->append("Узел не найден.");
}

void MainWindow::on_traverseButton_clicked()
{
    QString traversal = tree->traverse();
    ui->textEdit->append(traversal);
}

void MainWindow::on_findLowestCommonAncestorButton_clicked()
{
    QString value1Str = ui->lineEdit->text();
    int value1 = value1Str.toInt();
    QString value2Str = ui->lineEdit_2->text();
    int value2 = value2Str.toInt();
    int ancestor = tree->findLowestCommonAncestor(value1, value2);
    ui->textEdit->append("Наименьший общий предок двух узлов: " + QString::number(ancestor));
}

void MainWindow::on_printOriginalTreeButton_clicked()
{
    QString traversal = tree->traverse();
    ui->textEdit->append("Дерево: " + traversal);
}


