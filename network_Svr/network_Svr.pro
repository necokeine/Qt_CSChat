#-------------------------------------------------
#
# Project created by QtCreator 2012-12-11T14:35:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = network_Svr
TEMPLATE = app


SOURCES += main.cpp\
        tcpserver.cpp \
    megserver.cpp \
    msgclient.cpp

HEADERS  += tcpserver.h \
    megserver.h \
    msgclient.h

FORMS    += tcpserver.ui
