#ifndef WORKSTRUCTFILE_H
#define WORKSTRUCTFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class WorkStructFile;
}

class WorkStructFile : public QDialog
{
    Q_OBJECT

public:
    explicit WorkStructFile(QWidget *parent = nullptr);
    ~WorkStructFile();

    struct City
    {
        int population;                                // население
        double area;                                   // площадь города
        QChar first_letter_country;                    // страна, в которой расположен город
        bool capital;                                  // логическаяя переменная для проверки, является ли город столицей
        char streets[5][25];                           // названия улиц
        int number_of_houses[5];                       // кол-во домов на различных улицах
    };
    City Minsk;

private slots:
    void on_inputFileButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::WorkStructFile *ui;
};

#endif // WORKSTRUCTFILE_H
