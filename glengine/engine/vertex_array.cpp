#include "vertex_array.h"

namespace gle
{
    struct vertex_array_t::storage_t
    {
        struct binding_data_t
        {
            buffer_ptr buf;
            int offset;
            int stride;
            binding_data_t(buffer_ptr buf, int offset, int stride)
                : buf(buf), offset(offset), stride(stride)
            {}
        };

        struct attrib_data_t
        {
            shader_input_variable_ptr var;
            vertex_format_ptr fmt;
            vertex_attrib_binding_t binding;
            attrib_data_t(shader_input_variable_ptr var, vertex_format_ptr fmt, vertex_attrib_binding_t binding)
                : var(var), fmt(fmt), binding(binding)
            {}
        };

        typedef std::map<int, attrib_data_t> attrib_map_t;
        typedef std::map<int, binding_data_t> binding_map_t;

        attrib_map_t attribs;
        binding_map_t buffers;
    };

    vertex_array_t::vertex_array_t(GLuint id)
        : id_(id)
        , applied_(true)
        , storage_(new storage_t())
    {}

    void vertex_array_t::add_vertex_attrib(shader_input_variable_ptr var, vertex_format_ptr fmt,
                                   vertex_attrib_binding_t binding)
    {
        applied_ = false;
        storage_->attribs.insert(std::make_pair(var->location(), storage_t::attrib_data_t(var, fmt, binding)));
        glEnableVertexArrayAttribEXT(id_, var->location());
    }

    void vertex_array_t::apply_bindings()
    {
        for (storage_t::binding_map_t::const_iterator b_it = storage_->buffers.begin();
             b_it != storage_->buffers.end(); ++b_it)
        {
            glBindVertexBuffer(b_it->first, b_it->second.buf->gl_id(), b_it->second.offset,
                               b_it->second.stride);
        }
    }

    void vertex_array_t::apply_formats()
    {
        for (storage_t::attrib_map_t::const_iterator a_it = storage_->attribs.begin();
             a_it != storage_->attribs.end(); ++a_it)
        {
            a_it->second.fmt->set_format(a_it->second.var);
        }
    }

    void vertex_array_t::apply_location_binding()
    {
        for (storage_t::attrib_map_t::const_iterator a_it = storage_->attribs.begin();
             a_it != storage_->attribs.end(); ++a_it)
        {
            glVertexAttribBinding(a_it->first, a_it->second.binding);
        }
    }

    void vertex_array_t::remove_vertex_attrib(shader_input_variable_ptr var)
    {
        applied_ = false;
        storage_->attribs.erase(var->location());
        glDisableVertexArrayAttribEXT(id_, var->location());
    }

    vertex_attrib_binding_t vertex_array_t::bind_buffer(buffer_ptr buf, int offset, int stride)
    {
        applied_ = false;
        for (int free_binding = 0;;free_binding++)
        {
            if (storage_->buffers.find(free_binding) == storage_->buffers.end())
            {
                storage_->buffers.insert(std::make_pair(free_binding,
                                                        storage_t::binding_data_t(buf, offset, stride)));
                return free_binding;
            }
        }
    }

    buffer_ptr vertex_array_t::binding(vertex_attrib_binding_t binding) const
    {
        return storage_->buffers.at(binding).buf;
    }

    void vertex_array_t::unbind_buffer(vertex_attrib_binding_t binding)
    {
        applied_ = false;
        storage_->buffers.erase(binding);
    }


    vertex_array_t::~vertex_array_t() {}
}
