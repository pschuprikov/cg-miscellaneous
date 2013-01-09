#ifndef SHADER_OUTPUT_H
#define SHADER_OUTPUT_H

#include <gleshader_output.h>

#include "../program_ifaces/iface_output_data.h"

namespace gle
{

struct shader_output_variable_t
    : i_shader_output_variable
{
    shader_output_variable_t(GLuint pid, iface_output_variable_data_t const& data)
        : pid_(pid)
        , data_(data)
    {}

    // i_shader_output_variable
public:
    int location() const { return data_.location(); }
    int index() const { return data_.index(); }

    GLenum type() const { return data_.type(); }

private:
    GLuint pid_;

    iface_output_variable_data_t data_;
};

struct shader_output_array_t
    : i_shader_output_array
{
    shader_output_array_t(GLuint pid, iface_output_array_data_t const& data)
        : pid_(pid)
        , data_(data)
    {}

    // i_shader_output_array
public:
    GLenum type() const { return data_.type(); }

    int size() const { return data_.size(); }
    shader_output_variable_ptr get(int idx) const;

private:
    GLuint pid_;

    iface_output_array_data_t data_;
};

}

#endif // SHADER_OUTPUT_H
