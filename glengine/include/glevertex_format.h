#ifndef GLEVERTEX_FORMAT_H
#define GLEVERTEX_FORMAT_H

#include <glecommon.h>
#include <gleshader_input.h>

namespace gle
{

struct base_vertex_format_entry
{
    base_vertex_format_entry(int size, GLenum type, int relative_offset)
        : size_(size), type_(type), relative_offset_(relative_offset)
    {}

    virtual ~base_vertex_format_entry() {}

    int size() const { return size_; }
    GLenum type() const { return type_; }
    int relative_offset() const { return relative_offset_; }

    virtual void set_format(shader_input_variable_ptr var) const = 0;

private:
    int size_;
    GLenum type_;
    int relative_offset_;
};
typedef boost::shared_ptr<base_vertex_format_entry> vertex_format_ptr;

struct int_vertex_format_entry
    : base_vertex_format_entry
{
    int_vertex_format_entry(int size, GLenum type, int relative_offset)
        : base_vertex_format_entry(size, type, relative_offset)
    {}

    void set_format(shader_input_variable_ptr var) const;
};

struct float_vertex_format_entry
    : base_vertex_format_entry
{
    float_vertex_format_entry(int size, GLenum type, int relative_offset, bool normalized)
        : base_vertex_format_entry(size, type, relative_offset)
        , normalized_(normalized)
    {}

    bool normalized() const { return normalized_; }

    void set_format(shader_input_variable_ptr var) const;

private:
    bool normalized_;
};

}

#endif // GLEVERTEX_FORMAT_H
