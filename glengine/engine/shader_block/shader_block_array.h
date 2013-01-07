#ifndef SHADER_BLOCK_ARRAY_H
#define SHADER_BLOCK_ARRAY_H

#include <gleshader_variable.h>

#include "mapped_block_adaptor_fwd.h"

#include "../program_ifaces/iface_block_data.h"

namespace gle
{

struct shader_block_array_t
    : i_shader_array
{
public:
    shader_block_array_t(mapped_block_adaptor_t const * adaptor, GLuint pid, iface_block_array_data_t const& data)
        : adaptor_(adaptor), pid_(pid), data_(data)
    {}

    // i_shader_array
public:
    int size() const { return data_.size(); }

    shader_variable_ptr operator[](int idx);

private:
    mapped_block_adaptor_t const * adaptor_;

    GLuint pid_;
    iface_block_array_data_t const data_;
};

}

#endif // SHADER_BLOCK_ARRAY_H
