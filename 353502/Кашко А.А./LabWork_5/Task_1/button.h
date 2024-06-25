#ifndef BUTTON_H
#define BUTTON_H

#include <QString>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsTextItem>
#include "const.h"

class Button : public QGraphicsRectItem
{
public:
    explicit Button(QString symb, int len, QGraphicsItem *parent = nullptr);
    int getLength() const;
    QString getSymbol() const;
    void resetColor();
    void highlight();

private:

    QGraphicsTextItem* textItem;
    int length;
    QString symbol;
};

#endif // BUTTON_H
