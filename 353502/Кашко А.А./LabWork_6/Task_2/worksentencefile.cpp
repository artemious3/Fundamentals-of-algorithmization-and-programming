#include "worksentencefile.h"
#include "ui_worksentencefile.h"
#include <QMessageBox>
#include <QRegularExpression>

WorkSentenceFile::WorkSentenceFile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkSentenceFile)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &WorkSentenceFile::onTextEntered);
}

WorkSentenceFile::~WorkSentenceFile()
{
    delete ui;
}

void WorkSentenceFile::on_closeButton_clicked()
{
    close();
}

void WorkSentenceFile::onTextEntered()
{
    QString text = ui->textEdit->toPlainText();

    QRegularExpression re(R"(([^.!?]*[.!?]){2,})");
    QRegularExpressionMatch match = re.match(text);

    if (match.hasMatch()) {
        QMessageBox::warning(this, tr("Ошибка ввода!"), tr("Пожалуйста, введите одно предложение!"));

        ui->textEdit->clear();
    } else if (text.contains('\n')) {
        ui->textEdit->clear();

        QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьПредложения.txt");
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

void WorkSentenceFile::on_showButton_clicked()
{
    QFile file("/home/nastya/laba6_Kashko/Кашко_ЗаписьПредложения.txt");
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
