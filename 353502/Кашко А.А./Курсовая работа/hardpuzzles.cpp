#include "hardpuzzles.h"
#include "ui_hardpuzzles.h"

HardPuzzles::HardPuzzles(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HardPuzzles)
{
    ui->setupUi(this);

    ui->label_2->hide();
    ui->label_4->hide();
    ui->textEdit->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();

    ui->pushButton->setStyleSheet("background-color: pink;");
    ui->pushButton_2->setStyleSheet("background-color: pink;");
    ui->pushButton_3->setStyleSheet("background-color: pink;");
    ui->pushButton_4->setStyleSheet("background-color: pink;");
    ui->pushButton_5->setStyleSheet("background-color: pink;");
    ui->pushButton_6->setStyleSheet("background-color: pink;");

    scene = new GraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->installEventFilter(this);

    // Инициализируем QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HardPuzzles::swapImageParts);
    // Запускаем таймер с интервалом 5 секунд
    timer->start(5000);
}

HardPuzzles::~HardPuzzles()
{
    delete ui;
}

void HardPuzzles::themesPuzzle(int choise)
{
    switch(choise) {
    case 0:
        themes = 0;
        break;
    case 1:
        themes = 1;
        break;
    case 2:
        themes = 2;
        break;
    case 3:
        themes = 3;
        break;
    case 4:
        themes = 4;
        break;
    default:
        break;
    }
}

QList<QImage> HardPuzzles::splitImage(const QString& filename) {
    // Загрузка изображения из файла
    QImage originalImage(filename);
    QSize targetSize(450, 300);
    originalImage = originalImage.scaled(targetSize, Qt::KeepAspectRatio);

    if(originalImage.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить изображение";
        return imageParts;
    }

    // Определение размеров каждой части
    int partWidth = originalImage.width() / 6;
    int partHeight = originalImage.height() / 4;

    // Разбиение изображения на 24 равных части
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 6; ++x) {
            QRect rect(x * partWidth, y * partHeight, partWidth, partHeight);
            QImage part = originalImage.copy(rect);
            imageParts.append(part);
        }
    }

    for (int i = 0; i < imageParts.size(); ++i) {
        int xPos = (i % 6) * imageParts[i].width();
        int yPos = (i / 6) * imageParts[i].height();
        partPositions.insert(i, QPointF(xPos, yPos));
    }

    return imageParts;
}

void HardPuzzles::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->show();
    ui->pushButton_3->show();

    // Загрузка и разделение изображения
    switch(themes) {
    case 0:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_sea/sea15";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_sea/sea16";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_sea/sea17";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_sea/sea18";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_sea/sea19";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_sea/sea20";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_sea/sea21";
        break;
    case 1:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_animal/animal15";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_animal/animal16";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_animal/animal17";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_animal/animal18";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_animal/animal19";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_animal/animal20";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_animal/animal21";
        break;
    case 2:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_nature/nature15";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_nature/nature16";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_nature/nature17";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_nature/nature18";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_nature/nature19";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_nature/nature20";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_nature/nature21";
        break;
    case 3:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_game/game15";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_game/game16";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_game/game17";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_game/game18";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_game/game19";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_game/game20";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_game/game21";
        break;
    case 4:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_good/good15";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_good/good16";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_good/good17";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_good/good18";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_good/good19";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_good/good20";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_good/good21";
        break;
    default:
        break;
    }
    imageParts = splitImage(filename);

    // Отображение всех частей изображения на графической сцене
    for (int i = 0; i < imageParts.size(); ++i) {
        // Создание элемента QGraphicsPixmapItem для текущей части изображения
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(imageParts[i]));

        pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, true);

        // Расположение текущей части на сцене (расположение может быть настроено по вашему выбору)
        int xPos = (i % 6) * imageParts[i].width(); // Размещение частей по горизонтали (в этом примере 3 части в ряд)
        int yPos = (i / 6) * imageParts[i].height(); // Размещение частей по вертикали

        pixmapItem->setPos(xPos, yPos); // Установка позиции элемента на сцене
        // Добавление элемента на графическую сцену
        scene->addItem(pixmapItem);
        indexes[pixmapItem] = i;
        QGraphicsRectItem *outlineRect = new QGraphicsRectItem(xPos, yPos, imageParts[i].width(), imageParts[i].height());
        outlineRect->setPen(QPen(Qt::black)); // Установка цвета контура
        scene->addItem(outlineRect);
    }

    timer->start(5000);
}

void HardPuzzles::swapImageParts() {
    // Получаем список индексов частей
    QList<int> partIndexes = partPositions.keys();

    // Перемешиваем индексы
    std::shuffle(partIndexes.begin(), partIndexes.end(), std::mt19937(std::random_device()()));

    // Меняем позиции между собой
    for (int i = 0; i < partIndexes.size(); ++i) {
        QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem *>(scene->items().at(partIndexes[i]));
        if (item) {
            // Выбираем новую позицию для текущей части, чтобы она не перекрывалась с другими частями
            QPointF newPos;
            do {
                newPos = partPositions.value(partIndexes[i]);
            } while (newPos == item->pos()); // Проверяем, не равна ли новая позиция текущей позиции
            item->setPos(newPos);
            //partPositions[partIndexes[i]] = newPos;
        }
    }

    // Остановка таймера после первой смены позиций
    timer->stop();
}

bool HardPuzzles::eventFilter(QObject *obj, QEvent *ev) {
    if(ev->type() == QEvent::GraphicsSceneMousePress) {
        for(auto& item : scene->items()) {
            item = (QGraphicsPixmapItem*)item;
            if(item->type() == 7) {
                auto mPos = ((QGraphicsSceneMouseEvent*)ev)->scenePos();
                if(item->isUnderMouse()) {
                    selectedItem = dynamic_cast<QGraphicsPixmapItem *>(item);
                    break;
                }
            }
        }
    }
    if(ev->type() == QEvent::GraphicsSceneMouseRelease) {
        // Проверяем, выбран ли какой-либо элемент для перемещения
        if (selectedItem) {
            // Получаем индекс элемента в графической сцене
            int index = indexes[selectedItem];

            // Получаем координаты выбранной части пазла из partPositions
            QPointF partCoordinates = partPositions.value(index);
            qreal xCoord1 = partCoordinates.x(); // Получаем координату x
            qreal yCoord1 = partCoordinates.y(); // Получаем координату y

            // Получаем текущие координаты позиции пазлинки после отпускания мыши
            QPointF releasedPosition = selectedItem->pos();
            qreal xCoord2 = releasedPosition.x(); // Получаем координату x
            qreal yCoord2 = releasedPosition.y(); // Получаем координату y
            //qDebug() << xCoord1 << " " << xCoord2 << " - " << yCoord1 << " " << yCoord2 << index;
            if (qAbs(xCoord2 - xCoord1) < 30 && qAbs(yCoord2 - yCoord1) < 30)
            {
                // Получаем новые координаты для перемещения пазлинки
                QPointF newPosition(xCoord1, yCoord1); // Предположим, что xCoord и yCoord - новые координаты

                // Перемещаем пазлинку на новые координаты
                selectedItem->setPos(newPosition);

                correctPartsSet.insert(index);
                // Проверяем, все ли части пазла на своих местах
                if (correctPartsSet.size() == 6) {
                    // Если да, выводим уведомление о том, что пазл собран
                    QMessageBox::information(this, "Поздравляем!", "Пазл собран!");
                    // Очищаем набор для возможности сбора пазла заново
                    correctPartsSet.clear();
                }
            }
        }
    }

    return false;
}

void HardPuzzles::on_pushButton_2_clicked()
{
    ui->label->hide();
    ui->label_4->hide();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->textEdit->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();

    // Удаление всего текущего контента со сцены
    scene->clear();

    imageParts.clear();
    // Очистка индексов и корректных частей
    indexes.clear();
    correctPartsSet.clear();

    dop++;
    if (dop < 7) on_pushButton_clicked();
    else {
        ui->pushButton_2->hide();
        ui->pushButton->hide();
        ui->pushButton_3->hide();
        ui->label->hide();
        ui->pushButton_6->show();
        ui->label_2->show();
    }
}


void HardPuzzles::on_pushButton_5_clicked()
{
    close();
}


void HardPuzzles::on_pushButton_4_clicked()
{
    PuzzleThemes *puzzleThemes = new PuzzleThemes();
    puzzleThemes->show();
    this->hide();
}


void HardPuzzles::on_pushButton_3_clicked()
{
    ui->label_4->show();
    ui->textEdit->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();

    num1 = rand() % 15 + 1;
    num2 = rand() % 15 + 1;
    num3 = rand() % 15 + 1;
    num4 = rand() % 15 + 1;
    num5 = rand() % 15 + 1;
    num6 = rand() % 15 + 1;
    num7 = rand() % 15 + 1;
    num8 = rand() % 15 + 1;
    num9 = rand() % 15 + 1;

    answer = (num1 * num5 * num9) + (num3 * num4 * num8) + (num2 * num6 * num7) - (num3 * num5 * num7) - (num1 * num6 * num8) - (num9 * num2 * num4);

    QString str1 = QString::number(num1) + " " + QString::number(num2) + " " + QString::number(num3);
    QString str2 = QString::number(num4) + " " + QString::number(num5) + " " + QString::number(num6);
    QString str3 = QString::number(num7) + " " + QString::number(num8) + " " + QString::number(num9);
    QString answ = str1 + "\n" + str2 + "\n" + str3;
    ui->label_5->setText(answ);
}


void HardPuzzles::on_pushButton_6_clicked()
{
    MainWindow *screen = new MainWindow();
    screen->show();
    this->hide();
}


void HardPuzzles::on_pushButton_7_clicked()
{
    HelpForPlayer *screen = new HelpForPlayer();
    screen->show();
}


void HardPuzzles::on_pushButton_9_clicked()
{
    ui->label->show();
    // Загрузка изображения в QLabel
    QPixmap pixmap(filename);
    if (pixmap.isNull()) {
        qDebug() << "Ошибка загрузки изображения";
        return;
    }
    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents(true);
}


void HardPuzzles::on_pushButton_8_clicked()
{
    QString text = ui->textEdit->toPlainText();
    bool ok;
    int number = text.toInt(&ok);
    if (answer == number) {
        ui->label_6->setText("ВЕРНО!");
        ui->pushButton_9->show();
    }
    else {
        ui->label_6->setText("НЕВЕРНО!");
    }
}

