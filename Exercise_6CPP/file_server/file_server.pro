TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Serversocket.cpp \
    Message.cpp \
    Filehandler.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    Serversocket.h \
    Message.h \
    Filehandler.h

DISTFILES += \
    backup \
    ../../simpleFileCopy.txt
