TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bsocket.cpp \
    filehandler.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    bsocket.h \
    filehandler.h

DISTFILES += \
    backup
