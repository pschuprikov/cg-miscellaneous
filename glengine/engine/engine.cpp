#include <bitset>

#include "engine.h"

gle::i_engine * gle::default_engine()
{
    static engine_t eng;
    return &eng;
}

namespace gle
{

engine_t::engine_t() : line_width_(1) { glewInit(); }

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


void engine_t::draw_arrays(drawing_mode_t mode, int first, int count)
{
    glDrawArrays(mode, first, count);
}

void engine_t::draw_elements(drawing_mode_t mode, int count, GLenum type, const void * indicies)
{
    glDrawElements(mode, count, type, indicies);
}

void engine_t::enable(engine_state_bit_t bits)
{
    if ((bits & ES_depth_test) && !(state_ & ES_depth_test))
        glEnable(gl_state(ES_depth_test));
    if ((bits & ES_blend) && !(state_ & ES_blend))
        glEnable(gl_state(ES_blend));
    if ((bits & ES_line_smooth) && !(state_ & ES_line_smooth))
        glEnable(gl_state(ES_line_smooth));
    if ((bits & ES_point_smooth) && !(state_ & ES_point_smooth))
        glEnable(gl_state(ES_point_smooth));
    state_ = state_ | bits;
}

void engine_t::disable(engine_state_bit_t bits)
{
    if ((bits & ES_depth_test) && (state_ & ES_depth_test))
        glDisable(gl_state(ES_depth_test));
    if ((bits & ES_blend) && (state_ & ES_blend))
        glDisable(gl_state(ES_blend));
    if ((bits & ES_line_smooth) && (state_ & ES_line_smooth))
        glDisable(gl_state(ES_line_smooth));
    if ((bits & ES_point_smooth) && (state_ & ES_point_smooth))
        glDisable(gl_state(ES_point_smooth));
    state_ = state_ & ~bits;
}

void engine_t::blit_framebuffer(int src_x0, int src_y0, int src_x1, int src_y1,
                                int dst_x0, int dst_y0, int dst_x1, int dst_y1,
                                bit_plane_bit_t mask, framebuffer_filter_t filter)
{
    glBlitFramebuffer(src_x0, src_y0, src_x1, src_y1, dst_x0, dst_y0, dst_x1, dst_y1, mask, filter);
}

blending_t engine_t::blending() const
{
    return blending_;
}

void engine_t::set_blending(blending_t const& blending)
{
    blending_ = blending;
    glBlendEquation(blending.equation());
    glBlendFunc(blending.src(), blending.dst());
}

float engine_t::line_width() const
{
    return line_width_;
}

void engine_t::set_line_width(float width)
{
    line_width_ = width;
    glLineWidth(line_width_);
}

float engine_t::point_size() const
{
    return point_size_;
}

void engine_t::set_point_size(float size)
{
    point_size_ = size;
    glPointSize(size);
}

}
