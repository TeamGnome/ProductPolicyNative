#-------------------------------------------------
#
# Project created by QtCreator 2016-02-27T18:11:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProductPolicy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ppobject.cpp \
    pprecord.cpp

HEADERS  += mainwindow.h \
    ppobject.h \
    pprecord.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS += -std=c++11
