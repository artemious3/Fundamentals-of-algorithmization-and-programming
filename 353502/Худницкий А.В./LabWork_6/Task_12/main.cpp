#include "shop.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
