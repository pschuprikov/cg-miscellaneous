#-------------------------------------------------
#
# Project created by QtCreator 2012-09-01T16:36:53
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /home/pasha/repos/deploy/include
LIBS += -L/home/pasha/repos/deploy/lib -lenginegl

TARGET = voronoi_diagrams
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    opengl_test_widget.cpp

HEADERS  += mainwindow.h \
    opengl_test_widget.h

FORMS    += mainwindow.ui
