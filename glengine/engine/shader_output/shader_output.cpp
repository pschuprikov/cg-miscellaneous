#include "shader_output.h"

namespace gle
{

shader_output_variable_ptr shader_output_array_t::get(int idx) const
{
    return shader_output_variable_ptr(new shader_output_variable_t(pid_, data_[idx]),
                                      boost::bind(&::operator delete, _1));
}

}
