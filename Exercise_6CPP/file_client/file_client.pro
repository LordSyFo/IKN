TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    client_socket.cpp \
    ../file_server/bsocket.cpp \
    ../file_server/filehandler.cpp \
    ../file_server/message.cpp

unix:!macx: LIBS += -liknlib

HEADERS += \
    client_socket.h \
    ../file_server/bsocket.h \
    ../file_server/filehandler.h \
    ../file_server/message.h
