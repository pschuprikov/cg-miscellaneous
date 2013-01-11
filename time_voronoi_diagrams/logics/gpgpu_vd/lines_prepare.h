#ifndef LINES_PREPARE_H
#define LINES_PREPARE_H

#include "../lines_builder.h"

namespace tvd
{

#pragma pack(push, 1)
struct newline_vertex_t
{
    float x;
    float y;

    float prefix_dist;

    newline_vertex_t()
        : x(0), y(0), prefix_dist(0)
    {}

    newline_vertex_t(float x, float y, float prefix_dist)
        : x(x), y(y), prefix_dist(prefix_dist)
    {}
};
#pragma pack(pop)

struct newline_data_t
{
    newline_data_t(glm::vec3 color, gle::buffer_ptr segments)
        : color_(color), segments_(segments)
    {}

    int count() const { return segments_->size() / sizeof(newline_vertex_t); }

    gle::buffer_ptr segments() const { return segments_; }
    glm::vec3 color() const { return color_; }

private:
    glm::vec3 color_;
    gle::buffer_ptr segments_;
};


struct lines_prepare_t
{
    lines_prepare_t() {}

    newline_data_t prepare(line_data_t const& data);
};

}

#endif // LINES_PREPARE_H
