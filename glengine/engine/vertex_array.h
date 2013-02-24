#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glevertex_array.h>
#include <glevertex_array_manager.h>

namespace gle
{

struct vertex_array_t
    : i_vertex_array
{
    vertex_array_t(GLuint id, i_vertex_array_manager * owner);
    ~vertex_array_t();

    void apply()
    {
        if (!bindings_applied_)
        {
            apply_bindings();
            bindings_applied_ = true;
        }
        if (!attribs_applied_)
        {
            apply_formats();
            apply_location_binding();
            attribs_applied_ = true;
        }
        if (!element_binding_applied_)
        {
            apply_element_binding();
            element_binding_applied_ = true;
        }
        if (!primitive_restart_index_applied_)
        {
            apply_primitive_restart_index();
            primitive_restart_index_applied_ = true;
        }
    }

    // i_vertex_array
public:
    GLuint gl_id() const { return id_; }

    void add_vertex_attrib(shader_input_variable_ptr var,
        vertex_format_t format, vertex_attrib_binding_t binding);
    void remove_vertex_attrib(shader_input_variable_ptr var);

    vertex_attrib_binding_t reserve_binding();
    void free_binding(vertex_attrib_binding_t binding);

    void bind_buffer(vertex_attrib_binding_t binding, buffer_ptr buf,
                     int offset, int stride);
    buffer_ptr binding(vertex_attrib_binding_t binding) const;
    void unbind_buffer(vertex_attrib_binding_t binding);

    void bind_element_buffer(buffer_ptr buf);
    buffer_ptr element_binding() const;

    void set_primitive_restart_index(boost::optional<size_t> idx);
    boost::optional<size_t> primitive_restart_index() const;

private:
    void apply_bindings();
    void apply_element_binding();
    void apply_formats();
    void apply_location_binding();
    void apply_primitive_restart_index();

private:
    struct storage_t;

private:
    GLuint id_;
    bool attribs_applied_;
    bool bindings_applied_;
    bool element_binding_applied_;
    bool primitive_restart_index_applied_;

    boost::scoped_ptr<storage_t> storage_;

    i_vertex_array_manager * owner_;
};

}

#endif // VERTEX_ARRAY_H
