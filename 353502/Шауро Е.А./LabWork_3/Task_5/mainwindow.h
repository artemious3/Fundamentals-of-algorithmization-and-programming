#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString sourceDir;

    int countDirs(QDir dir, bool isDot = false);
    int countFiles(QDir dir, QString prefix);
};
// MAINWINDOW_H
