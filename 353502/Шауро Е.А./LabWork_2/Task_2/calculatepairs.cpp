#include "calculatepairs.h"
#include "ui_calculatepairs.h"

CalculatePairs::CalculatePairs(QWidget* parent)
    : QWidget(parent), ui(new Ui::CalculatePairs) {
  ui->setupUi(this);
}

CalculatePairs::~CalculatePairs() {
  delete ui;
}

void CalculatePairs::addToList(QList<CoupleMaker>* partners,
                               CoupleMaker participant) {
  for (CoupleMaker partner : *partners) {
    ui->listWidget->addItem(partner.getFIO(partner) + ", " +
                            partner.getAge(partner));
  }

  QString text = "Участник: " + participant.getFIO(participant);
  ui->label->setText(text);
}

void CalculatePairs::addToTotalList(const QList<CoupleMaker>& mainPerson,
                                    const QList<QList<CoupleMaker>>& allPairs) {
  int index = 0;
  for (const QList<CoupleMaker>& possiblePair : allPairs) {
    ui->listWidget->addItem(helperParticipant.getFIO(mainPerson[index]) + ", " +
                            helperParticipant.getAge(mainPerson[index]));
    ui->listWidget->addItem("----------------------------------------------");

    if (possiblePair.size() == 0) {
      ui->listWidget->addItem("Нет подходящей пары :(");
    }

    for (const CoupleMaker& person : possiblePair) {
      ui->listWidget->addItem(helperParticipant.getFIO(person) + ", " +
                              helperParticipant.getAge(person));
    }
    ui->listWidget->addItem("");
    ++index;
  }
}

void CalculatePairs::clearList() {
  ui->listWidget->clear();
}
