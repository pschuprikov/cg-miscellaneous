#include "cleaner.h"

namespace tvd
{

cleaner_t::cleaner_t()
{
    prg_ = gle::default_engine()->programs()->create_program("cleaner");
    try
    {
        gle::shader_ptr cs = gle::default_engine()->programs()->load_shader("shaders/cleaner_cs.glsl", gle::ST_compute);
        prg_->attach_shader(cs);
        prg_->link();
    }
    catch (gle::compilation_failed_exception_t const& ex)
    {
        std::cerr << ex.what() << "\n" << ex.reason() << "\n";
    }
    clear_color_ = prg_->var("clear_color");
    img_clear_ = prg_->var("img_clear");
}

void cleaner_t::clean_tex(gle::texture_ptr tex, glm::uvec4 color)
{
    clear_color_->set(color);
    gle::image_binding_t binding = gle::default_engine()->textures()->reserve_image_binding();
    img_clear_->set(binding);

    gle::default_engine()->textures()->bind_image(binding, tex, 0, gle::ITA_write_only, tex->internal_format());
    gle::default_engine()->programs()->use(prg_);

    size_t const dimx = (tex->width() + 15) / 16;
    size_t const dimy = (tex->height() + 15) / 16;

    gle::default_engine()->dispatch_compute(dimx, dimy, 1);

    gle::default_engine()->programs()->reset_program_in_use();
    gle::default_engine()->textures()->release_image_binding(binding);
}

}
