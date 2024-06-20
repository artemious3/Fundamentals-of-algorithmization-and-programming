#include "distributepatientstorooms.h"

PatientManager::PatientManager() {}

void PatientManager::distributePatientsToRooms(QTableWidget *tableWidget,
                                               QTableWidget *lonelyTableWidget)
{
    // Очищаем карту пациентов
    patientsMap.clear();

    // Заполнение карты пациентов
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        Patient patient;
        patient.fio = tableWidget->item(row, 0)->text();
        patient.gender = tableWidget->item(row, 1)->text();
        patient.age = tableWidget->item(row, 2)->text();
        patient.diagnosis = tableWidget->item(row, 3)->text();
        patient.roomNumber = 0;

        QString key = patient.gender + "_" + patient.diagnosis;
        patientsMap[key].append(patient);
    }

    int roomNumber = 1;

    // Установка количества колонок и заголовков для основной таблицы
    tableWidget->setColumnCount(5);
    QStringList headers;
    headers << "ФИО"
            << "Пол"
            << "Возраст"
            << "Диагноз"
            << "Номер палаты";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Установка количества колонок и заголовков для таблицы одиночек
    lonelyTableWidget->setColumnCount(4);
    QStringList lonelyHeaders;
    lonelyHeaders << "ФИО"
                  << "Пол"
                  << "Возраст"
                  << "Диагноз";
    lonelyTableWidget->setHorizontalHeaderLabels(lonelyHeaders);

    int row = 0;
    int lonelyRow = 0;
    for (auto it = patientsMap.begin(); it != patientsMap.end(); ++it) {
        QList<Patient> &patients = it.value();
        for (Patient &patient : patients) {
            QTableWidgetItem *fioItem = new QTableWidgetItem(patient.fio);
            QTableWidgetItem *genderItem = new QTableWidgetItem(patient.gender);
            QTableWidgetItem *ageItem = new QTableWidgetItem(patient.age);
            QTableWidgetItem *diagnosisItem = new QTableWidgetItem(patient.diagnosis);
            QTableWidgetItem *roomNumberItem = new QTableWidgetItem(QString::number(roomNumber));

            tableWidget->setRowCount(row + 1);
            tableWidget->setItem(row, 0, fioItem);
            tableWidget->setItem(row, 1, genderItem);
            tableWidget->setItem(row, 2, ageItem);
            tableWidget->setItem(row, 3, diagnosisItem);
            tableWidget->setItem(row, 4, roomNumberItem);
            patient.roomNumber = roomNumber;

            ++row;
        }
        if (patients.size() == 1) {
            const Patient &patient = patients.first();

            QTableWidgetItem *fioItem = new QTableWidgetItem(patient.fio);
            QTableWidgetItem *genderItem = new QTableWidgetItem(patient.gender);
            QTableWidgetItem *ageItem = new QTableWidgetItem(patient.age);
            QTableWidgetItem *diagnosisItem = new QTableWidgetItem(patient.diagnosis);

            lonelyTableWidget->setRowCount(lonelyRow + 1);
            lonelyTableWidget->setItem(lonelyRow, 0, fioItem);
            lonelyTableWidget->setItem(lonelyRow, 1, genderItem);
            lonelyTableWidget->setItem(lonelyRow, 2, ageItem);
            lonelyTableWidget->setItem(lonelyRow, 3, diagnosisItem);

            ++lonelyRow;
        }
        ++roomNumber;
    }

    // Удаление одиночек из основной таблицы
    for (auto it = patientsMap.begin(); it != patientsMap.end();) {
        if (it.value().size() == 1) {
            it = patientsMap.erase(it);
        } else {
            ++it;
        }
    }

    // Обновление основной таблицы после удаления одиночек
    tableWidget->setRowCount(0);
    row = 0;
    for (auto it = patientsMap.begin(); it != patientsMap.end(); ++it) {
        QList<Patient> &patients = it.value();
        for (const Patient &patient : patients) {
            QTableWidgetItem *fioItem = new QTableWidgetItem(patient.fio);
            QTableWidgetItem *genderItem = new QTableWidgetItem(patient.gender);
            QTableWidgetItem *ageItem = new QTableWidgetItem(patient.age);
            QTableWidgetItem *diagnosisItem = new QTableWidgetItem(patient.diagnosis);
            QTableWidgetItem *roomNumberItem = new QTableWidgetItem(
                QString::number(patient.roomNumber));

            tableWidget->setRowCount(row + 1);
            tableWidget->setItem(row, 0, fioItem);
            tableWidget->setItem(row, 1, genderItem);
            tableWidget->setItem(row, 2, ageItem);
            tableWidget->setItem(row, 3, diagnosisItem);
            tableWidget->setItem(row, 4, roomNumberItem);

            ++row;
        }
    }
}
