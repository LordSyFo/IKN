TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../file_server/Serversocket.cpp \
    ../file_server/Filehandler.cpp \
    ../file_server/Message.cpp \
    Clientsocket.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    ../file_server/Serversocket.h \
    ../file_server/Filehandler.h \
    ../file_server/Message.h \
    Clientsocket.h
