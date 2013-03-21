#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include "stdafx.h"

namespace tvd
{
    struct quad01
    {
    private:
        quad01();

    public:
        static void draw(gle::shader_input_variable_ptr var);

    private:
        static quad01 * instance();

        gle::vertex_array_ptr vao_;
        gle::vertex_attrib_binding_t binding_;
    };
}

#endif // DRAWING_UTILS_H
