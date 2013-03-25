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

    void process(gle::texture_ptr tex_rastr, gle::texture_ptr tex_lines,
        float max_distance, float outer_velocity, unsigned int num_segments);

private:
    cleaner_t cleaner_;

    gle::program_ptr prg_;
    gle::shader_variable_ptr img_vd_;
    gle::shader_variable_ptr img_lines_data_;
    gle::shader_variable_ptr max_distance_;
    gle::shader_variable_ptr outer_params_;
    gle::shader_variable_ptr num_segments_;
};

}

#endif // NAIVE_H
