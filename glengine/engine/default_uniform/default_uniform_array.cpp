#include <new>
#include "default_uniform_array.h"

#include "default_uniform.h"

namespace gle
{
    shader_variable_ptr default_uniform_array_t::get(int idx)
    {
        return shader_variable_ptr(new default_uniform_t(pid_, data_[idx]),
                                   boost::bind(&::operator delete, _1));
    }
}
