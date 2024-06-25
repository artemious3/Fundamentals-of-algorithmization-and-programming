#ifndef HELPFORPLAYER_H
#define HELPFORPLAYER_H

#include <QDialog>

#include "helppuzzle.h"
#include "averagepuzzles.h"
#include "hardpuzzles.h"

namespace Ui {
class HelpForPlayer;
}

class HelpForPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit HelpForPlayer(QWidget *parent = nullptr);
    ~HelpForPlayer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::HelpForPlayer *ui;
};

#endif // HELPFORPLAYER_H
