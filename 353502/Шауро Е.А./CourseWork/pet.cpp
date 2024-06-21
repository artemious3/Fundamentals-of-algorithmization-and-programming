#include "pet.h"

Pet::Pet()
{
    setPixmap(QPixmap(":/Images/standart_cat.png").scaled(QSize(PET_SIZE_X, PET_SIZE_Y)));
    setPos(CENTRAL);
}

void Pet::updateCatIcon()
{
    QPixmap picture;
    int x = PET_SIZE_X, y = PET_SIZE_Y, x_pos = CENTRAL.x(), y_pos = CENTRAL.y();

    switch (mood) {
    case Standart:
        picture = QPixmap(":/Images/standart_cat.png");

        break;
    case Cool:
        picture = QPixmap(":/Images/cool_cat.png");
        std::swap(x, y);
        x+=70;
        y_pos -= 200;
        break;
    case Angry:
        picture = QPixmap(":/Images/angry_cat.png");
        std::swap(x, y);
        x+=70;
        y_pos -= 200;
        break;
    case GoAway:
        picture = QPixmap(":/Images/cat_go_away.png");
        y+=50;
        break;
    }

    setPixmap(picture.scaled(QSize(x, y)));
    setPos(x_pos, y_pos);
}

CatMood Pet::getMood() const
{
    return mood;
}

void Pet::setMood(const CatMood &value)
{
    mood = value;
}
