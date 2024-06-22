#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<int> dataSizes = {16, 64, 1024, 2048};
    QVector<QChartView *> chartViews;
    QVector<qint64> timings;

    QElapsedTimer* timer = new QElapsedTimer();

    for(int size : dataSizes)
    {
        timings.clear();
        table = new HashTable<int>(size, rand() % 10000 / 3);

        for (int i = 0; i < size; ++i) {

            std::string str;
            for(int j = 0; j < rand() % 9 + 1; j++)
            {
                str += char(rand() % 29 + 97);
            }

            table->insert(str, i);
        }

        std::string str;
        for(int j = 0; j < rand() % 9 + 1; j++)
        {
            str += char(rand() % 29 + 97);
        }

        for(int i = 0; i <= 100; i++)
        {
            timer->start();

            table->search(str);

            timings.append(timer->nsecsElapsed());
            timer->restart();
        }

        QLineSeries *series = new QLineSeries();
        for (int i = 1; i <= 100; ++i) {
            series->append(i, timings[i]);
        }

        series->setName("Search times for size " + QString::number(size));

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Time of Hash Table Search Function with size = " + QString::number(size));
        chart->setAnimationOptions(QChart::AllAnimations);

        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("Number of search");
        axisX->setLabelFormat("%i");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Time (ns)");
        axisY->setLabelFormat("%i");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QList<QLegendMarker*> markers = chart->legend()->markers(series);
        for (QLegendMarker* marker : markers) {
            marker->setVisible(false);
        }

        chartViews.append(chartView);
    }


    for(int i = 0; i < 4; i++)
    {
        if(i == 0 || i == 1) ui->firstLayer->addWidget(chartViews[i]);
        if(i == 2 || i == 3) ui->secondLayer->addWidget(chartViews[i]);
    }

    for(QChartView* view : chartViews)
    {

        //ui->verticalLayout->addWidget(view);
    }


    //table->print(ui->listWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
