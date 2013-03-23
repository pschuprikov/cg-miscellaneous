#ifndef GLE_VERTEX_ARRAY_MANAGER_H
#define GLE_VERTEX_ARRAY_MANAGER_H

#include <glecommon.h>
#include <glevertex_array.h>

namespace gle
{

enum drawing_mode_t { DM_triangles = GL_TRIANGLES,
                      DM_lines = GL_LINES,
                      DM_line_strip = GL_LINE_STRIP,
                      DM_triangle_strip = GL_TRIANGLE_STRIP,
                      DM_points = GL_POINTS
                    };

struct i_vertex_array_manager
{
    virtual vertex_array_ptr create_vertex_array() = 0;

    virtual void set_current(vertex_array_ptr vao) = 0;
    virtual void reset_current() = 0;
    virtual vertex_array_ptr current() const = 0;
};

}

#endif // GLE_VERTEX_ARRAY_MANAGER_H
