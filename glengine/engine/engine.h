#ifndef ENGINE_H
#define ENGINE_H

#include <glengine.h>

#include "query_object_manager.h"
#include "buffer_object_manager.h"
#include "program_manager.h"
#include "vertex_array_manager.h"
#include "texture_manager.h"
#include "framebuffer_manager.h"

namespace gle
{
    struct engine_t
        : i_engine
    {
        engine_t() { glewInit(); }

        i_query_object_manager * queries() { return &query_manager_; }
        i_buffer_object_manager * buffers() { return &buffer_manager_; }
        i_program_manager * programs() { return &program_manager_; }
        i_vertex_array_manager * vaos() { return &vao_manager_; }
        i_texture_manager * textures() { return &texture_manager_; }
        i_framebuffer_manager * fbos() { return  &fbo_manager_; }

        // compute shaders
        void dispatch_compute(int gx, int gy, int gz);

        // whole framebuffer operations
        void clear(bit_plane_bit_t buffers_mask);
        void clear_color(glm::vec4 color);

        // memory access synchronization
        void memory_barrier(memory_barrier_bit_t barriers);

        // error detection
        GLenum get_error();
        char const * get_error_string(GLenum error) const;

        // viewport
        void viewport(int x, int y, int width, int height);

    private:
        query_object_manager_t query_manager_;
        buffer_object_manager_t buffer_manager_;
        program_manager_t program_manager_;
        vertex_array_manager_t vao_manager_;
        texture_manager_t texture_manager_;
        framebuffer_manager_t fbo_manager_;
    };
}

#endif // ENGINE_H
