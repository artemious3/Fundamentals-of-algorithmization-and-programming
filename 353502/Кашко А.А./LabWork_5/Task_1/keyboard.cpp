#include "keyboard.h"

Keyboard::Keyboard() : curLang(ru) {
    deleteButton = new Button("<--", BIG_BUTTON_LENGTH);
    capsButton = new Button("caps", BIG_BUTTON_LENGTH);
    enterButton = new Button("enter", BIG_BUTTON_LENGTH);
    shiftButton = new Button("shift", BIG_BUTTON_LENGTH);
    spaceButton = new Button("space", BIG_BUTTON_LENGTH);

    specialButtonMap[Qt::Key_CapsLock] =
        capsButton;  // Добавляем caps в карту соответствия
    specialButtonMap[Qt::Key_Return] = enterButton;
    specialButtonMap[Qt::Key_Shift] = shiftButton;
    specialButtonMap[Qt::Key_Backspace] = deleteButton;
    specialButtonMap[Qt::Key_Space] = spaceButton;

    languages.append("ё1234567890-=йцукенгшщзхъфывапролджэячсмитьбю\\.");
    languages.append("ё1234567890-=йцукенгшўзх\'\\фывапролджэячсмітьбю.");
    languages.append("ذ&é'(-è_çà)=شسيبلاتنمكطئءؤرلالاىةووزظ1234567890");
    languages.append("^1234567890ß´qwertzuiopü+#asdfghjklöäyxcvbnm,.-");
    languages.append("`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./");
    languages.append(";1234567890-=/'קראטוןםפ][\\שדגכעיחלךף,זסבהנמצתץ.");
    languages.append("`1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./\\");
}

void Keyboard::init(Language lang) {

    curLang = lang;
    int row = 0;
    int column = 0;

    QList<Button*> tempButtons;

    foreach (QChar simb, languages[lang]) {
        Button* but = new Button(simb, BUTTON_LENGTH);
        tempButtons.append(but);
        buttonMap[simb] = but;  // Добавляем в карту соответствия
    }

    // Добавляем специальные кнопки в нужные позиции

    tempButtons.insert(DELETE_PLACE, deleteButton);
    tempButtons.insert(CAPS_PLACE, capsButton);
    tempButtons.insert(ENTER_PLACE, enterButton);
    tempButtons.insert(SHIFT_PLACE, shiftButton);
    tempButtons.append(spaceButton);

    // Устанавливаем позиции для всех кнопок
    for (int i = 0; i < tempButtons.length(); ++i) {
        int len = tempButtons[i]->getLength();

        tempButtons[i]->setPos(column * (len + SPACING),
                               row * (BUTTON_WIDTH + SPACING));

        column++;
        if (column >= 13) {
            column = 0;
            row++;
        }
        addItem(tempButtons[i]);
    }
    buttons = tempButtons;
}

void Keyboard::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    QChar keyChar = event->text().isEmpty() ? QChar() : event->text().at(0);
    Button* button = nullptr;

    if (buttonMap.contains(keyChar)) {
        button = buttonMap[keyChar];

    } else if (specialButtonMap.contains(key)) {
        button = specialButtonMap[key];
    }

    if (button == capsButton || button == shiftButton) {
        button->highlight();
        return;
    }
    if (button) {
        button->highlight();
    }
    emit keyPressed(keyChar);
}

void Keyboard::keyReleaseEvent(QKeyEvent* event) {
    int key = event->key();
    QChar keyChar =
        event->text().isEmpty() ? QChar() : event->text().at(0).toLower();
    Button* button = nullptr;

    if (buttonMap.contains(keyChar)) {
        button = buttonMap[keyChar];
    } else if (specialButtonMap.contains(key)) {
        button = specialButtonMap[key];
    }

    if (button) {
        button->resetColor();
    }
}

Keyboard::~Keyboard() {
    delete deleteButton;
    delete shiftButton;
    delete capsButton;
    delete enterButton;
    delete spaceButton;
    deleteButton = nullptr;
    shiftButton = nullptr;
    capsButton = nullptr;
    enterButton = nullptr;
    spaceButton = nullptr;
}

void Keyboard::removeKeyboard() {
    for (auto but : buttons) {
        removeItem(but);
        delete but;
    }
}
