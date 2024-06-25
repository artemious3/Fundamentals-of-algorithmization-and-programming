#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTextEdit>
#include "button.h"
#include "const.h"

class Keyboard : public QGraphicsScene {
    Q_OBJECT
public:
    Keyboard();
    void init(Language lang);
    void removeKeyboard();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    ~Keyboard() override;

signals:
    void keyPressed(QChar keyChar);

private:
    QList<QString> languages;
    QList<Button*> buttons;
    QMap<QChar, Button*> buttonMap;
    QMap<int, Button*> specialButtonMap;
    Language curLang;
    Button* deleteButton;
    Button* shiftButton;
    Button* capsButton;
    Button* enterButton;
    Button* spaceButton;
};

#endif  // KEYBOARD_H
