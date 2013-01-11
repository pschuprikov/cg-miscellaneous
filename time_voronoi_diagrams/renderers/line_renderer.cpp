#include <glm/gtc/matrix_transform.hpp>
#include "line_renderer.h"

namespace tvd
{

line_renderer_t::line_renderer_t()
{
    prg_ = gle::default_engine()->programs()->create_program("line renderer");
    gle::shader_ptr fs = gle::default_engine()->programs()->load_shader(
                "/home/pasha/repos/cg-miscellaneous/time_voronoi_diagrams/shaders/line/fs.glsl",
                gle::ST_fragment);
    gle::shader_ptr vs = gle::default_engine()->programs()->load_shader(
                "/home/pasha/repos/cg-miscellaneous/time_voronoi_diagrams/shaders/line/vs.glsl",
                gle::ST_vertex);
    prg_->attach_shader(fs);
    prg_->attach_shader(vs);
    prg_->link();

    glm::mat4 mvp = glm::ortho<float>(0, 1, 0, 1, -1, 1);
    prg_->var("mvp")->set(mvp);

    vao_ = gle::default_engine()->vaos()->create_vertex_array();
    pos_binding_ = vao_->reserve_binding();

    gle::vertex_format_ptr fmt(new gle::float_vertex_format_entry(2, GL_FLOAT, 0, false));

    vao_->add_vertex_attrib(prg_->input_var("in_pos"), fmt, pos_binding_);
}

void line_renderer_t::render_line(const line_data_t &data)
{
    prg_->var("color")->set(data.color());

    vao_->bind_buffer(pos_binding_, data.vtx_data(), 0, sizeof(line_vertex_t));    
    gle::default_engine()->programs()->use(prg_);
    gle::default_engine()->vaos()->set_current(vao_);

    glLineWidth(5.0);
    gle::default_engine()->draw_arrays(gle::DM_line_strip, 0, data.count());

    gle::default_engine()->programs()->reset_program_in_use();
    gle::default_engine()->vaos()->reset_current();
    vao_->unbind_buffer(pos_binding_);
}

}
