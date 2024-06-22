#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "figure.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateSquare(qreal square){
    ui->textBrowser->setText(QString::number(square));
}

void MainWindow::updatePerimeter(qreal perimeter){
    ui->textBrowser_2->setText(QString::number(perimeter));
}

void MainWindow::updatePos(const QPointF &center){
    ui->textBrowser_4->setText(QString::number(center.x()));
    ui->textBrowser_3->setText(QString::number(center.y()));
}

void MainWindow::changes(){

    for(Base* base : mass){
        connect(base, &Base::positionChanged, this, &MainWindow::updatePos);
        connect(base, &Base::squareChanged, this, &MainWindow::updateSquare);
        connect(base, &Base::perimeterChanged, this, &MainWindow::updatePerimeter);
    }

    updateSquare(base->Area());
    updatePerimeter(base->Perimeter());
    updatePos(base->scenePos() + QPointF(base -> boundingRect().width() / 2, base -> boundingRect().height() / 2));
}

void MainWindow::on_pushButton_1_clicked() {

    base = new Circle();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_2_clicked() {

    base = new Square();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_3_clicked() {

    base = new Rect();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_4_clicked() {

    base = new Triangle();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_5_clicked() {

    base = new Rhombus();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_6_clicked() {

    base = new Hexagon();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_7_clicked() {

    base = new Trapezoid();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_8_clicked() {

    base = new Star5();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_9_clicked() {

    base = new Star6();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_10_clicked() {

    base = new Star8();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {

    double rotation_angle = ui->horizontalSlider->value() * 3.6;
    QPointF center = base->boundingRect().center();

    base->setTransformOriginPoint(center);
    base->setRotation(rotation_angle);
}

void MainWindow::on_pushButton_22_clicked() {

    int i =0;
    for(Base* basedop : mass){
        if (basedop == base)
            break;
        else
            ++i;
    }
    if(i!=0)
        base = mass[i - 1];
    changes();
}


void MainWindow::on_pushButton_23_clicked() {

    int i =0;
    for(Base* basedop : mass){
        if (basedop == base)
            break;
        else
            ++i;
    }

    if(mass.last() != base)
        base = mass[i + 1];

    changes();
}

void MainWindow::on_pushButton_99_clicked() {

    double xn = ui->textEdit->toPlainText().toDouble();
    double yn = ui->textEdit_16->toPlainText().toDouble();
    base->moveFigureTo(xn, yn);
    changes();
    scene->update();
}
void MainWindow::on_pushButton_11_clicked() {

    base->newArea(-5);
    ui->textBrowser->setText(QString::number(base->Area()));
    ui->textBrowser_2->setText(QString::number(base->Perimeter()));
    scene->update();
}

void MainWindow::on_pushButton_21_clicked()
{
    base->newArea(5);
    ui->textBrowser->setText(QString::number(base->Area()));
    ui->textBrowser_2->setText(QString::number(base->Perimeter()));
    scene->update();
}

void MainWindow::on_pushButton_12_clicked() {

    double sidesircle = ui->textEdit_1->toPlainText().toDouble();
    base->newparametrs(sidesircle, 1, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_24_clicked() {

    double sidesquare = ui->textEdit_2->toPlainText().toDouble();
    base->newparametrs(sidesquare, 1, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_13_clicked() {

    double side1 = ui->textEdit_3->toPlainText().toDouble();
    double side2 = ui->textEdit_4->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_14_clicked() {

    double side1 = ui->textEdit_5->toPlainText().toDouble();
    base->newparametrs(side1, 1, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_15_clicked() {

    double side1 = ui->textEdit_6->toPlainText().toDouble();
    double side2 = ui->textEdit_7->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_16_clicked() {

    double side1 = ui->textEdit_8->toPlainText().toDouble();
    base->newparametrs(side1, 1, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_17_clicked() {

    double side1 = ui->textEdit_9->toPlainText().toDouble();
    base->newparametrs(side1, 1, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_18_clicked() {

    double side1 = ui->textEdit_10->toPlainText().toDouble();
    double side2 = ui->textEdit_11->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_19_clicked() {

    double side1 = ui->textEdit_12->toPlainText().toDouble();
    double side2 = ui->textEdit_13->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_20_clicked() {

    double side1 = ui->textEdit_14->toPlainText().toDouble();
    double side2 = ui->textEdit_15->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}

