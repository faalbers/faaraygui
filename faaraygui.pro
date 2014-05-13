#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T23:08:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = faaraygui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderwidget.cpp

HEADERS  += mainwindow.h \
    renderwidget.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../inst/gfa/lib/ -lgfa

INCLUDEPATH += $$PWD/../inst/gfa/include
DEPENDPATH += $$PWD/../inst/gfa/include
