#include "balloon.h"

Balloon::Balloon(QWidget *pointer): BaseEllipse(pointer)
{
    *f = {108, 95};
    *flyDown = false;
}

void Balloon::paintEvent(QPaintEvent *p){

    QPainter paint(this);
    QPen pen;
    QPolygon pol, pol1;

    pen.setColor(Qt::red);
    pol1 << QPoint(120, 10) << QPoint(140, 10) << QPoint(135, 13) << QPoint(138, 16) << QPoint(138, 50) << QPoint(122, 50) << QPoint(122, 16) << QPoint(125, 13);

    paint.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    paint.drawPolygon(pol1);

    pen.setColor(Qt::lightGray);
    paint.drawLine(130, 50, 130, 70);


    if (int(f->ry()) == 65 || *flyDown){

        f ->rx() = 113;

        paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        paint. drawEllipse(int(f->rx()) + 5, int(f->ry()), 20, 30);

        pol << QPoint(f ->rx()+15, f -> ry()) << QPoint(f ->rx()+20, f -> ry() - 5) << QPoint(f ->rx()+10, f -> ry() - 5);
        paint.drawPolygon(pol);

        pen.setColor(Qt::black);

        paint.setPen(pen);
        paint.drawLine(int(f->rx()) + 15, int(f->ry()), int(f->rx()) + 15, int(f->ry())-30);


        if(*flyDown && f->ry() > QWidget::height()){
            *flyDown = false;
            BaseEllipse::up(f, 0.35);
            update();
        }
        if(*flyDown && f->ry() < QWidget::height()){

            BaseEllipse::down(f, 0.1);
            update();
        }
    }

    else if (!*flyDown){

         f ->rx() = 108;

        paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        paint. drawEllipse(int(f->rx()), int(f->ry()), 40, 60);

        pol << QPoint(int(f->rx()) +20, int(f->ry()) + 60) << QPoint(int(f->rx()) +25, int(f->ry()) + 65) << QPoint(int(f->rx()) +15, int(f->ry()) + 65);

        paint.drawPolygon(pol);

        pen.setColor(Qt::black);

        paint.setPen(pen);
        paint.drawLine(int(f->rx()) + 20, int(f->ry()) + 60, int(f->rx()) + 20, int(f->ry()) + 90);

        BaseEllipse::up(f, 0.035);
        if (int(f->ry()) == 65) {
            *flyDown = true;

        }
        update();
    }

}



