#ifndef PRIMITIVE_RENDERER_H
#define PRIMITIVE_RENDERER_H

#include "stdafx.h"

namespace tvd
{

struct primirives_renderer_t
{
    primirives_renderer_t()
    {
        init_unit_quad();
    }

    void draw_unit_quad(gle::shader_input_variable_ptr in_pos);
private:
    void init_unit_quad();

private:
    gle::vertex_array_ptr unit_quad_;
    size_t unit_quad_count_;
    gle::vertex_attrib_binding_t unit_quad_binding_;
};

}

#endif // PRIMITIVE_RENDERER_H
