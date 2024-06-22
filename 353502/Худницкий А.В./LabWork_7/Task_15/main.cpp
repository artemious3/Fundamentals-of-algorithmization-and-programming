#include "mainwindow.h"
#include "Node.h"
#include "Deque.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    Deque myDeque;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
