#include "mainwindow.h"

#include <QPainter>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "balloon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setSceneRect(0, 0, 500, 500);

    QPolygon triangle;
    triangle << QPoint(255, 0) << QPoint(265, 0) << QPoint(260, 10);

    scene.addPolygon(triangle, QPen(Qt::black), QBrush(Qt::blue));

    QPushButton button("Start");
    QObject::connect(&button, &QPushButton::clicked, [&scene](){
        Balloon *balloon = new Balloon;
        scene.addItem(balloon);
    });

    scene.addWidget(&button);
    view.show();

    return a.exec();
}
