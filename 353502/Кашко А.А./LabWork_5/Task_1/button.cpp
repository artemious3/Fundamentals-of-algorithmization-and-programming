#include "button.h"

Button::Button(QString symb, int len, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), length(len), symbol(symb) {

    setRect(0, 0, len, BUTTON_WIDTH); // Примерный размер кнопки, можно изменить
    setBrush(QBrush(Qt::lightGray));

    // Создаем текстовый элемент для символа на кнопке
    textItem = new QGraphicsTextItem(symbol, this);

    // Центрируем текст внутри кнопки
    int xPos = rect().width() / 2 - textItem->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - textItem->boundingRect().height() / 2;
    textItem->setPos(xPos, yPos);
    setBrush(QBrush(Qt::white));
}

int Button::getLength() const
{
    return length;
}


void Button::highlight() {
    setBrush(QBrush(Qt::yellow));
    update();
}

QString Button::getSymbol() const
{
    return symbol;
}

void Button::resetColor() {
    setBrush(QBrush(Qt::white));
}
