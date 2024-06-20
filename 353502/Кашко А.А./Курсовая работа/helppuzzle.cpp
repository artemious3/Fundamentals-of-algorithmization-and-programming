#include "helppuzzle.h"
#include "ui_helppuzzle.h"

HelpPuzzle::HelpPuzzle(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpPuzzle)
{
    ui->setupUi(this);

    ui->button_NextPuzzle->hide();
    ui->button_HelpUser->hide();
    ui->button_NextLevelHard->hide();
    ui->label_2->hide();
    ui->label_5->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->textEdit->hide();

    ui->button_StartGame->setStyleSheet("background-color: pink;");
    ui->button_NextPuzzle->setStyleSheet("background-color: pink;");
    ui->button_ClosePlay->setStyleSheet("background-color: pink;");
    ui->button_BackHomeScreen->setStyleSheet("background-color: pink;");
    ui->button_HelpUser->setStyleSheet("background-color: pink;");
    ui->button_NextLevelHard->setStyleSheet("background-color: pink;");

    scene = new GraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->installEventFilter(this);

    // Инициализируем QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HelpPuzzle::swapImageParts);
    // Запускаем таймер с интервалом 5 секунд
    timer->start(5000);
}

void HelpPuzzle::themesPuzzle(int choise)
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

// Функция для загрузки изображения из файла и разбиения его на 6 равных кусочков
QList<QImage> HelpPuzzle::splitImage(const QString& filename) {
    imageParts;

    // Загрузка изображения из файла
    QImage originalImage(filename);
    QSize targetSize(450, 300);
    originalImage = originalImage.scaled(targetSize, Qt::KeepAspectRatio);

    if(originalImage.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить изображение";
        return imageParts;
    }

    // Определение размеров каждой части
    int partWidth = originalImage.width() / 3;
    int partHeight = originalImage.height() / 2;

    // Разбиение изображения на 6 равных частей
    for(int y = 0; y < 2; ++y) {
        for(int x = 0; x < 3; ++x) {
            QRect rect(x * partWidth, y * partHeight, partWidth, partHeight);
            QImage part = originalImage.copy(rect);
            imageParts.append(part);
        }
    }

    for (int i = 0; i < imageParts.size(); ++i) {
        int xPos = (i % 3) * imageParts[i].width();
        int yPos = (i / 3) * imageParts[i].height();
        partPositions.insert(i, QPointF(xPos, yPos));
    }

    return imageParts;
}

HelpPuzzle::~HelpPuzzle()
{
    delete ui;
}

void HelpPuzzle::on_button_StartGame_clicked()
{
    ui->button_StartGame->hide();
    ui->button_NextPuzzle->show();
    ui->button_HelpUser->show();

    switch(themes) {
    case 0:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_sea/sea1";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_sea/sea2";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_sea/sea3";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_sea/sea4";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_sea/sea5";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_sea/sea6";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_sea/sea7";
        break;
    case 1:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_animal/animal1";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_animal/animal2";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_animal/animal3";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_animal/animal4";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_animal/animal5";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_animal/animal6";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_animal/animal7";
        break;
    case 2:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_nature/nature1";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_nature/nature2";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_nature/nature3";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_nature/nature4";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_nature/nature5";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_nature/nature6";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_nature/nature7";
        break;
    case 3:
        if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_game/game1";
        else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_game/game2";
        else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_game/game3";
        else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_game/game4";
        else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_game/game5";
        else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_game/game6";
        else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_game/game7";
        break;
    case 4:
       if(dop == 0) filename = "/home/nastya/coursework_puzzles/image_good/good1";
       else if(dop == 1) filename = "/home/nastya/coursework_puzzles/image_good/good2";
       else if(dop == 2) filename = "/home/nastya/coursework_puzzles/image_good/good3";
       else if(dop == 3) filename = "/home/nastya/coursework_puzzles/image_good/good4";
       else if(dop == 4) filename = "/home/nastya/coursework_puzzles/image_good/good5";
       else if(dop == 5) filename = "/home/nastya/coursework_puzzles/image_good/good6";
       else if(dop == 6) filename = "/home/nastya/coursework_puzzles/image_good/good7";
       break;
    default:
       break;
    }
    imageParts = splitImage(filename);

    // Отображение всех частей изображения на графической сцене
    for (int i = 0; i < imageParts.size(); ++i) {
        // Создание элемента QGraphicsPixmapItem для текущей части изображения
        pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(imageParts[i]));

        pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, true);

        // Расположение текущей части на сцене (расположение может быть настроено по вашему выбору)
        int xPos = (i % 3) * imageParts[i].width(); // Размещение частей по горизонтали (в этом примере 3 части в ряд)
        int yPos = (i / 3) * imageParts[i].height(); // Размещение частей по вертикали

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

void HelpPuzzle::swapImageParts() {
    // Получаем список индексов частей
    QList<int> partIndexes = partPositions.keys();

    // Перемешиваем индексы
    std::shuffle(partIndexes.begin(), partIndexes.end(), std::mt19937(std::random_device()()));

    // Меняем позиции между собой
    for (int i = 0; i < partIndexes.size(); ++i)
    {
        QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem *>(scene->items().at(partIndexes[i]));
        if (item) {
            // Получаем новые случайные координаты для текущей части
            qreal newX = rand() % static_cast<int>(scene->width() - item->boundingRect().width());
            qreal newY = rand() % static_cast<int>(scene->height() - item->boundingRect().height());
            QPointF newPos(newX, newY);

            // Устанавливаем новые координаты для текущей части
            item->setPos(newPos);
        }
    }

    // Остановка таймера после первой смены позиций
    timer->stop();
}

bool HelpPuzzle::eventFilter(QObject *obj, QEvent *ev) {
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

void HelpPuzzle::on_button_ClosePlay_clicked()
{
    close();
}

void HelpPuzzle::on_button_BackHomeScreen_clicked()
{
    PuzzleThemes *puzzleThemes = new PuzzleThemes();
    puzzleThemes->show();
    this->hide();
}

void HelpPuzzle::on_button_NextPuzzle_clicked()
{
    // Удаление всего текущего контента со сцены
    scene->clear();

    imageParts.clear();
    // Очистка индексов и корректных частей
    indexes.clear();
    correctPartsSet.clear();

    ui->label->clear();
    ui->label_4->clear();
    ui->label_6->clear();
    ui->label_5->hide();
    ui->textEdit->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();

    dop++;
    if (dop < 7) on_button_StartGame_clicked();
    else {
        ui->button_NextPuzzle->hide();
        ui->button_StartGame->hide();
        ui->button_HelpUser->hide();
        ui->label->hide();
        ui->button_NextLevelHard->show();
        ui->label_2->show();
    }
}

void HelpPuzzle::on_button_HelpUser_clicked()
{
    ui->label_5->show();
    ui->textEdit->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();

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
    ui->label_4->setText(answ);
}


void HelpPuzzle::on_button_NextLevelHard_clicked()
{
    AveragePuzzles *puzzle = new AveragePuzzles();
    puzzle->show();
    this->hide();
}

void HelpPuzzle::on_pushButton_clicked()
{
    ui->pushButton->hide();

    // Загрузка изображения в QLabel
    QPixmap pixmap(filename);
    if (pixmap.isNull()) {
        qDebug() << "Ошибка загрузки изображения";
        return;
    }
    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents(true);
}


void HelpPuzzle::on_pushButton_2_clicked()
{
    QString text = ui->textEdit->toPlainText();
    bool ok;
    int number = text.toInt(&ok);
    if (answer == number) {
        ui->label_6->setText("ВЕРНО!");
        ui->pushButton->show();
    }
    else {
        ui->label_6->setText("НЕВЕРНО!");
    }
}

void HelpPuzzle::on_pushButton_3_clicked()
{
    HelpForPlayer *screen = new HelpForPlayer();
    screen->show();
}

