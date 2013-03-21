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
    gle::shader_variable_ptr img_vd_dc;

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
        img_vd_dc = prg->var("img_vd_dc");
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

void jump_flood_t::process(gle::texture_ptr tex_seg, gle::texture_ptr tex_dist_col)
{
    gle::image_binding_t bin_seg = gle::default_engine()->textures()->reserve_image_binding();
    gle::image_binding_t bin_dc = gle::default_engine()->textures()->reserve_image_binding();
    gle::default_engine()->textures()->bind_image(bin_seg, tex_seg, 0, gle::ITA_read_write, GL_RG32UI);
    gle::default_engine()->textures()->bind_image(bin_dc, tex_dist_col, 0, gle::ITA_read_write, GL_R32UI);

    impl_->img_vd->set(bin_seg);
    impl_->img_vd_dc->set(bin_dc);
    impl_->max_distance->set(max_distance_);

    double const sin_alpha = outer_velocity_;
    double const cos_alpha = sqrt(1 - sin_alpha * sin_alpha);

    impl_->outer_params->set(glm::vec3(sin_alpha, 1 / sin_alpha, cos_alpha));

    gle::default_engine()->programs()->use(impl_->prg);

    int const max_dim = std::max(tex_seg->width(), tex_seg->height());

    int step;
    for (step = 1; step << 1 < max_dim; step <<= 1)
        ;

    int const group_size = 16;
    for (; step > 0; step >>= 1)
    {
        impl_->jump_step->set(step);

        gle::default_engine()->dispatch_compute((tex_seg->width() + group_size - 1) / group_size,
            (tex_seg->height() + group_size - 1) / group_size, 1);
    }
    gle::default_engine()->dispatch_compute((tex_seg->width() + group_size - 1) / group_size,
        (tex_seg->height() + group_size - 1) / group_size, 1);
    gle::default_engine()->memory_barrier(gle::MBB_texture_fetch);

    gle::default_engine()->programs()->reset_program_in_use();
    gle::default_engine()->textures()->release_image_binding(bin_seg);
    gle::default_engine()->textures()->release_image_binding(bin_dc);
}

}
