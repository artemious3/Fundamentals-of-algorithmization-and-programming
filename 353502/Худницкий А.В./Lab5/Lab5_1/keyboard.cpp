#include "keyboard.h"

Keyboard::Keyboard() : curLang(ru) {
    deleteButton = new Button("Backspace", BIG_BUTTON_LENGTH);
    capsButton = new Button("Caps", BIG_BUTTON_LENGTH);
    enterButton = new Button("Enter", BIG_BUTTON_LENGTH);
    shiftButton = new Button("Shift", BIG_BUTTON_LENGTH);
    spaceButton = new Button("Space", BIG_BUTTON_LENGTH);

    specialButtonMap[Qt::Key_CapsLock] = capsButton;
    specialButtonMap[Qt::Key_Return] = enterButton;
    specialButtonMap[Qt::Key_Shift] = shiftButton;
    specialButtonMap[Qt::Key_Backspace] = deleteButton;
    specialButtonMap[Qt::Key_Space] = spaceButton;

    languages.append("ё1234567890-=йцукенгшщзхъфывапролджэячсмитьбю\\."); //русский
    languages.append("ё1234567890-=йцукенгшўзх\'\\фывапролджэячсмітьбю.");//белорусский
    languages.append("ذ&é'(-è_çà)=شسيبلاتنمكطئءؤرلالاىةووزظ1234567890");//иврит
    languages.append("ā1234567890-=qīwērtūyīuīopāsdfghjklzxcvbnm,.");//китайский
    languages.append("`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./");//английский
    languages.append(";1234567890-=/'קראטוןםפ][\\שדגכעיחלךף,זסבהנמצתץ.");//арабский
    languages.append("`1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./\\");//немецкий
    languages.append("é1234567890-=qswdfghjklmù*azertyuiop^$cvbn,;:!\\"); //французский

}
Keyboard::~Keyboard() {
    delete deleteButton;
    deleteButton = nullptr;

    delete shiftButton;
    shiftButton = nullptr;

    delete capsButton;
    capsButton = nullptr;

    delete enterButton;
    enterButton = nullptr;

    delete spaceButton;
    spaceButton = nullptr;
}

void Keyboard::init(Language language) {

    curLang = language;
    int row = 0;
    int column = 0;

    QList<Button*> tempButtons;

    foreach (QChar simb, languages[language]) {
        Button* but = new Button(simb, BUTTON_LENGTH);
        tempButtons.append(but);
        buttonMap[simb] = but;
    }

    tempButtons.insert(DELETE_PLACE, deleteButton);
    tempButtons.insert(CAPS_PLACE, capsButton);
    tempButtons.insert(ENTER_PLACE, enterButton);
    tempButtons.insert(SHIFT_PLACE, shiftButton);
    tempButtons.insert(SPACE_PLACE, spaceButton);

    for (int i = 0; i < tempButtons.length(); ++i) {
        int len = tempButtons[i]->getLength();

        tempButtons[i]->setPos(column * (len + SPACING), row * (BUTTON_WIDTH + SPACING));
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

    QChar keyChar = event->text().isEmpty() ? QChar() : event->text().at(0).toLower();
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

void Keyboard::removeKeyboard() {
    for (auto but : buttons) {
        removeItem(but);
        delete but;
    }
}
