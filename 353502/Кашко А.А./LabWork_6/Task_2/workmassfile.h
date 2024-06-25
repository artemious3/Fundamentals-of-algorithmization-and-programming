#ifndef WORKMASSFILE_H
#define WORKMASSFILE_H

#include <QDialog>
#include <QFile>

namespace Ui {
class WorkMassFile;
}

class WorkMassFile : public QDialog
{
    Q_OBJECT

public:
    explicit WorkMassFile(QWidget *parent = nullptr);
    ~WorkMassFile();

private slots:
    void on_sizeMassButton_clicked();

    void on_massButton_clicked();

    void on_showButton_clicked();

private:
    Ui::WorkMassFile *ui;

    int sizeMass;
};

#endif // WORKMASSFILE_H
