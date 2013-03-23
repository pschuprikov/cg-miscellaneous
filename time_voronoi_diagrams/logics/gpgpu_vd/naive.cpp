#include "naive.h"

namespace tvd
{

naive_t::naive_t()
{
    buf_tex_ = gle::default_engine()->textures()->create_buffer_texture();

    prg_ = gle::default_engine()->programs()->create_program("naive");
    try
    {
        gle::shader_ptr cs = gle::default_engine()->programs()->load_shader("shaders/naive_cs.glsl", gle::ST_compute);
        prg_->attach_shader(cs);
        prg_->link();
    }
    catch (gle::compilation_failed_exception_t const& ex)
    {
        std::cerr << ex.what() << "\n" << ex.reason() << "\n";
    }

    color_ = prg_->var("color");
    img_vd_ = prg_->var("img_vd");
    tex_line_ = prg_->var("tex_line");
    max_distance_ = prg_->var("max_distance");
    outer_params_ = prg_->var("outer_params");
}

}
