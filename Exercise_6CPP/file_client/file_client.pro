TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../file_server/bsocket.cpp \
    ../file_server/filehandler.cpp \
    ../file_server/message.cpp \
    Clientsocket.cpp \
    ../file_server/Serversocket.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    ../file_server/bsocket.h \
    ../file_server/filehandler.h \
    ../file_server/message.h \
    Clientsocket.h \
    ../file_server/Serversocket.h
