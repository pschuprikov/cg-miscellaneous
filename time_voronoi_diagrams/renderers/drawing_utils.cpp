#include "drawing_utils.h"

namespace tvd
{

void quad01::draw(gle::shader_input_variable_ptr var)
{
    static gle::vertex_format_t const fmt(gle::float_vertex_format(2, GL_FLOAT, 0, false));

    instance()->vao_->add_vertex_attrib(var, fmt, instance()->binding_);
    gle::default_engine()->vaos()->set_current(instance()->vao_);
    gle::default_engine()->draw_arrays(gle::DM_triangle_strip, 0, 4);

    gle::default_engine()->vaos()->reset_current();
    instance()->vao_->remove_vertex_attrib(var);
}

quad01 * quad01::instance()
{
    static quad01 quad;
    return &quad;
}

quad01::quad01()
{
    vao_ = gle::default_engine()->vaos()->create_vertex_array();

    static const float vtx_data[] = {
        0.f, 0.f,
        1.f, 0.f,
        0.f, 1.f,
        1.f, 1.f
    };
    gle::buffer_ptr tex01buf = gle::default_engine()->buffers()->create_buffer();
    tex01buf->buffer_data(gle::BU_static_draw, sizeof(vtx_data), vtx_data);

    binding_ = vao_->reserve_binding();
    vao_->bind_buffer(binding_, tex01buf, 0, sizeof(float) * 2);
}

}
