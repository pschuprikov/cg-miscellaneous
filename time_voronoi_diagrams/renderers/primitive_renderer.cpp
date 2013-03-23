#include "primitive_renderer.h"

namespace tvd
{

void primirives_renderer_t::init_unit_quad()
{
    static float vtx[] = { 1.f, -1.f,
                           1.f,  1.f,
                          -1.f, -1.f,
                          -1.f,  1.f };

    gle::buffer_ptr vtx_buf = gle::default_engine()->buffers()->create_buffer();
    vtx_buf->buffer_data(gle::BU_static_draw, sizeof(vtx), vtx);

    unit_quad_ = gle::default_engine()->vaos()->create_vertex_array();
    unit_quad_binding_ = unit_quad_->reserve_binding();
    unit_quad_->bind_buffer(unit_quad_binding_, vtx_buf, 0, sizeof(float) * 2);
    unit_quad_count_ = 4;
}

void primirives_renderer_t::draw_unit_quad(gle::shader_input_variable_ptr in_pos)
{
    static gle::float_vertex_format vtx_fmt(2, GL_FLOAT, 0, false);
    unit_quad_->add_vertex_attrib(in_pos, vtx_fmt, unit_quad_binding_);
    gle::default_engine()->vaos()->set_current(unit_quad_);
    gle::default_engine()->draw_arrays(gle::DM_triangle_strip, 0, unit_quad_count_);
    gle::default_engine()->vaos()->reset_current();
    unit_quad_->remove_vertex_attrib(in_pos);
}

}
