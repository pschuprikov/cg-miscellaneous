#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

#include "stdafx.h"

namespace tvd
{

#pragma pack(push, 1)
struct line_vertex_t
{
    float x;
    float y;
};
#pragma pack(pop)

struct line_data_t
{
    line_data_t(glm::vec3 color)
        : color_(color)
        , vertrices_(gle::default_engine()->buffers()->create_buffer())
    {}

    glm::vec3 color() const { return color_; }
    gle::buffer_ptr vtx_data() const { return vertrices_; }

    int count() const { return vertrices_->size() / sizeof(line_vertex_t); }

private:
    glm::vec3 color_;
    gle::buffer_ptr vertrices_;
};

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
