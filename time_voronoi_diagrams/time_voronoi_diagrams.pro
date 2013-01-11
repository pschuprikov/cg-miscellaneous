### eqmake4 was here ###
TEMPLATE = app

CONFIG += console debug
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    core/input_manager.cpp \
    core/input_infos.cpp \
    core/render_manager.cpp \
    core/logic_processor.cpp \
    core/core.cpp \
    logics/line_builder.cpp \
    renderers/line_renderer.cpp \
    logics/main_logic.cpp \
    logics/lines_builder.cpp \
    logics/voronoi_diagram.cpp \
    logics/gpgpu_vd/lines_prepare.cpp \
    logics/gpgpu_vd/rasterizer.cpp \
    logics/gpgpu_vd/voronoi_texdraw.cpp \
    logics/gpgpu_vd/jump_flood.cpp

PRECOMPILED_HEADER = stdafx.h

LIBS += -L/home/pasha/qtprojects/glengine/debug
LIBS += -lGL -lglut -lGLU -lglengine

INCLUDEPATH += /home/pasha/repos/cg-miscellaneous/glengine/include

HEADERS += \
    renderable.h \
    input_listener.h \
    stdafx.h \
    logics.h \
    io_interfaces.h \
    core/input_manager.h \
    core/input_infos.h \
    core/render_manager.h \
    core/core.h \
    core/logic_processor.h \
    logics/main_logic.h \
    logics/line_builder.h \
    logics/lines_builder.h \
    logics/main_logic_fwd.h \
    renderers/line_renderer.h \
    logics/invalidator.h \
    logics/voronoi_diagram.h \
    logics/gpgpu_vd/lines_prepare.h \
    logics/gpgpu_vd/rasterizer.h \
    logics/gpgpu_vd/voronoi_texdraw.h \
    logics/gpgpu_vd/jump_flood.h

OTHER_FILES += \
    shaders/line/vs.glsl \
    shaders/line/fs.glsl \
    shaders/rasterizer/vs.glsl \
    shaders/rasterizer/fs.glsl \
    shaders/rasterizer/gs.glsl \
    shaders/texdraw/vs.glsl \
    shaders/texdraw/fs.glsl \
    shaders/jump_flood/cs.glsl
