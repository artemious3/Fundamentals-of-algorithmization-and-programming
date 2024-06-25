#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->assignButton->hide();
    ui->atButton->hide();
    ui->backButton->hide();
    ui->beginButton->hide();
    ui->capacityButton->hide();
    ui->cbeginButton->hide();
    ui->clearButton->hide();
    ui->dataButton->hide();
    ui->emplaceButton->hide();
    ui->emplace_back_Button->hide();
    ui->emptyButton->hide();
    ui->endButton->hide();
    ui->eraseButton->hide();
    ui->frontButton->hide();
    ui->insertButton->hide();
    ui->max_size_Button->hide();
    ui->pop_back_Button->hide();
    ui->push_back_Button->hide();
    ui->rbeginButton->hide();
    ui->rendButton->hide();
    ui->reserveButton->hide();
    ui->resizeButton->hide();
    ui->sizeButton->hide();
    ui->swapButton->hide();
    ui->help_for_user_Button->hide();
    ui->view_vector_content_Button->hide();
    ui->vector_content_textBrowser->hide();
    ui->function_result_textBrowser->hide();
    ui->function_label->hide();
    ui->function_result_label->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateResultTextBrowser(const QString &text)
{
    ui->function_result_textBrowser->clear();
    ui->function_result_textBrowser->append(text);
}

void MainWindow::on_help_for_user_Button_clicked()
{
    VectorFunctionInformation *screen = new VectorFunctionInformation();
    screen->show();
}

void MainWindow::on_assignButton_clicked()
{
    vector.assign({1, 2, 3, 4, 5});
    updateResultTextBrowser("Назначены значения: {1, 2, 3, 4, 5}");
}

void MainWindow::on_atButton_clicked()
{
    try {
        int value = vector.at(2);
        updateResultTextBrowser(QString("Элемент по индексу 2: %1").arg(value));
    } catch (const std::out_of_range &e) {
        updateResultTextBrowser("Индекс вне диапазона");
    }
}

void MainWindow::on_backButton_clicked()
{
    try {
        int value = vector.back();
        updateResultTextBrowser(QString("Последний элемент: %1").arg(value));
    } catch (const std::out_of_range &e) {
        updateResultTextBrowser("Вектор пуст");
    }
}

void MainWindow::on_beginButton_clicked()
{
    auto it = vector.begin();
    updateResultTextBrowser(QString("Итератор begin указывает на: %1").arg(*it));
}

void MainWindow::on_capacityButton_clicked()
{
    updateResultTextBrowser(QString("Емкость: %1").arg(vector.capacity()));
}

void MainWindow::on_reserveButton_clicked()
{
    vector.reserve(10);
    updateResultTextBrowser("Зарезервировано место для 10 элементов");
}

void MainWindow::on_cbeginButton_clicked()
{
    auto it = vector.cbegin();
    updateResultTextBrowser(QString("Константный итератор cbegin указывает на: %1").arg(*it));
}

void MainWindow::on_clearButton_clicked()
{
    vector.clear();
    updateResultTextBrowser("Вектор очищен");
}

void MainWindow::on_dataButton_clicked()
{
    auto data = vector.data();
    updateResultTextBrowser(QString("Указатель на данные: %1").arg(reinterpret_cast<uintptr_t>(data)));
}

void MainWindow::on_emplaceButton_clicked()
{
    vector.emplace(vector.begin() + 1, 10);
    updateResultTextBrowser("Добавлено значение 10 на позицию 1");
}

void MainWindow::on_emplace_back_Button_clicked()
{
    vector.emplace_back(20);
    updateResultTextBrowser("Добавлено значение 20 в конец");
}

void MainWindow::on_resizeButton_clicked()
{
    vector.resize(3);
    updateResultTextBrowser("Размер вектора изменен до 3 элементов");
}

void MainWindow::on_emptyButton_clicked()
{
    bool isEmpty = vector.empty();
    updateResultTextBrowser(QString("Вектор пустой? %1").arg(isEmpty ? "Да" : "Нет"));
}

void MainWindow::on_endButton_clicked()
{
    auto it = vector.end();
    updateResultTextBrowser("Итератор end");
}

void MainWindow::on_eraseButton_clicked()
{
    vector.erase(vector.begin());
    updateResultTextBrowser("Удален первый элемент");
}

void MainWindow::on_frontButton_clicked()
{
    try {
        int value = vector.front();
        updateResultTextBrowser(QString("Первый элемент: %1").arg(value));
    } catch (const std::out_of_range &e) {
        updateResultTextBrowser("Вектор пуст");
    }
}

void MainWindow::on_insertButton_clicked()
{
    vector.insert(vector.begin(), 30);
    updateResultTextBrowser("Добавлено значение 30 в начало");
}

void MainWindow::on_sizeButton_clicked()
{
    updateResultTextBrowser(QString("Размер: %1").arg(vector.size()));
}

void MainWindow::on_max_size_Button_clicked()
{
    updateResultTextBrowser(QString("Максимальный размер: %1").arg(vector.max_size()));
}

void MainWindow::on_pop_back_Button_clicked()
{
    try {
        vector.pop_back();
        updateResultTextBrowser("Удален последний элемент");
    } catch (const std::out_of_range &e) {
        updateResultTextBrowser("Вектор пуст");
    }
}

void MainWindow::on_push_back_Button_clicked()
{
    vector.push_back(40);
    updateResultTextBrowser("Добавлено значение 40 в конец");
}

void MainWindow::on_rbeginButton_clicked()
{
    auto it = vector.rbegin();
    updateResultTextBrowser(QString("Итератор rbegin указывает на: %1").arg(*it));
}

void MainWindow::on_rendButton_clicked()
{
    auto it = vector.rend();
    updateResultTextBrowser("Итератор rend");
}

void MainWindow::on_swapButton_clicked()
{
    vectorKashko<int> other;
    other.assign({50, 60});
    vector.swap(other);
    updateResultTextBrowser("Вектор обменян с другим вектором {50, 60}");
}

void MainWindow::on_view_vector_content_Button_clicked()
{
    int* data = vector.data();
    std::size_t size = vector.size();
    ui->vector_content_textBrowser->clear();

    // Выводим содержимое вектора в textBrowser
    for (std::size_t i = 0; i < size; ++i) {
        ui->vector_content_textBrowser->append(QString::number(data[i]));
    }
}


void MainWindow::on_vectorButton_clicked()
{
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);
    vector.push_back(6);
    vector.push_back(7);
    vector.push_back(8);
    vector.push_back(9);
    vector.push_back(10);

    ui->assignButton->show();
    ui->atButton->show();
    ui->backButton->show();
    ui->beginButton->show();
    ui->capacityButton->show();
    ui->cbeginButton->show();
    ui->clearButton->show();
    ui->dataButton->show();
    ui->emplaceButton->show();
    ui->emplace_back_Button->show();
    ui->emptyButton->show();
    ui->endButton->show();
    ui->eraseButton->show();
    ui->frontButton->show();
    ui->insertButton->show();
    ui->max_size_Button->show();
    ui->pop_back_Button->show();
    ui->push_back_Button->show();
    ui->rbeginButton->show();
    ui->rendButton->show();
    ui->reserveButton->show();
    ui->resizeButton->show();
    ui->sizeButton->show();
    ui->swapButton->show();
    ui->help_for_user_Button->show();
    ui->view_vector_content_Button->show();
    ui->vector_content_textBrowser->show();
    ui->function_result_textBrowser->show();
    ui->function_label->show();
    ui->function_result_label->show();
}

void MainWindow::setupUI() {
    tableWidgetInt = new QTableWidget(this);
    tableWidgetPair = new QTableWidget(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tableWidgetInt);
    layout->addWidget(tableWidgetPair);

    QWidget *container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}

void MainWindow::populateTables() {
    // Пример заполнения данных
    intVector.push_back(1);
    intVector.push_back(2);
    intVector.push_back(3);
    intVector.push_back(4);
    intVector.push_back(5);
    intVector.push_back(6);
    intVector.push_back(7);
    intVector.push_back(8);
    intVector.push_back(9);

    pairVector.push_back(PairKashko<int, double>(1, 1.1));
    pairVector.push_back(PairKashko<int, double>(2, 2.2));
    pairVector.push_back(PairKashko<int, double>(3, 3.3));
    pairVector.push_back(PairKashko<int, double>(4, 4.4));
    pairVector.push_back(PairKashko<int, double>(5, 5.5));
    pairVector.push_back(PairKashko<int, double>(6, 6.6));
    pairVector.push_back(PairKashko<int, double>(7, 7.7));
    pairVector.push_back(PairKashko<int, double>(8, 8.8));
    pairVector.push_back(PairKashko<int, double>(9, 9.9));

    tableWidgetInt->setRowCount(intVector.size());
    tableWidgetInt->setColumnCount(1);
    for (size_t i = 0; i < intVector.size(); ++i) {
        tableWidgetInt->setItem(i, 0, new QTableWidgetItem(QString::number(intVector.at(i))));
    }

    tableWidgetPair->setRowCount(pairVector.size());
    tableWidgetPair->setColumnCount(2);
    for (size_t i = 0; i < pairVector.size(); ++i) {
        tableWidgetPair->setItem(i, 0, new QTableWidgetItem(QString::number(pairVector.at(i).first)));
        tableWidgetPair->setItem(i, 1, new QTableWidgetItem(QString::number(pairVector.at(i).second)));
    }
}

void MainWindow::on_class_pair_Button_clicked()
{
    setupUI();
    populateTables();
}

