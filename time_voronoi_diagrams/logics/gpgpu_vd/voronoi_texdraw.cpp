#include <glm/gtc/matrix_transform.hpp>

#include "voronoi_texdraw.h"

namespace tvd
{

struct voronoi_texdraw_t::impl_t
{
    gle::vertex_array_ptr vao;
    gle::program_ptr prg;

    gle::shader_variable_ptr img_vd;

    int count;

    impl_t()
    {
        load_program();
        setup_vao();
    }

private:
    void load_program()
    {
        prg = gle::default_engine()->programs()->create_program("vd_texdraw");
        try
        {
            gle::shader_ptr fs = gle::default_engine()->programs()->load_shader(
                "shaders/texdraw_fs.glsl",
                gle::ST_fragment);
            gle::shader_ptr vs = gle::default_engine()->programs()->load_shader(
                "shaders/texdraw_vs.glsl",
                gle::ST_vertex);
            prg->attach_shader(fs);
            prg->attach_shader(vs);
            prg->link();
        }
        catch (gle::compilation_failed_exception_t const& exc)
        {
            std::cerr << exc.name() << "\n" << exc.reason() << "\n";
        }
        img_vd = prg->var("img_vd");
        glm::mat4 mvp = glm::ortho<float>(0, 1, 0, 1, -1, 1);
        prg->var("mvp")->set(mvp);
    }

    void setup_vao()
    {
        vao = gle::default_engine()->vaos()->create_vertex_array();

        static const float vtx_data[] = {
            0.f, 0.f,
            1.f, 0.f,
            0.f, 1.f,
            1.f, 1.f
        };
        gle::buffer_ptr tex01buf = gle::default_engine()->buffers()->create_buffer();
        tex01buf->buffer_data(gle::BU_static_draw, sizeof(vtx_data), vtx_data);

        gle::vertex_attrib_binding_t binding = vao->reserve_binding();
        vao->bind_buffer(binding, tex01buf, 0, sizeof(float) * 2);
        static gle::vertex_format_t const fmt(gle::float_vertex_format(2, GL_FLOAT, 0, false));
        vao->add_vertex_attrib(prg->input_var("in_pos"), fmt, binding);

        count = 4;
    }
};

voronoi_texdraw_t::voronoi_texdraw_t()
    : impl_(new impl_t())
{}


voronoi_texdraw_t::~voronoi_texdraw_t() {}

void voronoi_texdraw_t::draw_tex(gle::texture_ptr tex)
{
    gle::default_engine()->vaos()->set_current(impl_->vao);
    gle::default_engine()->programs()->use(impl_->prg);

    gle::image_binding_t img_binding = gle::default_engine()->textures()->reserve_image_binding();
    gle::default_engine()->textures()->bind_image(img_binding, tex, 0, gle::ITA_read_only, GL_RGBA32UI);

    impl_->img_vd->set(img_binding);

    gle::default_engine()->draw_arrays(gle::DM_triangle_strip, 0, impl_->count);

    gle::default_engine()->textures()->release_image_binding(img_binding);

    gle::default_engine()->vaos()->reset_current();
    gle::default_engine()->programs()->reset_program_in_use();
}

}
