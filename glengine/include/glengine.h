#ifndef GLENGINHE_H
#define GLENGINHE_H

#include <glm/glm.hpp>

#include <glequery_object_manager.h>
#include <glebuffer_object_manager.h>
#include <gleprogram_manager.h>
#include <glevertex_array_manager.h>
#include <gletexture_manager.h>
#include <gleframebuffer_manager.h>

#include <gleviewport.h>
#include <gleblending.h>

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
                                MBB_tranform_feedback = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
                                MBB_all = GL_ALL_BARRIER_BITS
                              };

    inline memory_barrier_bit_t operator|(memory_barrier_bit_t lhs, memory_barrier_bit_t rhs)
    {
        return memory_barrier_bit_t((unsigned int) lhs | (unsigned int) rhs);
    }

    enum bit_plane_bit_t { BPB_color = GL_COLOR_BUFFER_BIT,
                           BPB_depth = GL_DEPTH_BUFFER_BIT,
                           BPB_stencil = GL_STENCIL_BUFFER_BIT};

    inline bit_plane_bit_t operator|(bit_plane_bit_t lhs, bit_plane_bit_t rhs)
    {
        return bit_plane_bit_t((unsigned int) lhs | (unsigned int) rhs);
    }

    enum engine_state_bit_t { ES_depth_test = 1,
                              ES_blend = 1 << 1,
                              ES_line_smooth = 1 << 2 };

    inline engine_state_bit_t operator|(engine_state_bit_t lhs, engine_state_bit_t rhs)
    {
        return engine_state_bit_t((unsigned int) lhs | (unsigned int) rhs);
    }

    inline engine_state_bit_t operator&(engine_state_bit_t lhs, engine_state_bit_t rhs)
    {
        return engine_state_bit_t((unsigned int) lhs & (unsigned int) rhs);
    }

    inline engine_state_bit_t operator~(engine_state_bit_t s)
    {
        return engine_state_bit_t(~(unsigned int)s);
    }

    inline GLenum gl_state(engine_state_bit_t st)
    {
        switch(st)
        {
        case ES_depth_test : return GL_DEPTH_TEST;
        case ES_blend : return GL_BLEND;
        case ES_line_smooth : return GL_LINE_SMOOTH;
        default : return 0;
        }
    }

    enum framebuffer_filter_t { FF_linear = GL_LINEAR, FF_nearest = GL_NEAREST };

    struct i_engine
    {
        virtual i_query_object_manager *  queries() = 0;
        virtual i_buffer_object_manager * buffers() = 0;
        virtual i_program_manager *      programs() = 0;
        virtual i_vertex_array_manager *     vaos() = 0;
        virtual i_texture_manager *      textures() = 0;
        virtual i_framebuffer_manager *      fbos() = 0;

        // vertex arrays
        virtual void draw_arrays(drawing_mode_t mode, int first, int count) = 0;
        virtual void draw_elements(drawing_mode_t mode, int count, GLenum type, const void * indicies) = 0;

        // memory access synchronization
        virtual void memory_barrier(memory_barrier_bit_t barriers) = 0;

        // compute shaders
        virtual void dispatch_compute(int gx, int gy, int gz) = 0;

        // whole framebuffer operations
        virtual void clear(bit_plane_bit_t bit_plane_mask) = 0;
        virtual void clear_color(glm::vec4 color) = 0;
        virtual void blit_framebuffer(int src_x0, int src_y0, int src_x1, int src_y1,
                                      int dst_x0, int dst_y0, int dst_x1, int dst_y1,
                                      bit_plane_bit_t mask, framebuffer_filter_t filter) = 0;

        // error_stuff
        virtual GLenum get_error() = 0;
        virtual char const * get_error_string(GLenum error) const = 0;

        // viewport
        virtual viewport_t const& viewport() const = 0;
        virtual void set_viewport(viewport_t const& vp) = 0;

        // state management
        virtual void enable(engine_state_bit_t bits) = 0;
        virtual void disable(engine_state_bit_t bits) = 0;

        // pixel operations
        virtual blending_t blending() const = 0;
        virtual void set_blending(blending_t const& blending) = 0;

        // rasterization
        virtual float line_width() const = 0;
        virtual void set_line_width(float width) = 0;

        virtual ~i_engine() {}
    };

    i_engine * default_engine();
}

#endif // GLENGINHE_H
