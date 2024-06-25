#include "M3_gemsitem.h"

GemsItem::GemsItem() : isBackground(false) {
  QPixmap pixmap(":/Images/gems.png");
  int gemWidth = pixmap.width() / GEMS_COUNT;
  int gemHeight = pixmap.height();

  // Обрезка изображения для выбранного типа гема
  type = QRandomGenerator::global()->bounded(ROW_COUNT - 1);
  QPixmap gemPixmap = pixmap.copy(gemWidth * type, 0, gemWidth, gemHeight);
  setPixmap(gemPixmap.scaled(QSize(SIZE, SIZE), Qt::KeepAspectRatio));
}

int GemsItem::getpRow() const
{
    return pRow;
}

void GemsItem::setpRow(int value)
{
    pRow = value;
}

int GemsItem::getpCol() const
{
    return pCol;
}

void GemsItem::setpCol(int value)
{
    pCol = value;
}

int GemsItem::getType() const
{
    return type;
}

void GemsItem::setType(int value)
{
    type = value;
}

bool GemsItem::getIsBackground() const
{
    return isBackground;
}
