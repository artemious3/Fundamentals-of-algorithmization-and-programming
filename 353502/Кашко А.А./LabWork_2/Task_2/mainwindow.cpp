#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_5->hide();
    ui->tableWidget_2->hide();
    ui->pushButton_6->hide();
    ui->pushButton_3->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_3->show();

    // Открыть диалоговое окно для выбора файла
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Открыть файл"),
                                                    "",
                                                    tr("Текстовые файлы (*.txt);;Все файлы (*)"));

    // Проверить, был ли выбран файл
    if (!filePath.isEmpty()) {
        // Если файл выбран, загрузить его данные в таблицу
        loadFileToTable(filePath);
    }
}

void MainWindow::loadFileToTable(const QString &filePath)
{
    // Открытие файла
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    // Инициализация потока для чтения данных из файла
    QTextStream in(&file);

    // Начальная строка таблицы
    int row = ui->tableWidget->rowCount(), column = 0;

    while (!in.atEnd()) {
        // Чтение строки из файла
        QString line = in.readLine();

        // Установка количества строк в QTableWidget
        ui->tableWidget->setRowCount(row + 1);

        // Создание элемента таблицы и его установка
        QTableWidgetItem *date = new QTableWidgetItem(line);
        ui->tableWidget->setItem(row, column, date);

        // Увеличение номера строки
        ++column;
        if (column == 4) {
            ++row;
            column = 0;
        }
    }

    // Закрытие файла после завершения чтения
    file.close();
}

void MainWindow::on_pushButton_4_clicked()
{
    // Получение данных из элементов управления
    QString fio = ui->textEdit->toPlainText();
    QString gender = ui->comboBox->currentText();
    QString age = ui->textEdit_3->toPlainText();
    QString diagnosis = ui->textEdit_4->toPlainText();

    // Добавление данных в tableWidget
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rowCount + 1);

    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(fio));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(gender));
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(age));
    ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(diagnosis));

    // Очистка элементов управления после добавления данных
    ui->textEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_5->show();
    ui->pushButton_4->hide();
    ui->pushButton_6->show();
    PatientManager manager;
    manager.distributePatientsToRooms(ui->tableWidget, ui->tableWidget_2);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableWidget_2->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    PatientSearcher searcher(ui->tableWidget,
                             ui->textEdit_2,
                             ui->textEdit_5,
                             ui->textEdit_6,
                             ui->textBrowser);
    searcher.searchPatients();
}
