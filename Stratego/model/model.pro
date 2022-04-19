# QT -= gui

TEMPLATE = lib
# DEFINES += MODEL_LIBRARY

#CONFIG += c++11
CONFIG += staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../config.pri)

SOURCES += \
    Board.cpp \
    Game.cpp \
    Pawn.cpp \
    Position.cpp

HEADERS += \
    Board.h \
    Color.h \
    Direction.h \
    Game.h \
    Pawn.h \
    Position.h \
    Role.h \
    State.h \
    observable.h \
    observer.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
