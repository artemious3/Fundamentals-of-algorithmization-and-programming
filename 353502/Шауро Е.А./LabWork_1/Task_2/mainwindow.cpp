#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    ui->Ch1Text->hide();
    ui->Ch2Text->hide();
    ui->Ch3Text->hide();
    ui->UpdateButton_2->hide();
    ui->Char1->hide();
    ui->Char2->hide();
    ui->Char3->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Update-functions

void MainWindow::updatePosLabel(const QPointF &center){
    ui->PositionLabelForShow->setText("(" + QString::number(center.x()) + ", " + QString::number(center.y()) + ")");
    ui->textEditX->setText(QString::number(center.x()));
    ui->textEditY->setText(QString::number(center.y()));
}

void MainWindow::updatePerimeterLabel(qreal perimeter){
    ui->PerimeterBrowser->setText(QString::number(perimeter));
}

void MainWindow::updateSquareLabel(qreal square){
    ui->SquareBrowser->setText(QString::number(square));
}

void MainWindow::updateTypeLabel(Standart * /*element*/){

    QString text = "";
    QString text1 = "";
    QString text2 = "";
    QString text3 = "";

    if(auto* element = dynamic_cast<Triangle*>(item)){
        hideButtons();
        text = "Triangle";
        text1 = "Enter the length of the side";
        ui->Ch1Text->show();
        ui->Char1->show();
    }
    if(auto* element = dynamic_cast<Circle*>(item)){
         hideButtons();
        text = "Circle";
        text1 = "Enter the radius";
        ui->Ch1Text->show();
         ui->Char1->show();
    }
    if(auto* element = dynamic_cast<Hexagon*>(item)){
         hideButtons();
        text = "Hexagon";
        text1 = "Enter the length of the side";
        ui->Ch1Text->show();
         ui->Char1->show();
    }
    if(auto* element = dynamic_cast<Rectangle*>(item)){
         hideButtons();
        text = "Rectangle";
        text1 = "Enter the width";
        text2 = "Enter the length";
        ui->Ch1Text->show();
        ui->Ch2Text->show();
         ui->Char1->show();
          ui->Char2->show();
    }
    if(auto* element = dynamic_cast<Rhombus*>(item)){
         hideButtons();
        text = "Rhombus";
        text1 = "Enter the 1st diagonal";
        text2 = "Enter the 2nd diagonal";
        ui->Ch1Text->show();
        ui->Ch2Text->show();
        ui->Char1->show();
         ui->Char2->show();
    }
    if(auto* element = dynamic_cast<Square*>(item)){
         hideButtons();
        text = "Square";
        text1 = "Enter the length of the side";
        ui->Ch1Text->show();
        ui->Char1->show();

    }
    if(auto* element = dynamic_cast<Star5*>(item)){
         hideButtons();
        text = "Star5";
        text1 = "Enter the inner radius";
        text2 = "Enter the outer radius";
        ui->Ch1Text->show();
        ui->Ch2Text->show();
        ui->Char1->show();
         ui->Char2->show();
    }
    if(auto* element = dynamic_cast<Star6*>(item)){
         hideButtons();
        text = "Star6";
        text1 = "Enter the inner radius";
        text2 = "Enter the outer radius";
        ui->Ch1Text->show();
        ui->Ch2Text->show();
        ui->Char1->show();
         ui->Char2->show();
    }
    if(auto* element = dynamic_cast<Star8*>(item)){
         hideButtons();
        text = "Star8";
        text1 = "Enter the inner radius";
        text2 = "Enter the outer radius";
        ui->Ch1Text->show();
        ui->Ch2Text->show();
        ui->Char1->show();
         ui->Char2->show();
    }
    if(auto* element = dynamic_cast<Cross*>(item)){
         hideButtons();
        text = "Cross";
        text1 = "Enter the length";
        text2 = "Enter the height";
        text3 = "Enter the width";
        ui->Ch1Text->show();
        ui->Ch2Text->show();
        ui->Ch3Text->show();
        ui->Char1->show();
        ui->Char2->show();
        ui->Char3->show();

    }

    ui->TypeLabel->setText(text);
    ui->Char1->setText(text1);
    ui->Char2->setText(text2);
    ui->Char3->setText(text3);
    ui->UpdateButton_2->show();
}

void MainWindow::changes(){

     for(Standart* item : items){
       connect(item, &Standart::positionChanged, this, &MainWindow::updatePosLabel);
       connect(item, &Standart::perimeterChanged, this, &MainWindow::updatePerimeterLabel);
       connect(item, &Standart::squareChanged, this, &MainWindow::updateSquareLabel);
     }

     updatePosLabel(item->scenePos() + QPointF(item -> boundingRect().width() / 2, item -> boundingRect().height() / 2));
     updatePerimeterLabel(item->countPerimeter());
     updateSquareLabel(item->countSquare());
     updateTypeLabel(item);

}

//Push Buttons
void MainWindow::on_TriangleButton_clicked()
{
    hideButtons();


    item = new Triangle();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();
}

void MainWindow::on_CircleButton_clicked()
{
    hideButtons();
    ui->UpdateButton_2->show();

    item = new Circle();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();
}

void MainWindow::on_RhombusButton_clicked()
{
    hideButtons();
    ui->UpdateButton_2->show();
    item = new Rhombus();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();
}

void MainWindow::on_SquareButton_clicked()
{
    hideButtons();
    ui->UpdateButton_2->show();

    item = new Square();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();
}

void MainWindow::on_RectButton_clicked()
{
    hideButtons();
    ui->UpdateButton_2->show();

    item = new Rectangle();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();
}

void MainWindow::on_Star5Button_clicked()
{
    hideButtons();
       ui->UpdateButton_2->show();

    item = new Star5();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();

}

void MainWindow::on_Star6Button_clicked()
{
    hideButtons();
    ui->UpdateButton_2->show();

    item = new Star6();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();

}

void MainWindow::on_Star8Button_clicked()
{
    hideButtons();
    ui->UpdateButton_2->show();

    item = new Star8();
    item->setPos(rand()%250+1, rand()%250+1);
    scene->addItem(item);
    items.append(item);
    changes();

}

void MainWindow::on_HexButton_clicked()
{
    hideButtons();
       ui->UpdateButton_2->show();

    item = new Hexagon();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();

}

void MainWindow::on_CrossButton_clicked(){

    hideButtons();
       ui->UpdateButton_2->show();

    item = new Cross();
    item->setPos(rand() % 250 + 1, rand() % 250 + 1 );
    scene->addItem(item);
    items.append(item);
    changes();
}

void MainWindow::on_UpdateButton_clicked()
{
    double newX = ui->textEditX->toPlainText().toDouble();
    double newY = ui->textEditY->toPlainText().toDouble();
    item->moveFigureTo(newX, newY);
}

void MainWindow::on_UpdateButton_2_clicked()
{
    qreal param1 = ui->Ch1Text->toPlainText().toDouble();
    qreal param2 = ui->Ch2Text->toPlainText().toDouble();
    qreal param3 = ui->Ch3Text->toPlainText().toDouble();

    if(param1 != 0 && param2 >= 0 && param3 >= 0)
    rePaint(item, param1, param2, param3);

    changes();

}

void MainWindow::on_BackButton_clicked()
{
    int i =0;
    for(Standart* item2 : items){
        if (item2 == item)
            break;
        
            ++i;
    }
    if(i!=0)
    item = items[i - 1];
    changes();
}

void MainWindow::on_NextButton_clicked()
{
    int i =0;
    for(Standart* item2 : items){
        if (item2 == item)
            break;
        
            ++i;
    }

    if(items.last() != item)
    item = items[i + 1];

    changes();
}

void MainWindow::on_PlussButton_clicked()
{
    plusMinus(item, 5);
    scene->update();

}

void MainWindow::on_MinusButton_clicked()
{
    plusMinus(item, -5);
    scene->update();
}

void MainWindow::on_PosSlider_valueChanged(int  /*value*/)
{
        ui->ValueLabel2->setText(QString::number(ui->PosSlider->value()));

        // Вращение фигуры вокруг центра масс
        double rotation_angle = ui->PosSlider->value() * 3.6;


        QPointF center = item->boundingRect().center();
        item->setTransformOriginPoint(center);
        item->setRotation(rotation_angle);
}







// Other functions

void MainWindow::plusMinus(Standart *item, qreal con){
     item->newSquare(con);
     updateSquareLabel(item->countSquare());
     updatePerimeterLabel(item->countPerimeter());
}


void MainWindow::hideButtons(){
    ui->Ch1Text->hide();
    ui->Ch2Text->hide();
    ui->Ch3Text->hide();
    ui->UpdateButton_2->hide();
    ui->Char1->hide();
    ui->Char2->hide();
    ui->Char3->hide();
}

void MainWindow::rePaint(Standart *item, qreal param1, qreal param2, qreal param3){
    item->setParameters(param1, param2, param3);
    scene->update();
}

void MainWindow::on_pushButton_clicked()
{
    for(auto & item : items){
        delete[] item;
    }

    close();
}
