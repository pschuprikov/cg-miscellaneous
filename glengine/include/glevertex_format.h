#ifndef GLEVERTEX_FORMAT_H
#define GLEVERTEX_FORMAT_H

#include <glecommon.h>
#include <gleshader_input.h>

namespace gle
{

struct base_vertex_format
{
protected:
    base_vertex_format(int size, GLenum type, int relative_offset)
        : size_(size), type_(type), relative_offset_(relative_offset)
    {}

public:
    int size() const { return size_; }
    GLenum type() const { return type_; }
    int relative_offset() const { return relative_offset_; }

private:
    int size_;
    GLenum type_;
    int relative_offset_;
};

struct int_vertex_format
    : base_vertex_format
{
    int_vertex_format(int size, GLenum type, int relative_offset)
        : base_vertex_format(size, type, relative_offset)
    {}

    void set_format(shader_input_variable_ptr var) const;
};

struct float_vertex_format
    : base_vertex_format
{
    float_vertex_format(int size, GLenum type, int relative_offset, bool normalized)
        : base_vertex_format(size, type, relative_offset)
        , normalized_(normalized)
    {}

    bool normalized() const { return normalized_; }

    void set_format(shader_input_variable_ptr var) const;

private:
    bool normalized_;
};

typedef boost::variant<int_vertex_format, float_vertex_format> vertex_format_t;

}

#endif // GLEVERTEX_FORMAT_H
