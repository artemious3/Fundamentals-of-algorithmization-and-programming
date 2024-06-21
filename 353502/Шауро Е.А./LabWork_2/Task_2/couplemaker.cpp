#include "couplemaker.h"

CoupleMaker::CoupleMaker() = default;

CoupleMaker::~CoupleMaker() = default;

QString CoupleMaker::getFIO(const CoupleMaker& couple)

{
  return couple.FIO;
}

QString CoupleMaker::getAge(const CoupleMaker& couple) {
  return QString::number(couple.age);
}

QString CoupleMaker::getSex(const CoupleMaker& couple) {
  return couple.sex;
}

QString CoupleMaker::getHigh(const CoupleMaker& couple) {
  return QString::number(couple.high);
}

QString CoupleMaker::getWeight(const CoupleMaker& couple) {
  return QString::number(couple.weight);
}

QString CoupleMaker::getPartAge(const CoupleMaker& couple) {
  return QString::number(couple.partnerAge[0]) + '-' +
         QString::number(couple.partnerAge[1]);
}

QString CoupleMaker::getPartHigh(const CoupleMaker& couple) {
  return QString::number(couple.partnerHigh[0]) + '-' +
         QString::number(couple.partnerHigh[1]);
}

QString CoupleMaker::getPartWeight(const CoupleMaker& couple) {
  return QString::number(couple.partnerWeight[0]) + '-' +
         QString::number(couple.partnerWeight[1]);
}

int CoupleMaker::getPartMinAge(const CoupleMaker& couple) {
  return couple.partnerAge[0];
}

int CoupleMaker::getPartMaxAge(const CoupleMaker& couple) {
  return couple.partnerAge[1];
}

int CoupleMaker::getPartMinHigh(const CoupleMaker& couple) {
  return couple.partnerHigh[0];
}

int CoupleMaker::getPartMaxHigh(const CoupleMaker& couple) {
  return couple.partnerHigh[1];
}

int CoupleMaker::getPartMinWeight(const CoupleMaker& couple) {
  return couple.partnerWeight[0];
}

int CoupleMaker::getPartMaxWeight(const CoupleMaker& couple) {
  return couple.partnerWeight[1];
}

CoupleMaker CoupleMaker::setData(CoupleMaker couple, const QString& str) {
  int maxVal, minVal;

  QStringList list = str.split('/'), innerList;
  couple.FIO = list[FIO_FIELD];
  couple.sex = list[SEX_FIELD];
  couple.age = list[AGE_FIELD].toInt();
  couple.high = list[HIGH_FIELD].toInt();
  couple.weight = list[WEIGHT_FIELD].toInt();

  innerList = list[PART_AGE_FIELD].split('-');
  maxVal = innerList[0].toInt() >= innerList[1].toInt() ? innerList[0].toInt()
                                                        : innerList[1].toInt();
  minVal = innerList[0].toInt() < innerList[1].toInt() ? innerList[0].toInt()
                                                       : innerList[1].toInt();
  couple.partnerAge[0] = minVal;
  couple.partnerAge[1] = maxVal;

  innerList = list[PART_HIGH_FIELD].split('-');
  maxVal = innerList[0].toInt() >= innerList[1].toInt() ? innerList[0].toInt()
                                                        : innerList[1].toInt();
  minVal = innerList[0].toInt() < innerList[1].toInt() ? innerList[0].toInt()
                                                       : innerList[1].toInt();
  couple.partnerHigh[0] = minVal;
  couple.partnerHigh[1] = maxVal;

  innerList = list[PART_WEIGHT_FIELD].split('-');
  maxVal = innerList[0].toInt() >= innerList[1].toInt() ? innerList[0].toInt()
                                                        : innerList[1].toInt();
  minVal = innerList[0].toInt() < innerList[1].toInt() ? innerList[0].toInt()
                                                       : innerList[1].toInt();
  couple.partnerWeight[0] = minVal;
  couple.partnerWeight[1] = maxVal;

  return couple;
}

QString CoupleMaker::FileOpener(CoupleMaker* couple, const QString& content) {
  QStringList list = content.split('\n');
  QString errorLine = "";
  bool ok1 = false, ok2 = false;

  for (int i = 0, field = 0; i < list.size() - 1;
       ++i, field = i % TOTAL_FIELD_COUNT) {
    if (field == FIO_FIELD) {
      couple->FIO = list[i];
    }
    if (field == SEX_FIELD) {
      couple->sex = list[i];
    }
    if (field == AGE_FIELD) {
      couple->age = list[i].toInt(&ok1);
      if (!ok1) {
        errorLine += "\nОшибка в возрасте у участника №: ";
        i += FIVE;
      }
    }
    if (field == HIGH_FIELD) {
      couple->high = list[i].toInt(&ok1);
      if (!ok1) {
        errorLine += "\nОшибка в росте у участника №: ";
        i += 4;
      }
    }
    if (field == WEIGHT_FIELD) {
      couple->weight = list[i].toInt(&ok1);
      if (!ok1) {
        errorLine += "\nОшибка в весе у участника №: ";
        i += 3;
      }
    }
    if (field == PART_AGE_FIELD) {
      QStringList line = list[i].split('-');
      couple->partnerAge[0] = line[0].toInt(&ok1);
      couple->partnerAge[1] = line[1].toInt(&ok2);

      if (!ok1 || !ok2) {
        errorLine += "\nОшибка в возрасте партнёра у участника №: ";
        i += 2;
      }
    }
    if (field == PART_HIGH_FIELD) {
      QStringList line = list[i].split('-');
      //    partnerHigh = new int[2];
      couple->partnerHigh[0] = line[0].toInt(&ok1);
      couple->partnerHigh[1] = line[1].toInt(&ok2);
      if (!ok1 || !ok2) {
        errorLine += "\nОшибка в росте партнёра у участника №: ";
        i += 1;
      }
    }
    if (field == PART_WEIGHT_FIELD) {
      QStringList line = list[i].split('-');
      couple->partnerWeight[0] = line[0].toInt(&ok1);
      couple->partnerWeight[1] = line[1].toInt(&ok2);
      if (!ok1 || !ok2) {
        errorLine += "\nОшибка в весе партнёра у участника №: ";
      }
    }
  }
  return errorLine;
}

QString CoupleMaker::ConvertCoupleIntoText(const CoupleMaker& couple,
                                           bool isNotFirst) {
  QString text = "";
  if (isNotFirst) {
    text += '/';
  }
  text += couple.FIO + '\n' + couple.sex + '\n' + QString::number(couple.age) +
          '\n' + QString::number(couple.high) + '\n' +
          QString::number(couple.weight) + '\n' +
          QString::number(couple.partnerAge[0]) + '-' +
          QString::number(couple.partnerAge[1]) + '\n' +
          QString::number(couple.partnerHigh[0]) + '-' +
          QString::number(couple.partnerHigh[1]) + '\n' +
          QString::number(couple.partnerWeight[0]) + '-' +
          QString::number(couple.partnerWeight[1]);

  return text;
}

void swap(CoupleMaker& couple1, CoupleMaker& couple2) {
  CoupleMaker helperCouple;
  helperCouple = couple1;
  couple1 = couple2;
  couple2 = helperCouple;
}

// Функция для разделения массива и возврата индекса опорного элемента
int partition(QList<CoupleMaker>* couples, int low, int high) {
  int pivot = (*couples)[high].getAge((*couples)[high]).toInt();
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if ((*couples)[j].getAge((*couples)[j]).toInt() <= pivot) {
      i++;
      swap((*couples)[i], (*couples)[j]);
    }
  }
  swap((*couples)[i + 1], (*couples)[high]);
  return (i + 1);
}


// Основная функция, которая реализует QuickSort
void quickSort(QList<CoupleMaker>* couples, int low, int high) {
  if (low < high) {
    int pi = partition(couples, low, high);
    quickSort(couples, low, pi - 1);
    quickSort(couples, pi + 1, high);
  }
}

// Функция для вызова быстрой сортировки
void CoupleMaker::SortByAge(QList<CoupleMaker>* couples) {
  int n = couples->size();
  quickSort(couples, 0, n - 1);
}

void CoupleMaker::Make2Lists(const QList<CoupleMaker>& couples,
                             QList<CoupleMaker>* women,
                             QList<CoupleMaker>* men) {
  for (const CoupleMaker& person : couples) {
    if (person.sex == "Мужской") {
      men->append(person);
    } else {
      women->append(person);
    }
  }
}

QList<CoupleMaker>* CoupleMaker::MakeList(const QList<CoupleMaker>& couples,
                                         const CoupleMaker& participant,
                                         const QString& participantSex) {
  QList<CoupleMaker>* partners = new QList<CoupleMaker>();
  for (const CoupleMaker& person : couples) {
    if (person.sex != participantSex) {
      if (person.age >= participant.partnerAge[0] &&
          person.age <= participant.partnerAge[1] &&
          participant.age >= person.partnerAge[0] &&
          participant.age <= person.partnerAge[1]) {
        if (person.high >= participant.partnerHigh[0] &&
            person.high <= participant.partnerHigh[1] &&
            participant.high >= person.partnerHigh[0] &&
            participant.high <= person.partnerHigh[1]) {
          if (person.weight >= participant.partnerWeight[0] &&
              person.weight <= participant.partnerWeight[1] &&
              participant.weight >= person.partnerWeight[0] &&
              participant.weight <= person.partnerWeight[1]) {
            partners->append(person);
          }
        }
      }
    }
  }
  return partners;
}
