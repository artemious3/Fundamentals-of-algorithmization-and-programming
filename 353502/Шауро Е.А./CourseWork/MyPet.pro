QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    B_birditem.cpp \
    B_birdwind.cpp \
    B_pillaritem.cpp \
    B_scene.cpp \
    F_foodcatchwind.cpp \
    F_fruits.cpp \
    F_player.cpp \
    F_scene.cpp \
    M3_gemsitem.cpp \
    M3_match3wind.cpp \
    M3_scene.cpp \
    S_apple.cpp \
    S_scene.cpp \
    S_snake.cpp \
    S_snakewind.cpp \
    globals.cpp \
    infowindow.cpp \
    main.cpp \
    mainscene.cpp \
    mainwindow.cpp \
    pet.cpp

HEADERS += \
    B_birditem.h \
    B_birdwind.h \
    B_const.h \
    B_pillaritem.h \
    B_scene.h \
    F_const.h \
    F_foodcatchwind.h \
    F_fruits.h \
    F_player.h \
    F_scene.h \
    M3 _gemsitem.h \
    M3_const.h \
    M3_gemsitem.h \
    M3_match3wind.h \
    M3_scene.h \
    S_apple.h \
    S_const.h \
    S_scene.h \
    S_snake.h \
    S_snakewind.h \
    globals.h \
    infowindow.h \
    mainConst.h \
    mainscene.h \
    mainwindow.h \
    pet.h

FORMS += \
    birdwind.ui \
    foodcatchwind.ui \
    infowindow.ui \
    mainwindow.ui \
    match3wind.ui \
    snakewind.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  res.qrc

DISTFILES += \
  Images/mainGO.png
