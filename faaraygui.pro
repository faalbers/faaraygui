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
    renderwidget.cpp \
    guiviewplane.cpp \
    renderthread.cpp

HEADERS  += mainwindow.h \
    renderwidget.h \
    guiviewplane.h \
    renderthread.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

unix|win32: LIBS += -L$$PWD/../inst/lib/ -lgfa
unix|win32: LIBS += -L$$PWD/../inst/lib/ -lfaaray

INCLUDEPATH += $$PWD/../inst/include
DEPENDPATH += $$PWD/../inst/include

