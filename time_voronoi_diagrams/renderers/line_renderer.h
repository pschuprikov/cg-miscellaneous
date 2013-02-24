#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

#include "stdafx.h"

#include "lines_common.h"

namespace tvd
{

struct line_renderer_t
{
    line_renderer_t();

    void render_line(line_data_t const& data);

private:
    gle::program_ptr prg_;
    gle::vertex_array_ptr vao_;

    gle::vertex_attrib_binding_t pos_binding_;
};
typedef boost::shared_ptr<line_renderer_t> line_renderer_ptr;

}

#endif // LINE_RENDERER_H
