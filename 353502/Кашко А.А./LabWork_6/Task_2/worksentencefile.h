#ifndef WORKSENTENCEFILE_H
#define WORKSENTENCEFILE_H

#include <QDialog>
#include <QFile>
#include <QTextEdit>
#include <QTextStream>

namespace Ui {
class WorkSentenceFile;
}

class WorkSentenceFile : public QDialog
{
    Q_OBJECT

public:
    explicit WorkSentenceFile(QWidget *parent = nullptr);
    ~WorkSentenceFile();

private slots:
    void on_closeButton_clicked();

    void on_showButton_clicked();

private:
    Ui::WorkSentenceFile *ui;

    void onTextEntered();
};

#endif // WORKSENTENCEFILE_H
