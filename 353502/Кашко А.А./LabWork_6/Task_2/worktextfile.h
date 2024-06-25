#ifndef WORKTEXTFILE_H
#define WORKTEXTFILE_H

#include <QDialog>
#include <QFile>
#include <QTextEdit>
#include <QTextStream>

namespace Ui {
class WorkTextFile;
}

class WorkTextFile : public QDialog
{
    Q_OBJECT

public:
    explicit WorkTextFile(QWidget *parent = nullptr);
    ~WorkTextFile();

private slots:
    void on_closeButton_clicked();

    void onTextEntered();

    void on_showButton_clicked();

private:
    Ui::WorkTextFile *ui;
};

#endif // WORKTEXTFILE_H
