#include "vectorfunctioninformation.h"
#include "ui_vectorfunctioninformation.h"

VectorFunctionInformation::VectorFunctionInformation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VectorFunctionInformation)
{
    ui->setupUi(this);
}

VectorFunctionInformation::~VectorFunctionInformation()
{
    delete ui;
}

void VectorFunctionInformation::on_closeButton_clicked()
{
    close();
}

