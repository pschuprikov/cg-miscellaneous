TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/home/pasha/qtprojects/cg-miscellaneous/glengine-build-Desktop-Debug
LIBS += -lGL -lglut -lGLU -lglengine

INCLUDEPATH += /home/pasha/repos/cg-miscellaneous/glengine/include


SOURCES += main.cpp

