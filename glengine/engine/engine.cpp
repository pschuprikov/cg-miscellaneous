#include "engine.h"

gle::i_engine * gle::default_engine()
{
    static engine_t eng;
    return &eng;
}

namespace gle
{

void engine_t::memory_barrier(memory_barrier_bit_t barriers)
{
    glMemoryBarrier(barriers);
}

void engine_t::clear(bit_plane_bit_t buffers_mask)
{
    glClear(buffers_mask);
}

void engine_t::clear_color(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void engine_t::dispatch_compute(int gx, int gy, int gz)
{
    glDispatchCompute(gx, gy, gz);
}

GLenum engine_t::get_error()
{
    return glGetError();
}

char const * engine_t::get_error_string(GLenum error) const
{
    switch (error)
    {
    case GL_NO_ERROR : return "No error";
    case GL_INVALID_ENUM: return "Invalid enum";
    case GL_INVALID_OPERATION : return "Invalid operation";
    case GL_INVALID_VALUE: return "Invalid value";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
    default : return "Unknown error";
    }
}

void engine_t::set_viewport(viewport_t const& vp)
{
    viewport_ = vp;
    glViewport(vp.x(), vp.y(), vp.width(), vp.height());
}


}
