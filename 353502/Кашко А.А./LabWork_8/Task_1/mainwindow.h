#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include "binarytree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_findButton_clicked();
    void on_traverseButton_clicked();
    void on_findLowestCommonAncestorButton_clicked();
    void on_printOriginalTreeButton_clicked();

private:
    Ui::MainWindow *ui;
    BinaryTree<int> *tree;

    void setupModelData(QStandardItemModel *model, Node<int> *node, QStandardItem *parentItem);
};

#endif // MAINWINDOW_H
