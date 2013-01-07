#ifndef SHADER_BLOCK_H
#define SHADER_BLOCK_H

#include <gleshader_block.h>

#include "../program_ifaces/iface_block_data.h"

#include "mapped_block_adaptor_fwd.h"

namespace gle
{

struct shader_block_t
    : i_shader_block
{
    shader_block_t(GLuint pid, iface_block_data_ptr data)
        : pid_(pid), data_(data)
    {}

    // i_shader_block
public:
    int idx() const { return data_->idx(); }
    shader_block_type_t type() const { return data_->type(); }
    int data_size() const { return data_->data_size(); }

    int binding() const { return data_->binding(); }
    void set_binding(int idx);

    mapped_block_adaptor_ptr mapped_adapter() const;

private:
    GLuint const pid_;
    iface_block_data_ptr const data_;
};

}

#endif // SHADER_BLOCK_H
