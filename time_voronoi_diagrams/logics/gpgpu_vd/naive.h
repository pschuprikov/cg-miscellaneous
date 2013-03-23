#ifndef NAIVE_H
#define NAIVE_H

#include "stdafx.h"
#include "lines_prepare.h"
#include "cleaner.h"

namespace tvd
{

struct naive_t
{
    naive_t();

    template<class Iter>
    void process(Iter beg, Iter end, gle::texture_ptr tex, float max_distance, float outer_velocity)
    {
        gle::image_binding_t vd_bind = gle::default_engine()->textures()->reserve_image_binding();
        img_vd_->set(vd_bind);

        gle::texture_binding_t line_bind = gle::default_engine()->textures()->reserve_texture_binding();
        tex_line_->set(line_bind);

        max_distance_->set(max_distance);

        double const sin_alpha = outer_velocity;
        double const cos_alpha = sqrt(1 - sin_alpha * sin_alpha);

        outer_params_->set(glm::vec3(sin_alpha, 1 / sin_alpha, cos_alpha));

        gle::default_engine()->textures()->bind_image(vd_bind, tex, 0,
            gle::ITA_read_write, tex->internal_format());
        gle::default_engine()->textures()->bind_texture(line_bind, buf_tex_);

        gle::default_engine()->programs()->use(prg_);

        int const group_size = 16;
        int const dimx = (tex->width() + group_size - 1) / group_size;
        int const dimy = (tex->height() + group_size - 1) / group_size;

        gle::time_elapsed_query_ptr teq = gle::default_engine()->queries()->create_time_elapsed_query();
        teq->begin_query();

        for (;beg != end; ++beg)
        {
            buf_tex_->set_buffer(GL_RGB32F, beg->segments());
            //gle::default_engine()->textures()->bind_texture(line_bind, buf_tex_);
            color_->set(beg->color());
            gle::default_engine()->dispatch_compute(dimx, dimy, 1);
        }

        teq->end_query();
        std::cerr << "naive_time: " << (teq->time_elapsed_ns() * 1.e-6) << "ms\n";

        gle::default_engine()->programs()->reset_program_in_use();

        gle::default_engine()->textures()->release_image_binding(vd_bind);
        gle::default_engine()->textures()->release_texture_binding(line_bind);
    }

private:
    gle::buffer_texture_ptr buf_tex_;
    cleaner_t cleaner_;

    gle::program_ptr prg_;
    gle::shader_variable_ptr color_;
    gle::shader_variable_ptr img_vd_;
    gle::shader_variable_ptr tex_line_;
    gle::shader_variable_ptr max_distance_;
    gle::shader_variable_ptr outer_params_;
};

}

#endif // NAIVE_H
