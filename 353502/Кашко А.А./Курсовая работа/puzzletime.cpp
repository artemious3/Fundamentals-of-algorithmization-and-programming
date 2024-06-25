#include "puzzletime.h"
#include "ui_puzzletime.h"

PuzzleTime::PuzzleTime(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PuzzleTime)
{
    ui->setupUi(this);

    scene = new GraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->installEventFilter(this);

    timer = new QTimer(this);
    time = new QTime(0, 0);

    connect(timer, &QTimer::timeout, this, &PuzzleTime::updateTimer);
}

PuzzleTime::~PuzzleTime()
{
    delete ui;
    delete timer;
    delete time;
}

void PuzzleTime::updateTimer()
{
    *time = time->addSecs(1);
    ui->label->setText(time->toString("mm:ss"));
}

void PuzzleTime::on_closeButton_clicked()
{
    close();
}


void PuzzleTime::on_pushButton_3_clicked()
{
    PuzzleThemes *puzzleThemes = new PuzzleThemes();
    puzzleThemes->show();
    this->hide();
}

QList<QImage> PuzzleTime::splitImage(const QString& filename) {
    // Загрузка изображения из файла
    QImage originalImage(filename);
    QSize targetSize(450, 300);
    originalImage = originalImage.scaled(targetSize, Qt::KeepAspectRatio);

    if(originalImage.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить изображение";
        return imageParts;
    }

    // Определение размеров каждой части
    int partWidth = originalImage.width() / 4;
    int partHeight = originalImage.height() / 3;

    // Разбиение изображения на 12 равных частей
    for(int y = 0; y < 3; ++y) {
        for(int x = 0; x < 4; ++x) {
            QRect rect(x * partWidth, y * partHeight, partWidth, partHeight);
            QImage part = originalImage.copy(rect);
            imageParts.append(part);
        }
    }

    for (int i = 0; i < imageParts.size(); ++i) {
        int xPos = (i % 4) * imageParts[i].width();
        int yPos = (i / 4) * imageParts[i].height();
        partPositions.insert(i, QPointF(xPos, yPos));
    }

    return imageParts;
}

void PuzzleTime::on_startButton_clicked()
{
    ui->startButton->hide();

    // Загрузка и разделение изображения
    filename = "/home/nastya/coursework_puzzles/image_sea/sea8";
    imageParts = splitImage(filename);

    // Отображение всех частей изображения на графической сцене
    for (int i = 0; i < imageParts.size(); ++i) {
        // Создание элемента QGraphicsPixmapItem для текущей части изображения
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(imageParts[i]));

        pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, true);

        // Расположение текущей части на сцене (расположение может быть настроено по вашему выбору)
        int xPos = (i % 4) * imageParts[i].width(); // Размещение частей по горизонтали (в этом примере 3 части в ряд)
        int yPos = (i / 4) * imageParts[i].height(); // Размещение частей по вертикали

        pixmapItem->setPos(xPos, yPos); // Установка позиции элемента на сцене
        // Добавление элемента на графическую сцену
        scene->addItem(pixmapItem);
        indexes[pixmapItem] = i;
        QGraphicsRectItem *outlineRect = new QGraphicsRectItem(xPos, yPos, imageParts[i].width(), imageParts[i].height());
        outlineRect->setPen(QPen(Qt::black)); // Установка цвета контура
        scene->addItem(outlineRect);
    }

    swapImageParts();

    // Start the timer
    time->setHMS(0, 0, 0);
    timer->start(1000);  // Update every second
}

void PuzzleTime::swapImageParts() {
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
}

bool PuzzleTime::eventFilter(QObject *obj, QEvent *ev) {
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
                if (correctPartsSet.size() == 12) {
                    // Если да, выводим уведомление о том, что пазл собран
                    QMessageBox::information(this, "Поздравляем!", "Пазл собран!");
                    // Останавливаем таймер
                    timer->stop();
                    // Очищаем набор для возможности сбора пазла заново
                    correctPartsSet.clear();
                }
            }
        }
    }

    return false;
}

