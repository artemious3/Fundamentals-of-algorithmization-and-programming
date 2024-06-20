#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "vectorfunctioninformation.h"
#include "vectorkashko.h"
#include "pairkashko.h"

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
    void on_help_for_user_Button_clicked();

    void on_assignButton_clicked();
    void on_atButton_clicked();
    void on_backButton_clicked();
    void on_beginButton_clicked();
    void on_capacityButton_clicked();
    void on_reserveButton_clicked();
    void on_cbeginButton_clicked();
    void on_clearButton_clicked();
    void on_dataButton_clicked();
    void on_emplaceButton_clicked();
    void on_emplace_back_Button_clicked();
    void on_resizeButton_clicked();
    void on_emptyButton_clicked();
    void on_endButton_clicked();
    void on_eraseButton_clicked();
    void on_frontButton_clicked();
    void on_insertButton_clicked();
    void on_sizeButton_clicked();
    void on_max_size_Button_clicked();
    void on_pop_back_Button_clicked();
    void on_push_back_Button_clicked();
    void on_rbeginButton_clicked();
    void on_rendButton_clicked();
    void on_swapButton_clicked();
    void on_view_vector_content_Button_clicked();
    void on_vectorButton_clicked();
    void on_class_pair_Button_clicked();

private:
    Ui::MainWindow *ui;
    vectorKashko<int> vector;
    void updateResultTextBrowser(const QString &text);

    QTableWidget *tableWidgetInt;
    QTableWidget *tableWidgetPair;

    vectorKashko<int> intVector;
    vectorKashko<PairKashko<int, double>> pairVector;

    void setupUI();
    void populateTables();
};

#endif // MAINWINDOW_H
