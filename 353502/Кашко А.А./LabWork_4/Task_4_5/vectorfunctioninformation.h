#ifndef VECTORFUNCTIONINFORMATION_H
#define VECTORFUNCTIONINFORMATION_H

#include <QDialog>

namespace Ui {
class VectorFunctionInformation;
}

class VectorFunctionInformation : public QDialog
{
    Q_OBJECT

public:
    explicit VectorFunctionInformation(QWidget *parent = nullptr);
    ~VectorFunctionInformation();

private slots:
    void on_closeButton_clicked();

private:
    Ui::VectorFunctionInformation *ui;
};

#endif // VECTORFUNCTIONINFORMATION_H
