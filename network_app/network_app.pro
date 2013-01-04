#-------------------------------------------------
#
# Project created by QtCreator 2012-12-04T14:08:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = network_app
TEMPLATE = app


SOURCES += main.cpp\
        chat.cpp \
    msgclient.cpp \
    chname.cpp \
    msgencode.cpp

HEADERS  += chat.h \
    msgclient.h \
    chname.h \
    msgencode.h

FORMS    += chat.ui \
    chname.ui

CONFIG   += -static
