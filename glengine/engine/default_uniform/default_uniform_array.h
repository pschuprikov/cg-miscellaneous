#ifndef DEFAULT_UNIFORM_ARRAY_H
#define DEFAULT_UNIFORM_ARRAY_H

#include <gleshader_variable.h>
#include <gleprogram.h>

#include "../program_ifaces/iface_default_data.h"

namespace gle
{

struct default_uniform_array_t
    : i_shader_array
{
    default_uniform_array_t(GLuint pid, iface_default_array_data_t const& data)
        : pid_(pid)
        , data_(data)
    {}

    int size() const { return data_.size(); }
    shader_variable_ptr operator[](int idx);

private:
    GLuint pid_;
    iface_default_array_data_t data_;
};

}

#endif // DEFAULT_UNIFORM_ARRAY_H
