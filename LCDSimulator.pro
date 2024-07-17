TEMPLATE = app
CONFIG += c++11 no_keywords console

QT += qml quick qml
CONFIG += c++11

RESOURCES += qml.qrc

CONFIG += game
SOURCES += main.cpp  \
    ApplicationController.cpp \
    VideoDisplay/I420Render.cpp \
    VideoDisplay/VideoRender.cpp \
    Game/GameItem.cpp \
    ApplicationSim.cpp \
    MainProcess.cpp \
    LCDLibrary.cpp


HEADERS += \
    ApplicationController.h \
    VideoDisplay/I420Render.h \
    VideoDisplay/VideoRender.h \
    Game/GameItem.h \
    ApplicationSim.h \
    MainProcess.h \
    LCDLibrary.h

game {
SOURCES += \
    Game/Snake.cpp \
    Game/SpaceImpact.cpp \
    Game/Tank.cpp

HEADERS += \
    Game/Snake.h \
    Game/SpaceImpact.h \
    Game/Tank.h
}
