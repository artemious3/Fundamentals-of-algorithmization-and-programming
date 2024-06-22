#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "button.h"
#include "const.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTextEdit>

class Keyboard : public QGraphicsScene {
    Q_OBJECT
public:
    Keyboard();
    ~Keyboard() override;

    void init(Language language);
    void removeKeyboard();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

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
