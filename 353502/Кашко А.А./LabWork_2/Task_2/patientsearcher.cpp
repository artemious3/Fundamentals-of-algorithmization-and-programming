#include "patientsearcher.h"

PatientSearcher::PatientSearcher(QTableWidget *tableWidget,
                                 QTextEdit *roomTextEdit,
                                 QTextEdit *diagnosisTextEdit,
                                 QTextEdit *fioTextEdit,
                                 QTextBrowser *resultTextBrowser)
    : tableWidget(tableWidget)
    , roomTextEdit(roomTextEdit)
    , diagnosisTextEdit(diagnosisTextEdit)
    , fioTextEdit(fioTextEdit)
    , resultTextBrowser(resultTextBrowser)
{}

void PatientSearcher::searchPatients()
{
    QString roomNumber = roomTextEdit->toPlainText();
    QString diagnosis = diagnosisTextEdit->toPlainText();
    QString fio = fioTextEdit->toPlainText();

    if (roomNumber.isEmpty() || diagnosis.isEmpty() || fio.isEmpty()) {
        resultTextBrowser->clear();
        return;
    }

    resultTextBrowser->clear();

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        bool match = true;

        if (!roomNumber.isEmpty()) {
            QTableWidgetItem *item = tableWidget->item(row, 4);
            if (item && item->text() != roomNumber) {
                match = false;
            }
        }

        if (!diagnosis.isEmpty()) {
            QTableWidgetItem *item = tableWidget->item(row, 3);
            if (item && item->text() != diagnosis) {
                match = false;
            }
        }

        if (!fio.isEmpty()) {
            QTableWidgetItem *item = tableWidget->item(row, 0);
            if (item && !item->text().contains(fio, Qt::CaseInsensitive)) {
                match = false;
            }
        }

        if (match) {
            resultTextBrowser->append(QString::number(row + 1));
            return; // Выходим из цикла после первого совпадения
        }
    }
}
