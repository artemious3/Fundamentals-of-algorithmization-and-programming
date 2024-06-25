#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include "newpair.h"
#include "newvector.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_cbeginButton_clicked();
    void on_dataButton_clicked();
    void on_beginButton_clicked();
    void on_backButton_clicked();
    void on_assignButton_clicked();
    void on_atButton_clicked();
    void on_capacityButton_clicked();
    void on_reserveButton_clicked();
    void on_clearButton_clicked();
    void on_emplaceButton_clicked();
    void on_emplace_back_Button_clicked();
    void on_resizeButton_clicked();
    void on_emptyButton_clicked();
    void on_eraseButton_clicked();
    void on_frontButton_clicked();
    void on_insertButton_clicked();
    void on_sizeButton_clicked();
    void on_max_size_Button_clicked();
    void on_pop_back_Button_clicked();
    void on_push_back_Button_clicked();
    void on_swapButton_clicked();
    void on_actionPair_triggered();

private:
    Ui::MainWindow *ui;
    NewVector<int> vector;
    void updateResultTextBrowser(const QString &text);
    void updateBrowsers();
    void showMessage(const QString& str);

    QTableWidget *tableWidgetInt;
    QTableWidget *tableWidgetPair;

    NewVector<int> intVector;
    NewVector<NewPair<int, double>> pairVector;

    void setupUI();
    void populateTables();
};

#endif // MAINWINDOW_H
