#include "worktextfile.h"
#include "ui_worktextfile.h"
#include "iostream"

WorkTextFile::WorkTextFile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkTextFile)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &WorkTextFile::onTextEntered);
}

WorkTextFile::~WorkTextFile()
{
    delete ui;
}

void WorkTextFile::on_closeButton_clicked()
{
    close();
}

void WorkTextFile::onTextEntered()
{
    QString text = ui->textEdit->toPlainText();

    if (text.contains('\n')) {
        ui->textEdit->clear();

        QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьТекста.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            QTextStream out(&file);
            out.setEncoding(QStringConverter::Utf8); // Устанавливаем кодировку UTF-8

            for (QChar c : text) {
                out << c;
            }

            file.close();
        }
    }
}

void WorkTextFile::on_showButton_clicked()
{
    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьТекста.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Utf8); // Устанавливаем кодировку UTF-8

        QString fileContent;
        while (!in.atEnd()) {
            QChar c;
            in >> c;
            fileContent.append(c);
        }

        ui->textBrowser->setPlainText(fileContent);
        file.close();
    }
}
