#include "shader_block.h"

#include "mapped_block_adaptor.h"

namespace gle
{

mapped_block_adaptor_ptr shader_block_t::mapped_adapter() const
{
    return mapped_block_adaptor_ptr(new mapped_block_adaptor_t(pid_, data_),
                                    boost::bind(::operator delete, _1));
}

void shader_block_t::set_binding(int idx)
{
    data_->set_binding(idx);
    switch(type())
    {
    case SBT_uniform :
        glUniformBlockBinding(pid_, data_->idx(), data_->binding());
        break;

    case SBT_storage :
        glShaderStorageBlockBinding(pid_, data_->idx(), data_->binding());
        break;
    }
}

}
