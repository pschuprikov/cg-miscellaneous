#ifndef GLENGINHE_H
#define GLENGINHE_H

#include <glm/glm.hpp>

#include <glequery_object_manager.h>
#include <glebuffer_object_manager.h>
#include <gleprogram_manager.h>
#include <glevertex_array_manager.h>

namespace gle
{

    enum memory_barrier_bit_t { MBB_vertex_attrib_array = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
                                MBB_element_array = GL_ELEMENT_ARRAY_BARRIER_BIT,
                                MBB_uniform = GL_UNIFORM_BARRIER_BIT,
                                MBB_texture_fetch = GL_TEXTURE_FETCH_BARRIER_BIT,
                                MBB_shader_image_access = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
                                MBB_command = GL_COMMAND_BARRIER_BIT,
                                MBB_pixel_buffer = GL_PIXEL_BUFFER_BARRIER_BIT,
                                MBB_texture_update = GL_TEXTURE_UPDATE_BARRIER_BIT,
                                MBB_buffer_update = GL_BUFFER_UPDATE_BARRIER_BIT,
                                MBB_framebuffer = GL_FRAMEBUFFER_BARRIER_BIT,
                                MBB_tranform_feedback = GL_TRANSFORM_FEEDBACK_BARRIER_BIT };

    inline memory_barrier_bit_t operator|(memory_barrier_bit_t lhs, memory_barrier_bit_t rhs)
    {
        return memory_barrier_bit_t((int) lhs | (int) rhs);
    }

    enum bit_plane_bit_t { BPB_color = GL_COLOR_BUFFER_BIT,
                           BPB_depth = GL_DEPTH_BUFFER_BIT,
                           BPB_stencil = GL_STENCIL_BUFFER_BIT};

    inline bit_plane_bit_t operator|(bit_plane_bit_t lhs, bit_plane_bit_t rhs)
    {
        return bit_plane_bit_t((int) lhs | (int) rhs);
    }

    struct i_engine
    {
        virtual i_query_object_manager * queries() = 0;
        virtual i_buffer_object_manager * buffers() = 0;
        virtual i_program_manager * programs() = 0;
        virtual i_vertex_array_manager * vaos() = 0;

        virtual void memory_barrier(memory_barrier_bit_t barriers) = 0;

        // whole framebuffer operations
        virtual void clear(bit_plane_bit_t bit_plane_mask) = 0;
        virtual void clear_color(glm::vec4 color) = 0;

        virtual ~i_engine() {}
    };

    i_engine * default_engine();
}

#endif // GLENGINHE_H
