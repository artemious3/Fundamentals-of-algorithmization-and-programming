#ifndef SICK_H
#define SICK_H

#include <QDebug>
#include <QDate>
#include <QList>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <array>

class Sick {
private:
    int number;
    QString FIO;
    QString sex;
    int age;
    QList<QString> diagnoz;
    QDate admissionDate;
    QDate extractDate;

    int counter;
public:
    QString getNumber(const Sick& couple);
    QString getFIO(const Sick& couple);
    QString getSex(const Sick& couple);
    QString getAge(const Sick& couple);
    QString getDiagnoz(const Sick& couple, int counter);
    QString getAdmissionDate(const Sick& couple);
    QString getExtractDate(const Sick& couple);

    QString FileOpener(Sick* sick, const QString& content, int cuonter);

    void SortByDate(QList<Sick>* sicks);

    void SortByDiagnoz(QList<Sick>* sicks);
};

#endif  // SICK_H
