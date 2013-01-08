#include "shader_input.h"

namespace gle
{

shader_input_variable_ptr shader_input_array_t::get(int idx) const
{
    return shader_input_variable_ptr(new shader_input_variable_t(pid_, data_[idx]),
                                     boost::bind(&::operator delete, _1));
}

}
