QT -= core gui

CONFIG += debug

QMAKE_CXXFLAGS = -Wno-reorder

TARGET = glengine
TEMPLATE = lib

SOURCES += \
    engine/queries.cpp \
    engine/query_object_manager.cpp \
    engine/engine.cpp \
    engine/buffers.cpp \
    engine/buffer_targets.cpp \
    engine/buffer_object_manager.cpp \
    engine/shaders.cpp \
    engine/program_manager.cpp \
    utils/io_utils.cpp \
    engine/program.cpp \
    engine/default_uniform/default_uniform.cpp \
    engine/default_uniform/default_uniform_array.cpp \
    engine/shader_block/shader_block_variable.cpp \
    engine/shader_block/shader_block_array.cpp \
    engine/shader_block/mapped_block_adaptor.cpp \
    engine/program_ifaces/iface_storage.cpp \
    engine/shader_block/shader_block.cpp \
    engine/program_ifaces/iface_input_data.cpp \
    engine/shader_input/shader_input.cpp \
    engine/vertex_format.cpp \
    engine/vertex_array_manager.cpp \
    engine/vertex_array.cpp \
    engine/textures/texture.cpp \
    engine/textures/buffer_texture.cpp \
    engine/texture_manager.cpp \
    engine/program_ifaces/iface_output_data.cpp \
    engine/shader_output/shader_output.cpp \
    engine/framebuffer/framebuffer_attachment.cpp \
    engine/framebuffer/framebuffer.cpp \
    engine/framebuffer_manager.cpp

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
    engine/buffer_object_manager.h \
    include/gleshader.h \
    include/gleprogram_manager.h \
    engine/shaders.h \
    engine/program_manager.h \
    utils/io_utils.h \
    include/gleprogram.h \
    engine/program.h \
    include/gleshader_variable.h \
    include/gleshader_block.h \
    engine/default_uniform/default_uniform.h \
    engine/default_uniform/default_uniform_array.h \
    engine/shader_block/shader_block.h \
    engine/shader_block/shader_block_variable.h \
    engine/shader_block/shader_block_array.h \
    engine/shader_block/mapped_block_adaptor.h \
    engine/shader_block/mapped_block_adaptor_fwd.h \
    engine/shader_block/shader_block_fwd.h \
    engine/program_ifaces/iface_common_data.h \
    engine/program_ifaces/iface_default_data.h \
    engine/program_ifaces/iface_block_data.h \
    engine/program_ifaces/iface_storage.h \
    engine/program_ifaces/iface_storage_fwd.h \
    engine/program_ifaces/iface_input_data.h \
    include/gleshader_input.h \
    engine/shader_input/shader_input.h \
    include/glevertex_array.h \
    include/glevertex_format.h \
    engine/vertex_array_manager.h \
    include/glevertex_array_manager.h \
    engine/vertex_array.h \
    include/gletexture.h \
    include/gletexture_manager.h \
    engine/textures/texture.h \
    engine/textures/buffer_texture.h \
    engine/texture_manager.h \
    include/gleshader_output.h \
    engine/program_ifaces/iface_output_data.h \
    engine/shader_output/shader_output.h \
    include/gleframebuffer.h \
    include/gleframebuffer_manager.h \
    engine/framebuffer/framebuffer.h \
    engine/framebuffer/framebuffer_attachment.h \
    utils/stl_utils.h \
    engine/framebuffer_manager.h \
    include/gleviewport.h

