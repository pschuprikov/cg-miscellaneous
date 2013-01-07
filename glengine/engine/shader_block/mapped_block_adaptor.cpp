#include "mapped_block_adaptor.h"

#include "shader_block_variable.h"
#include "shader_block_array.h"

namespace gle
{

shader_variable_ptr mapped_block_adaptor_t::var(std::string name)
{
    return shader_variable_ptr(new shader_block_variable_t(this, pid_, data_->var(name)));
}

shader_array_ptr mapped_block_adaptor_t::array(std::string name)
{
    return shader_array_ptr(new shader_block_array_t(this, pid_, data_->array(name)));
}

}
