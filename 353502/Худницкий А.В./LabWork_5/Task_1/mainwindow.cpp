#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    startTime(QTime(0, 0, 0, 0)),
    progBarValue(MAX_VALUE) {
    ui->setupUi(this);
    setFixedSize(LENGTH, WIDTH);

    timer = new QTimer();
    keyboard = new Keyboard();
    keyboard->setSceneRect(0, 0, SCENE_LEN, SCENE_WIDTH);
    keyboard->init(ru);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(SCENE_LEN, SCENE_WIDTH);
    ui->graphicsView->setScene(keyboard);
    ui->progressBar->setValue(progBarValue);

    connect(keyboard, &Keyboard::keyPressed, this, &MainWindow::takeText);
    connect(keyboard, &Keyboard::keyPressed, this, &MainWindow::checkText);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);

    ui->timerLabel->setText("");
    ui->progressBar->setValue(MAX_VALUE);
    ui->wordCountLabel->setText("Words: 0");
    ui->wordsLabel->setText("0");
}

MainWindow::~MainWindow() {
    delete keyboard;
    keyboard = nullptr;

    delete timer;
    timer = nullptr;

    delete ui;
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
}

void MainWindow::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    ui->textBrowser->setText(content);

    exampleText = content;
    file.close();
}

void MainWindow::takeText(QChar simb) {

    if (simb == '\b' && !textForSet.isEmpty()) {
        textForSet.chop(1);
    }

    else {
        textForSet += simb;
    }
    ui->mainTextBrowser->setText(textForSet);
}

void MainWindow::checkText() {
    QString newText = ui->mainTextBrowser->toPlainText();
    QTextCursor cursor(ui->mainTextBrowser->document());

    int correctLength = 0;
    for (int i = 0; i < newText.length() && i < exampleText.length(); ++i) {
        if (newText[i] == exampleText[i]) {
            ++correctLength;
        } else {
            break;
        }
    }

    QTextCharFormat fmtBlack;
    fmtBlack.setForeground(Qt::black);
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(exampleText.length(), QTextCursor::KeepAnchor);
    cursor.mergeCharFormat(fmtBlack);

    if (correctLength < newText.length()) {
        --progBarValue;
        QTextCharFormat fmtRed;
        fmtRed.setForeground(Qt::red);
        cursor.setPosition(correctLength, QTextCursor::MoveAnchor);
        cursor.setPosition(newText.length(), QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(fmtRed);
    }

    ui->progressBar->setValue(progBarValue);

    QString correctText = newText.left(correctLength);
    int wordCount = 0;
    if (!correctText.isEmpty()) {
        QStringList words = correctText.split(QRegularExpression("\\s+"));
        wordCount = words.count();
    }

    ui->wordCountLabel->setText(QString("Words: %1").arg(wordCount));
    ui->wordsLabel->setText( QString::number(float(wordCount * ONE_MIN) / elapsed));

    if (newText == exampleText) {
        QMessageBox::information(this, "Хорош.", "Текст закончен.");
        timer->stop();
    }
}

void MainWindow::on_pushButton_clicked() {

    progBarValue = MAX_VALUE;
    timer->start(TIME_INTERVAL);
    startTime = QTime::currentTime();

    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
}

void MainWindow::updateTime() {
    elapsed = startTime.msecsTo(QTime::currentTime());
    QTime timeToShow(0, 0, 0, 1);
    timeToShow = timeToShow.addMSecs(elapsed);
    QString formattedTime = timeToShow.toString("   mm:ss.zzz");
    ui->timerLabel->setText(formattedTime);
}

void MainWindow::on_stopButton_clicked() {
    if (timer->isActive()) {
        timer->stop();
    }
}

void MainWindow::on_clearButton_clicked() {
    ui->mainTextBrowser->setText("");
    ui->timerLabel->setText("");
    ui->progressBar->setValue(MAX_VALUE);
    ui->wordCountLabel->setText("Words: 0");
    ui->wordsLabel->setText("0");
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    textForSet = "";
}

void MainWindow::on_comboBox_currentIndexChanged(const QString& arg1) {

    QString selectedItem = ui->comboBox->currentText();
    Language lang;
    if (selectedItem == "ru") {
        lang = ru;
    }
    if (selectedItem == "bel") {
        lang = bel;
    }
    if (selectedItem == "heb") {
        lang = heb;
    }
    if (selectedItem == "ger") {
        lang = ger;
    }
    if (selectedItem == "zhin") {
        lang = chin;
    }
    if (selectedItem == "arab") {
        lang = arab;
    }
    if (selectedItem == "en") {
        lang = en;
    }
    if (selectedItem == "fr") {
        lang = fr;
    }
    qDebug() << lang;

    keyboard->init(lang);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
}

void MainWindow::on_progressBar_valueChanged(int value)
{
    if (value == 0) {
        QMessageBox::information(this, "Это стыд", "Сто раз не попасть по нужной кнопке?! Вы подвели партию. Убирайтесь!");
        timer->stop();
        update();
        close();
    }
}

