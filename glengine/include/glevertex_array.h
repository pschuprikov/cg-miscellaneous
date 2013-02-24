#ifndef GLEVERTEX_ARRAY_H
#define GLEVERTEX_ARRAY_H

#include <glecommon.h>
#include <glebuffer.h>
#include <glevertex_format.h>
#include <gleshader_variable.h>

namespace gle
{

typedef int vertex_attrib_binding_t;

struct i_vertex_array
{
    virtual GLuint gl_id() const = 0;

    virtual void add_vertex_attrib(shader_input_variable_ptr var, vertex_format_t fmt,
                                   vertex_attrib_binding_t binding) = 0;
    virtual void remove_vertex_attrib(shader_input_variable_ptr var) = 0;

    virtual vertex_attrib_binding_t reserve_binding() = 0;
    virtual void free_binding(vertex_attrib_binding_t binding) = 0;

    virtual void bind_buffer(vertex_attrib_binding_t binding, buffer_ptr buf,
                             int offset, int stride) = 0;
    virtual buffer_ptr binding(vertex_attrib_binding_t binding) const = 0;
    virtual void unbind_buffer(vertex_attrib_binding_t binding) = 0;

    virtual void bind_element_buffer(buffer_ptr buf) = 0;
    virtual buffer_ptr element_binding() const = 0;

    virtual void set_primitive_restart_index(boost::optional<size_t> idx) = 0;
    virtual boost::optional<size_t> primitive_restart_index() const = 0;

    virtual ~i_vertex_array() {}
};
typedef boost::shared_ptr<i_vertex_array> vertex_array_ptr;

}

#endif // GLEVERTEX_ARRAY_H
