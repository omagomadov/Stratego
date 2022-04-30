TEMPLATE = app
CONFIG += console #c++17
CONFIG -= app_bundle

include("../config.pri")

SOURCES += \
        gui.cpp \
        main.cpp \
        qboard.cpp \
        qchoosewindow.cpp \
        qfilewindow.cpp \
        qmanualwindow.cpp \
        qpawn.cpp \
        qsquare.cpp \
        qstartwindow.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../model/release/ -lmodel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../model/debug/ -lmodel
else:unix:!macx: LIBS += -L$$OUT_PWD/../model/ -lmodel

INCLUDEPATH += $$PWD/../model
DEPENDPATH += $$PWD/../model

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/release/libmodel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/debug/libmodel.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/release/model.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../model/debug/model.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../model/libmodel.a

HEADERS += \
    gui.h \
    qboard.h \
    qchoosewindow.h \
    qfilewindow.h \
    qmanualwindow.h \
    qpawn.h \
    qsquare.h \
    qstartwindow.h

QT += widgets

RESOURCES += \
    resource.qrc
