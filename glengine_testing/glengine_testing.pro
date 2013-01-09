TEMPLATE = app
CONFIG += console debug
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/home/pasha/qtprojects/glengine/debug
LIBS += -lGL -lglut -lGLU -lglengine

INCLUDEPATH += /home/pasha/repos/cg-miscellaneous/glengine/include


SOURCES += main.cpp

OTHER_FILES += \
    vs.glsl \
    fs.glsl \
    gs.glsl \
    tex_draw_vs.glsl \
    tex_draw_fs.glsl

