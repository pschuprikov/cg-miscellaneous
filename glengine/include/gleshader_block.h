#ifndef GLEUNIFORM_BLOCK_H
#define GLEUNIFORM_BLOCK_H

#include <gleshader_variable.h>

namespace gle
{

struct i_mapped_block_adaptor
    : i_shader_variables_provider
{
    virtual void set_pointer(void* ptr) = 0;
    virtual GLbyte * get_pointer() const = 0;

    virtual ~i_mapped_block_adaptor() {}
};
typedef boost::shared_ptr<i_mapped_block_adaptor> mapped_block_adaptor_ptr;

enum shader_block_type_t { SBT_uniform, SBT_storage };

inline GLenum sbt2gliface(shader_block_type_t type)
{
    switch(type)
    {
        case SBT_uniform : return GL_UNIFORM_BLOCK; case SBT_storage : return GL_SHADER_STORAGE_BLOCK;
        default : return 0;
    }
}

inline GLenum sbt2glvar(shader_block_type_t type)
{
    switch(type)
    {
        case SBT_uniform : return GL_UNIFORM; case SBT_storage : return GL_BUFFER_VARIABLE;
        default : return 0;
    }
}

struct i_shader_block
{
    virtual int idx() const = 0;
    virtual shader_block_type_t type() const = 0;
    virtual int data_size() const = 0;

    virtual int binding() const = 0;
    virtual void set_binding(int idx) = 0;

    virtual mapped_block_adaptor_ptr mapped_adapter() const = 0;
};
typedef boost::shared_ptr<i_shader_block> shader_block_ptr;

}

#endif // GLEUNIFORM_BLOCK_H
