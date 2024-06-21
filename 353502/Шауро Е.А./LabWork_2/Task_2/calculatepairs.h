#ifndef CALCULATEPAIRS_H
#define CALCULATEPAIRS_H

#include <QWidget>
#include "couplemaker.h"

namespace Ui {
class CalculatePairs;
}

class CalculatePairs : public QWidget {
  Q_OBJECT

 public:
  explicit CalculatePairs(QWidget* parent = nullptr);
  ~CalculatePairs() override;

  void addToList(QList<CoupleMaker>* partners, CoupleMaker participant);
  void addToTotalList(const QList<CoupleMaker>& mainPerson,
                      const QList<QList<CoupleMaker>>& allPairs);
  void clearList();

 private:
  Ui::CalculatePairs* ui;
  CoupleMaker helperParticipant;
};

#endif  // CALCULATEPAIRS_H
