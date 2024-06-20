#ifndef PATIENTSEARCHER_H
#define PATIENTSEARCHER_H

#include <QTableWidget>
#include <QTextBrowser>
#include <QTextEdit>

class PatientSearcher
{
public:
    PatientSearcher(QTableWidget *tableWidget,
                    QTextEdit *roomTextEdit,
                    QTextEdit *diagnosisTextEdit,
                    QTextEdit *fioTextEdit,
                    QTextBrowser *resultTextBrowser);

    void searchPatients();

private:
    QTableWidget *tableWidget;
    QTextEdit *roomTextEdit;
    QTextEdit *diagnosisTextEdit;
    QTextEdit *fioTextEdit;
    QTextBrowser *resultTextBrowser;
};

#endif // PATIENTSEARCHER_H
