TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    server.h

DISTFILES += \
    backup
