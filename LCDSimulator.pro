TEMPLATE = app
CONFIG += c++11 no_keywords console

QT += qml quick qml
CONFIG += c++11

SOURCES += main.cpp  \
    ApplicationController.cpp \
    Snake.cpp \
    SpaceImpact.cpp \
    Tank.cpp \
    VideoDisplay/I420Render.cpp \
    VideoDisplay/VideoRender.cpp

RESOURCES += qml.qrc

HEADERS += \
    ApplicationController.h \
    Snake.h \
    SpaceImpact.h \
    Tank.h \
    VideoDisplay/I420Render.h \
    VideoDisplay/VideoRender.h
