#include "sick.h"

QString Sick::getNumber(const Sick& sick) {
    return QString::number(sick.number);
}

QString Sick::getFIO(const Sick& sick) {
    return sick.FIO;
}

QString Sick::getSex(const Sick& sick) {
    return sick.sex;
}

QString Sick::getAge(const Sick& sick) {
    return QString::number(sick.age);
}

QString Sick::getDiagnoz(const Sick& sick, int counter) {
    for (int i = 0; i < counter; ++i) {
        return sick.diagnoz[i];
    }
}

QString Sick::getAdmissionDate(const Sick& sick) {
    QString dateString = sick.admissionDate.toString("yyyy-MM-dd");
    return dateString;
}

QString Sick::getExtractDate(const Sick& sick) {
    QString dateString = sick.extractDate.toString("yyyy-MM-dd");
    return dateString;
}

QString Sick::FileOpener(Sick* sick, const QString& content, int counter) {
    QStringList list = content.split('\n');
    QString errorLine = "";
    bool ok1 = false, ok2 = false;

    for (int i = 0, field = 0; i < list.size() - 1;
         ++i, field = i % 7) {

        if (field == 1) {
            sick->number = list[i].toInt(&ok1);
            if (!ok1) {
                errorLine += "\nОшибка в номере палаты у больного.";
                i += 5;
            }
        }
        if (field == 2) {
            sick->FIO = list[i];
        }
        if (field == 3) {
            sick->sex = list[i];
        }
        if (field == 4) {
            sick->age = list[i].toInt(&ok1);
            if (!ok1) {
                errorLine += "\nОшибка в возрасте у больного.";
                i += 5;
            }
        }
        if (field == 5) {
            for (int i = 0; i < counter; ++i) {
            sick->diagnoz[i] = list[i];
            }
        }
        if (field == 6) {
            QString dateString = sick->admissionDate.toString("yyyy-MM-dd");
            dateString = list[i];
        }
        if (field == 7) {
            QString dateString = sick->extractDate.toString("yyyy-MM-dd");
            dateString = list[i];
        }
    }
    return errorLine;
}


void SortByDate(QList<Sick>* sicks) {

};

void SortByDiagnoz(QList<Sick>* sicks) {

};
