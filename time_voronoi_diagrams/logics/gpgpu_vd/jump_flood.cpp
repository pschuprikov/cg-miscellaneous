#include "jump_flood.h"

namespace tvd
{

struct jump_flood_t::impl_t
{
    gle::program_ptr prg;

    gle::shader_variable_ptr max_distance;
    gle::shader_variable_ptr outer_params;
    gle::shader_variable_ptr jump_step;

    gle::shader_variable_ptr img_vd;

    impl_t()
    {
        load_program();
        find_uniforms();
    }
private:
    void find_uniforms()
    {
        max_distance = prg->var("max_distance");
        outer_params = prg->var("outer_params");
        jump_step = prg->var("jump_step");

        img_vd = prg->var("img_vd");
    }

    void load_program()
    {
        prg = gle::default_engine()->programs()->create_program("jump flood");
        try
        {
            gle::shader_ptr cs = gle::default_engine()->programs()->load_shader(
                "shaders/jump_flood_cs.glsl",
                gle::ST_compute);
            prg->attach_shader(cs);
            prg->link();
        }
        catch(gle::compilation_failed_exception_t const& cfe)
        {
            std::cerr << cfe.name() << "\n" << cfe.reason();
        }
    }
};

jump_flood_t::jump_flood_t(float max_distance, float outer_velocity)
    : max_distance_(max_distance)
    , outer_velocity_(outer_velocity)
    , impl_(new impl_t())
{}

jump_flood_t::~jump_flood_t() {}

void jump_flood_t::process(gle::texture_ptr tex)
{
    gle::texture_ptr tex_in = tex;

    gle::image_binding_t bin = gle::default_engine()->textures()->reserve_image_binding();
    gle::default_engine()->textures()->bind_image(bin, tex_in, 0, gle::ITA_read_write, GL_RGBA32UI);

    impl_->img_vd->set(bin);
    impl_->max_distance->set(max_distance_);

    double const sin_alpha = outer_velocity_;
    double const cos_alpha = sqrt(1 - sin_alpha * sin_alpha);

    impl_->outer_params->set(glm::vec3(sin_alpha, 1 / sin_alpha, cos_alpha));

    gle::default_engine()->programs()->use(impl_->prg);

    int const max_dim = std::max(tex->width(), tex->height());

    int step;
    for (step = 1; step << 1 < max_dim; step <<= 1)
        ;

    int const group_size = 16;
    int const dimx = (tex->width() + group_size - 1) / group_size;
    int const dimy = (tex->height() + group_size - 1) / group_size;

    gle::time_elapsed_query_ptr teq = gle::default_engine()->queries()->create_time_elapsed_query();
    teq->begin_query();

    for (; step > 0; step >>= 1)
    {
        impl_->jump_step->set(step);
        gle::default_engine()->dispatch_compute(dimx, dimy, 1);
    }
    gle::default_engine()->dispatch_compute(dimx, dimy, 1);

    teq->end_query();
    std::cerr << "jump_flood_time: " << (teq->time_elapsed_ns() * 1.e-6) << "ms\n";

    gle::default_engine()->programs()->reset_program_in_use();
    gle::default_engine()->textures()->release_image_binding(bin);
}

}
