### eqmake4 was here ###
TEMPLATE = app

CONFIG += console debug
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS = -Wno-reorder -std=c++0x -pg

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
    logics/gpgpu_vd/jump_flood.cpp \
    logics/lines_loader.cpp \
    renderers/primitive_renderer.cpp \
    logics/gpgpu_vd/cleaner.cpp \
    logics/gpgpu_vd/naive.cpp

PRECOMPILED_HEADER = stdafx.h

LIBS += -L/home/pasha/qtprojects/glengine/debug
LIBS += -lglut -lGLU -lglengine

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
    logics/gpgpu_vd/jump_flood.h \
    logics/lines_loader.h \
    lines_common.h \
    logics/gpgpu_vd/naive.h \
    renderers/primitive_renderer.h \
    logics/gpgpu_vd/cleaner.h

LINES_DATA_FILE = lines.dat

SHADER_FILES = \
    shaders/jump_flood/jump_flood_cs.glsl \
    shaders/line/line_fs.glsl \
    shaders/line/line_vs.glsl \
    shaders/rasterizer/rasterizer_fs.glsl \
    shaders/rasterizer/rasterizer_gs.glsl \
    shaders/rasterizer/rasterizer_vs.glsl \
    shaders/texdraw/texdraw_fs.glsl \
    shaders/texdraw/texdraw_vs.glsl \
    shaders/naive/naive_cs.glsl \
    shaders/cleaner/cleaner_cs.glsl

OTHER_FILES += $$SHADER_FILES $$LINES_DATA_FILE

shaders.path=$$OUT_PWD/shaders/
shaders.files += $$SHADER_FILES

lines_data.path = $$OUT_PWD/
lines_data.files += $$LINES_DATA_FILE

INSTALLS += shaders lines_data
