#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glevertex_array.h>

namespace gle
{

struct vertex_array_t
    : i_vertex_array
{
    vertex_array_t(GLuint id);
    ~vertex_array_t();

    void apply()
    {
        if (!bindings_applied_)
        {
            bindings_applied_ = true;
            apply_bindings();
        }
        if (!attribs_applied_)
        {
            attribs_applied_ = true;
            apply_formats();
            apply_location_binding();
        }
    }

    // i_vertex_array
public:
    GLuint gl_id() const { return id_; }

    void add_vertex_attrib(shader_input_variable_ptr var, vertex_format_ptr format,
                                   vertex_attrib_binding_t binding);
    void remove_vertex_attrib(shader_input_variable_ptr var);

    vertex_attrib_binding_t reserve_binding();
    void free_binding(vertex_attrib_binding_t binding);

    void bind_buffer(vertex_attrib_binding_t binding, buffer_ptr buf,
                     int offset, int stride);
    buffer_ptr binding(vertex_attrib_binding_t binding) const;
    void unbind_buffer(vertex_attrib_binding_t binding);

private:
    void apply_bindings();
    void apply_formats();
    void apply_location_binding();

private:
    struct storage_t;

private:
    GLuint id_;
    bool attribs_applied_;
    bool bindings_applied_;

    boost::scoped_ptr<storage_t> storage_;
};

}

#endif // VERTEX_ARRAY_H
