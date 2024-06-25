#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->hide();
    ui->pushButton_5->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    int row = ui->tableWidget->rowCount();

    while (!in.atEnd()) {
        // Чтение строки (даты) из файла
        QString line = in.readLine();

        // Установка количества строк в QTableWidget
        ui->tableWidget->setRowCount(row + 1);

        // Создание элемента таблицы для текущей даты и его установка
        QTableWidgetItem *currentDateItem = new QTableWidgetItem(line);
        ui->tableWidget->setItem(row, 0, currentDateItem);

        // Создание элемента таблицы для следующей даты и его установка
        QTableWidgetItem *nextDateItem = new QTableWidgetItem(
            functionForWorkWithDate->getNextDay(line).toString("dd.MM.yyyy"));
        ui->tableWidget->setItem(row, 1, nextDateItem);

        // Создание элемента таблицы для предыдущей даты и его установка
        QTableWidgetItem *previousDateItem = new QTableWidgetItem(
            functionForWorkWithDate->getPreviousDay(line).toString("dd.MM.yyyy"));
        ui->tableWidget->setItem(row, 2, previousDateItem);

        // Установка значения високосного года в четвертый столбец текущей строки таблицы
        int year = QDate::fromString(line, "dd.MM.yyyy").year();
        QTableWidgetItem *leapYearItem = new QTableWidgetItem(
            functionForWorkWithDate->isLeapYear(year) ? "true" : "false");
        ui->tableWidget->setItem(row, 3, leapYearItem);

        // Установка номера недели в пятый столбец текущей строки таблицы
        QTableWidgetItem *weekNumberItem = new QTableWidgetItem(
            QString::number(functionForWorkWithDate->getWeekNumber(line)));
        ui->tableWidget->setItem(row, 4, weekNumberItem);

        // Увеличение номера строки
        ++row;
    }

    // Закрытие файла после завершения чтения
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_3->show();
    ui->pushButton_5->show();
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

void MainWindow::on_pushButton_4_clicked()
{
    QDate selectedDate = ui->calendarWidget_2->selectedDate();
    QString dateString = selectedDate.toString("dd.MM.yyyy");

    int newRow = ui->tableWidget->rowCount(); // Новая строка в таблице
    ui->tableWidget->setRowCount(newRow + 1);

    // Установка выбранной даты в первый столбец новой строки таблицы
    QTableWidgetItem *currentDateItem = new QTableWidgetItem(dateString);
    ui->tableWidget->setItem(newRow, 0, currentDateItem);

    // Установка следующей даты во второй столбец новой строки таблицы
    QTableWidgetItem *nextDateItem = new QTableWidgetItem(
        functionForWorkWithDate->getNextDay(dateString).toString("dd.MM.yyyy"));
    ui->tableWidget->setItem(newRow, 1, nextDateItem);

    // Установка предыдущей даты в третий столбец новой строки таблицы
    QTableWidgetItem *previousDateItem = new QTableWidgetItem(
        functionForWorkWithDate->getPreviousDay(dateString).toString("dd.MM.yyyy"));
    ui->tableWidget->setItem(newRow, 2, previousDateItem);

    // Установка значения високосного года в четвертый столбец новой строки таблицы
    int year = selectedDate.year();
    QTableWidgetItem *leapYearItem = new QTableWidgetItem(
        functionForWorkWithDate->isLeapYear(year) ? "true" : "false");
    ui->tableWidget->setItem(newRow, 3, leapYearItem);

    // Установка номера недели в пятый столбец новой строки таблицы
    QTableWidgetItem *weekNumberItem = new QTableWidgetItem(
        QString::number(functionForWorkWithDate->getWeekNumber(dateString)));
    ui->tableWidget->setItem(newRow, 4, weekNumberItem);

    // Запись новой даты в файл
    functionForWorkWithDate->writeToFile("file.txt", dateString);
}

void MainWindow::on_pushButton_3_clicked()
{
    //получаем количество строк в таблице
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; i++) {
        //извлекаем дату из виджета и заносим её в переменную
        QDate selectedDate = ui->calendarWidget->selectedDate();

        //извлекаем дату из таблицы
        QTableWidgetItem *dateHelp = ui->tableWidget->item(i, 0);
        //преобразуем данные из таблицы в текст
        QString dateStringHelp = dateHelp->text();
        QDate date = QDate::fromString(dateStringHelp, "dd.MM.yyyy");

        int daysDifference = functionForWorkWithDate->DaysDifference(i, selectedDate, date);

        //устанавливаем разницу между днями в таблицу
        QTableWidgetItem *differenceItem = new QTableWidgetItem(QString::number(daysDifference));
        ui->tableWidget->setItem(i, 5, differenceItem);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString numberRowString = ui->textEdit->toPlainText();
    int numberRow = numberRowString.toInt();
    numberRow--;
    if (numberRow < 0) {
        numberRow = (ui->tableWidget->rowCount()) - 1;
    }
    //извлекаем дату из виджета и заносим её в переменную
    QDate selectedDate = ui->calendarWidget_3->selectedDate();
    //преобразуем дату в строковый формат
    QString dateString = selectedDate.toString("dd.MM.yyyy");
    //установка выбранной даты в новую строку таблицы
    QTableWidgetItem *currentDateItem = new QTableWidgetItem(dateString);
    ui->tableWidget->setItem(numberRow, 0, currentDateItem);

    // Установка следующей даты во второй столбец новой строки таблицы
    QTableWidgetItem *nextDateItem = new QTableWidgetItem(
        functionForWorkWithDate->getNextDay(dateString).toString("dd.MM.yyyy"));
    ui->tableWidget->setItem(numberRow, 1, nextDateItem);

    // Установка предыдущей даты в третий столбец новой строки таблицы
    QTableWidgetItem *previousDateItem = new QTableWidgetItem(
        functionForWorkWithDate->getPreviousDay(dateString).toString("dd.MM.yyyy"));
    ui->tableWidget->setItem(numberRow, 2, previousDateItem);

    // Установка значения високосного года в четвертый столбец новой строки таблицы
    int year = selectedDate.year();
    QTableWidgetItem *leapYearItem = new QTableWidgetItem(
        functionForWorkWithDate->isLeapYear(year) ? "true" : "false");
    ui->tableWidget->setItem(numberRow, 3, leapYearItem);

    // Установка номера недели в пятый столбец новой строки таблицы
    QTableWidgetItem *weekNumberItem = new QTableWidgetItem(
        QString::number(functionForWorkWithDate->getWeekNumber(dateString)));
    ui->tableWidget->setItem(numberRow, 4, weekNumberItem);
}
