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

unix:!macx: LIBS += -L$$PWD/../inst/lib/ -lgfa

INCLUDEPATH += $$PWD/../inst/include
DEPENDPATH += $$PWD/../inst/include
