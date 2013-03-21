#include <glm/gtc/matrix_transform.hpp>

#include "voronoi_texdraw.h"
#include "renderers/drawing_utils.h"

namespace tvd
{

struct voronoi_texdraw_t::impl_t
{
    gle::program_ptr prg;

    gle::shader_variable_ptr img_vd;

    impl_t()
    {
        load_program();
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
};

voronoi_texdraw_t::voronoi_texdraw_t()
    : impl_(new impl_t())
{}


voronoi_texdraw_t::~voronoi_texdraw_t() {}

void voronoi_texdraw_t::draw_tex(gle::texture_ptr tex)
{
    gle::default_engine()->programs()->use(impl_->prg);

    gle::image_binding_t img_binding = gle::default_engine()->textures()->reserve_image_binding();
    gle::default_engine()->textures()->bind_image(img_binding, tex, 0, gle::ITA_read_only, GL_R32UI);

    impl_->img_vd->set(img_binding);
    quad01::draw(impl_->prg->input_var("in_pos"));

    gle::default_engine()->textures()->release_image_binding(img_binding);

    gle::default_engine()->programs()->reset_program_in_use();
}

}
