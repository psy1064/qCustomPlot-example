#-------------------------------------------------
#
# Project created by QtCreator 2021-02-17T14:44:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = qcustomplot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h

FORMS    += mainwindow.ui
