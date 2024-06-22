#ifndef BUTTON_H
#define BUTTON_H

#include "const.h"
#include <QString>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsTextItem>

class Button : public QGraphicsRectItem
{
public:
    explicit Button(QString symb, int len, QGraphicsItem *parent = nullptr);
    QString getSymbol() const;
    int getLength() const;

    void resetColor();
    void highlight();

private:
    QGraphicsTextItem* textItem;
    int length;
    QString symbol;
};

#endif // BUTTON_H
