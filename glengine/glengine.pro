QT -= core gui

QMAKE_CXXFLAGS = -Wno-reorder

TARGET = glengine
TEMPLATE = lib

SOURCES += \
    engine/queries.cpp \
    engine/query_object_manager.cpp \
    engine/engine.cpp \
    engine/buffers.cpp \
    engine/buffer_targets.cpp \
    engine/buffer_object_manager.cpp

LIBS += -lGLEW

INCLUDEPATH += include

HEADERS += \
    include/glequery.h \
    engine/engine.h \
    engine/query_object_manager.h \
    engine/queries.h \
    include/glengine.h \
    include/glequery_object_manager.h \
    engine/query_ptrs_storage.hpp \
    engine/query_ptrs_storage_fwd.hpp \
    include/glebuffer.h \
    include/glebuffer_object_manager.h \
    engine/buffers.h \
    include/glecommon.h \
    include/glebuffer_target.h \
    engine/buffer_targets.h \
    engine/buffer_object_manager.h

