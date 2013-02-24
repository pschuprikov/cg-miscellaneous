#ifndef LINES_COMMON_H
#define LINES_COMMON_H

#include "stdafx.h"

#include <iostream>

namespace tvd
{

#pragma pack(push, 1)
struct line_vertex_t
{
    float x;
    float y;

    friend std::istream& operator>>(std::istream& stin, line_vertex_t& lvtx)
    {
        stin >> lvtx.x >> lvtx.y;
        return stin;
    }
};
#pragma pack(pop)

struct line_data_t
{
    line_data_t(glm::vec3 color = glm::vec3())
        : color_(color)
        , vertrices_(gle::default_engine()->buffers()->create_buffer())
    {}

    glm::vec3 color() const { return color_; }
    gle::buffer_ptr vtx_data() const { return vertrices_; }

    int count() const { return vertrices_->size() / sizeof(line_vertex_t); }

    friend std::istream& operator>>(std::istream& stin, line_data_t& ld)
    {
        stin >> ld.color_.r >> ld.color_.g >> ld.color_.b;
        int num_vertices;
        stin >> num_vertices;
        std::vector<line_vertex_t> vertices(num_vertices);
        for (int i = 0; i < num_vertices; i++)
        {
            stin >> vertices[i];
        }
        ld.vertrices_->buffer_data(gle::BU_static_draw,
            sizeof(line_vertex_t) * num_vertices, &vertices[0]);

        return stin;
    }

private:
    glm::vec3 color_;
    gle::buffer_ptr vertrices_;
};

typedef std::vector<line_data_t> lines_data_t;

}

#endif // LINES_COMMON_H
