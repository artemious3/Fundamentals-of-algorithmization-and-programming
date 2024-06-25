#ifndef COUPLEMAKER_H
#define COUPLEMAKER_H

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <array>

#include "const.h"

class CoupleMaker {
 private:
  QString FIO;
  QString sex;
  int age;
  int weight;
  int high;

  std::array<int, 2> partnerAge;
  std::array<int, 2> partnerWeight;
  std::array<int, 2> partnerHigh;

  int test = 0;

 public:
  CoupleMaker();
  ~CoupleMaker();

  CoupleMaker setData(CoupleMaker couple, const QString& str);

  QString getFIO(const CoupleMaker& couple);
  QString getAge(const CoupleMaker& couple);
  QString getSex(const CoupleMaker& couple);
  QString getHigh(const CoupleMaker& couple);
  QString getWeight(const CoupleMaker& couple);
  QString getPartAge(const CoupleMaker& couple);
  QString getPartHigh(const CoupleMaker& couple);
  QString getPartWeight(const CoupleMaker& couple);
  int getPartMinAge(const CoupleMaker& couple);
  int getPartMaxAge(const CoupleMaker& couple);
  int getPartMinHigh(const CoupleMaker& couple);
  int getPartMaxHigh(const CoupleMaker& couple);
  int getPartMinWeight(const CoupleMaker& couple);
  int getPartMaxWeight(const CoupleMaker& couple);

  QString FileOpener(CoupleMaker* couple, const QString& content);

  QString ConvertCoupleIntoText(const CoupleMaker& couple, bool isNotFirst);

  void SortByAge(QList<CoupleMaker>* couples);

  void Make2Lists(const QList<CoupleMaker>& couples, QList<CoupleMaker>* women,
                  QList<CoupleMaker>* men);

  QList<CoupleMaker>* MakeList(const QList<CoupleMaker>& couples,
                              const CoupleMaker& participant,
                              const QString& participantSex);
};

#endif  // COUPLEMAKER_H
