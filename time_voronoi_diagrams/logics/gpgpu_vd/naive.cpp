#include "naive.h"

namespace tvd
{

naive_t::naive_t()
{
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

    img_vd_ = prg_->var("img_vd");
    img_lines_data_ = prg_->var("img_lines_data");
    max_distance_ = prg_->var("max_distance");
    outer_params_ = prg_->var("outer_params");
    num_segments_ = prg_->var("num_segments");
}

void naive_t::process(gle::texture_ptr tex_rastr, gle::texture_ptr tex_lines,
             float max_distance, float outer_velocity, unsigned int num_segments)
{
    gle::image_binding_t vd_bind = gle::default_engine()->textures()->reserve_image_binding();
    img_vd_->set(vd_bind);

    gle::image_binding_t lines_data_bind = gle::default_engine()->textures()->reserve_image_binding();
    img_lines_data_->set(lines_data_bind);

    max_distance_->set(max_distance);
    num_segments_->set(num_segments);

    double const sin_alpha = outer_velocity;
    double const cos_alpha = sqrt(1 - sin_alpha * sin_alpha);

    outer_params_->set(glm::vec3(sin_alpha, 1 / sin_alpha, cos_alpha));

    gle::default_engine()->textures()->bind_image(vd_bind, tex_rastr, 0,
        gle::ITA_read_write, tex_rastr->internal_format());
    gle::default_engine()->textures()->bind_image(lines_data_bind, tex_lines, 0,
        gle::ITA_read_only, tex_lines->internal_format());

    gle::default_engine()->programs()->use(prg_);

    int const group_size = 16;
    int const dimx = (tex_rastr->width() + group_size - 1) / group_size;
    int const dimy = (tex_rastr->height() + group_size - 1) / group_size;

    gle::time_elapsed_query_ptr teq = gle::default_engine()->queries()->create_time_elapsed_query();
    teq->begin_query();

    gle::default_engine()->dispatch_compute(dimx, dimy, 1);

    teq->end_query();
    std::cerr << "naive_time: " << (teq->time_elapsed_ns() * 1.e-6) << "ms\n";

    gle::default_engine()->programs()->reset_program_in_use();

    gle::default_engine()->textures()->release_image_binding(vd_bind);
    gle::default_engine()->textures()->release_image_binding(lines_data_bind);
}

}
