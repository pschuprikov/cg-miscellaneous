#ifndef SHADER_BLOCK_STORAGE_H
#define SHADER_BLOCK_STORAGE_H

#include <gleshader_block.h>

#include "mapped_block_adaptor_fwd.h"

#include "../program_ifaces/iface_block_data.h"

namespace gle
{

struct mapped_block_adaptor_t
    : i_mapped_block_adaptor
{
    mapped_block_adaptor_t(GLuint pid, iface_block_data_ptr data)
        : pid_(pid)
        , data_(data)
        , ptr_(NULL)
    {}

    // i_mapped_block_adaptor
public:
    void set_pointer(void* ptr) { ptr_ = static_cast<GLbyte *>(ptr); }
    GLbyte * get_pointer() const { return ptr_; }

    // i_shader_variables_provider
public:
    shader_variable_ptr var(std::string name);
    shader_array_ptr array(std::string name);

private:
    GLuint pid_;

    iface_block_data_ptr const data_;

    GLbyte * ptr_;
};

}

#endif // SHADER_BLOCK_STORAGE_H
