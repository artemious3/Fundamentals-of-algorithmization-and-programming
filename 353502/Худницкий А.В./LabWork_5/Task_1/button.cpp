#include "button.h"

Button::Button(QString symb, int len, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), length(len), symbol(symb) {

    setRect(0, 0, len, BUTTON_WIDTH);
    setBrush(QBrush(Qt::lightGray));

    textItem = new QGraphicsTextItem(symbol, this);

    int xPos = rect().width() / 2 - textItem->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - textItem->boundingRect().height() / 2;
    textItem->setPos(xPos, yPos);
    setBrush(QBrush(Qt::white));
}

void Button::highlight() {
    setBrush(QBrush(Qt:: darkGray));
    update();
}

int Button::getLength() const {
    return length;
}

QString Button::getSymbol() const
{
    return symbol;
}

void Button::resetColor() {
    setBrush(QBrush(Qt::white));
}
