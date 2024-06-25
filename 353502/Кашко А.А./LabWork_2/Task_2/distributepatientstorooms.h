#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>

struct Patient
{
    QString fio;
    QString gender;
    QString age;
    QString diagnosis;
    int roomNumber; // Номер палаты
};

class PatientManager
{
public:
    PatientManager();

    void distributePatientsToRooms(QTableWidget *tableWidget, QTableWidget *lonelyTableWidget);

private:
    QMap<QString, QList<Patient>> patientsMap; // карта пациента
};

#endif // PATIENTMANAGER_H
