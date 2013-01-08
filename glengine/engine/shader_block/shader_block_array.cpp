#include "shader_block_array.h"

#include "shader_block_variable.h"

namespace gle
{

shader_variable_ptr shader_block_array_t::get(int idx)
{
    return shader_variable_ptr(new shader_block_variable_t(adaptor_, pid_, data_[idx]),
                               boost::bind(&::operator delete, _1));
}

}
