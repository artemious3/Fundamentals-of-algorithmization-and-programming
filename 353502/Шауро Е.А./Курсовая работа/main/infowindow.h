#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QMainWindow>
#include <QString>
#include "mainConst.h"
#include "pet.h"
#include "mainscene.h"

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::InfoWindow *ui;
    MainScene* infoScene;
    Pet* cat;
    int num;
    QList<QString> description;
    QList<CatMood> mood;
};

#endif // INFOWINDOW_H
