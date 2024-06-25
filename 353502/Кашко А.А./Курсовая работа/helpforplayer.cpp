#include "helpforplayer.h"
#include "ui_helpforplayer.h"

HelpForPlayer::HelpForPlayer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpForPlayer)
{
    ui->setupUi(this);
}

HelpForPlayer::~HelpForPlayer()
{
    delete ui;
}

void HelpForPlayer::on_pushButton_clicked()
{
    close();
}

