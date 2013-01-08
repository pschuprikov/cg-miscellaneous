#ifndef SHADER_INPUT_H
#define SHADER_INPUT_H

#include <gleshader_input.h>

#include "../program_ifaces/iface_input_data.h"

namespace gle
{

struct shader_input_variable_t
    : i_shader_input_variable
{
    shader_input_variable_t(GLuint pid, iface_input_variable_data_t const& data)
        : pid_(pid)
        , data_(data)
    {}

    // i_shader_input_variable
public:
    int location() const { return data_.location(); }

    GLenum type() const { return data_.type(); }

private:
    GLuint pid_;

    iface_input_variable_data_t data_;
};

struct shader_input_array_t
    : i_shader_input_array
{
    shader_input_array_t(GLuint pid, iface_input_array_data_t const& data)
        : pid_(pid)
        , data_(data)
    {}

    // i_shader_input_array
public:
    GLenum type() const { return data_.type(); }

    int size() const { return data_.size(); }
    shader_input_variable_ptr get(int idx) const;

private:
    GLuint pid_;

    iface_input_array_data_t data_;
};

}

#endif // SHADER_INPUT_H
