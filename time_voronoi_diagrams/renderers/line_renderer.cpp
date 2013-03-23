#include <glm/gtc/matrix_transform.hpp>
#include "line_renderer.h"

namespace tvd
{

line_renderer_t::line_renderer_t()
{
    prg_ = gle::default_engine()->programs()->create_program("line renderer");
    gle::shader_ptr fs = gle::default_engine()->programs()->load_shader(
                "shaders/line_fs.glsl",
                gle::ST_fragment);
    gle::shader_ptr vs = gle::default_engine()->programs()->load_shader(
                "shaders/line_vs.glsl",
                gle::ST_vertex);
    prg_->attach_shader(fs);
    prg_->attach_shader(vs);
    prg_->link();

    glm::mat4 mvp = glm::ortho<float>(0, 1, 0, 1, -1, 1);
    prg_->var("mvp")->set(mvp);

    vao_ = gle::default_engine()->vaos()->create_vertex_array();
    pos_binding_ = vao_->reserve_binding();

    static gle::vertex_format_t fmt(gle::float_vertex_format(2, GL_FLOAT, 0, false));

    vao_->add_vertex_attrib(prg_->input_var("in_pos"), fmt, pos_binding_);
}

void line_renderer_t::render_line(const line_data_t &data)
{
    prg_->var("color")->set(data.color());
    gle::default_engine()->enable(gle::ES_line_smooth);
    gle::default_engine()->enable(gle::ES_point_smooth);
    gle::default_engine()->set_line_width(5.0);
    gle::default_engine()->set_point_size(10.0);

    vao_->bind_buffer(pos_binding_, data.vtx_data(), 0, sizeof(line_vertex_t));
    gle::default_engine()->programs()->use(prg_);
    gle::default_engine()->vaos()->set_current(vao_);

    gle::default_engine()->draw_arrays(gle::DM_line_strip, 0, data.count());;
    gle::default_engine()->draw_arrays(gle::DM_points, 0, 1);

    gle::default_engine()->programs()->reset_program_in_use();
    gle::default_engine()->vaos()->reset_current();
    vao_->unbind_buffer(pos_binding_);

    gle::default_engine()->disable(gle::ES_line_smooth);
    gle::default_engine()->disable(gle::ES_point_smooth);
}

}
