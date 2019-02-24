TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    client_socket.cpp \
    ../file_server/bsocket.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    client_socket.h \
    ../file_server/bsocket.h
