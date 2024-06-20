#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "figure.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_3->hide();
    ui->label_9->hide();
    ui->pushButton_16->hide();
    ui->textEdit_4->hide();
    ui->label_10->hide();
    ui->pushButton_17->hide();
    ui->textEdit_5->hide();
    ui->textEdit_6->hide();
    ui->label_11->hide();
    ui->pushButton_18->hide();
    ui->textEdit_7->hide();
    ui->textEdit_8->hide();
    ui->label_12->hide();
    ui->pushButton_19->hide();
    ui->textEdit_9->hide();
    ui->label_13->hide();
    ui->pushButton_20->hide();
    ui->textEdit_11->hide();
    ui->textEdit_12->hide();
    ui->label_15->hide();
    ui->pushButton_22->hide();
    ui->textEdit_13->hide();
    ui->textEdit_14->hide();
    ui->label_16->hide();
    ui->pushButton_23->hide();
    ui->textEdit_15->hide();
    ui->textEdit_16->hide();
    ui->label_17->hide();
    ui->pushButton_24->hide();
    ui->textEdit_17->hide();
    ui->label_18->hide();
    ui->pushButton_25->hide();
    ui->textEdit_10->hide();
    ui->label_14->hide();
    ui->pushButton_21->hide();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updatePosLabel(const QPointF &center){
    ui->textBrowser_3->setText(QString::number(center.x()));
    ui->textBrowser_4->setText(QString::number(center.y()));
}

void MainWindow::updateSquareLabel(qreal square){
    ui->textBrowser_2->setText(QString::number(square));
}

void MainWindow::updatePerimeterLabel(qreal perimeter){
    ui->textBrowser->setText(QString::number(perimeter));
}

void MainWindow::changes(){

   for(Base* base : mass){

    connect(base, &Base::squareChanged, this, &MainWindow::updateSquareLabel);
    connect(base, &Base::positionChanged, this, &MainWindow::updatePosLabel);
    connect(base, &Base::perimeterChanged, this, &MainWindow::updatePerimeterLabel);
    }

    updateSquareLabel(base->Area());
    updatePerimeterLabel(base->Perimeter());
    updatePosLabel(base->scenePos() + QPointF(base -> boundingRect().width() / 2, base -> boundingRect().height() / 2));
}

void MainWindow::on_pushButton_7_clicked() {

    ui->textEdit_7->show();
    ui->textEdit_8->show();
    ui->label_12->show();
    ui->pushButton_19->show();
    base = new Rect();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_4_clicked() {

    ui->textEdit_4->show();
    ui->label_10->show();
    ui->pushButton_17->show();
    base = new Square();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_clicked() {
    ui->textEdit_3->show();
    ui->label_9->show();
    ui->pushButton_16->show();
    base = new Circle();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_3_clicked() {
    ui->textEdit_5->show();
    ui->textEdit_6->show();
    ui->label_11->show();
    ui->pushButton_18->show();
    base = new Rhombus();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit_17->show();
    ui->label_18->show();
    ui->pushButton_25->show();
    base = new Triangle();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_5_clicked() {

    ui->textEdit_15->show();
    ui->textEdit_16->show();
    ui->label_17->show();
    ui->pushButton_24->show();
    base = new Star5();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_6_clicked() {

    ui->textEdit_11->show();
    ui->textEdit_12->show();
    ui->label_15->show();
    ui->pushButton_22->show();
    base = new Star6();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_9_clicked() {

    ui->textEdit_13->show();
    ui->textEdit_14->show();
    ui->label_16->show();
    ui->pushButton_23->show();
    base = new Star8();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_8_clicked() {

    ui->textEdit_9->show();
    ui->label_13->show();
    ui->pushButton_20->show();
    base = new Hexagon();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_pushButton_10_clicked() {

    ui->textEdit_10->show();
    ui->label_14->show();
    ui->pushButton_21->show();
    base = new Trapezoid();
    base->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(base);
    mass.append(base);
    changes();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {

    // Вращение фигуры вокруг центра масс
    double rotation_angle = ui->horizontalSlider->value() * 3.6; // Примерный масштаб

    // Находим центр масс фигуры
    QPointF center = base->boundingRect().center();

    // Устанавливаем точку поворота в центр масс
    base->setTransformOriginPoint(center);
    base->setRotation(rotation_angle);
}

void MainWindow::on_pushButton_11_clicked() {

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


void MainWindow::on_pushButton_12_clicked() {

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


void MainWindow::on_pushButton_13_clicked() {

    double newX = ui->textEdit->toPlainText().toDouble();
    double newY = ui->textEdit_2->toPlainText().toDouble();
    base->moveFigureTo(newX, newY);
}


void MainWindow::on_pushButton_14_clicked() {

    base->newArea(-5);
    ui->textBrowser_2->setText(QString::number(base->Area()));
    ui->textBrowser->setText(QString::number(base->Perimeter()));
    scene->update();
}


void MainWindow::on_pushButton_15_clicked()
{
    base->newArea(5);
    ui->textBrowser_2->setText(QString::number(base->Area()));
    ui->textBrowser->setText(QString::number(base->Perimeter()));
    scene->update();
}


void MainWindow::on_pushButton_16_clicked() {

    double sidesircle = ui->textEdit_3->toPlainText().toDouble();
    base->newparametrs(sidesircle, 1, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_17_clicked() {

    double sidesquare = ui->textEdit_4->toPlainText().toDouble();
    base->newparametrs(sidesquare, 1, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_18_clicked() {

    double side1 = ui->textEdit_5->toPlainText().toDouble();
    double side2 = ui->textEdit_6->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_19_clicked() {

    double side1 = ui->textEdit_7->toPlainText().toDouble();
    double side2 = ui->textEdit_8->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_20_clicked() {

    double side1 = ui->textEdit_9->toPlainText().toDouble();
    base->newparametrs(side1, 1, 1);
    changes();
    scene->update();
}

void MainWindow::on_pushButton_22_clicked() {

    double side1 = ui->textEdit_11->toPlainText().toDouble();
    double side2 = ui->textEdit_12->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_23_clicked() {

    double side1 = ui->textEdit_13->toPlainText().toDouble();
    double side2 = ui->textEdit_14->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_24_clicked() {

    double side1 = ui->textEdit_15->toPlainText().toDouble();
    double side2 = ui->textEdit_16->toPlainText().toDouble();
    base->newparametrs(side1, side2, 1);
    changes();
    scene->update();
}


void MainWindow::on_pushButton_25_clicked() {

    double side1 = ui->textEdit_17->toPlainText().toDouble();
    base->newparametrs(side1, 1, 1);
    changes();
    scene->update();
}



void MainWindow::on_pushButton_21_clicked() {

    double side1 = ui->textEdit_10->toPlainText().toDouble();
    base->newparametrs(side1, 1, 1);
    changes();
    scene->update();
}

