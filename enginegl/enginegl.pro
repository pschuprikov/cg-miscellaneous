#-------------------------------------------------
#
# Project created by QtCreator 2012-09-02T23:40:07
#
#-------------------------------------------------

QT       -= core gui

TARGET = enginegl
TEMPLATE = lib

INCLUDEPATH += include

HEADERS += \
    include/common_interfaces.h \
    include/engine.h \
    include/enginegl.h \
    include/savers_n_setters.h \
    engine/shaders.h

SOURCES += \
    engine/engine.cpp \
    engine/shaders.cpp \
    utils/savers_n_setters.cpp

include.files = include/*.h
include.path = $$PREFIX/include

target.path = $$PREFIX/lib
INSTALLS += target include
