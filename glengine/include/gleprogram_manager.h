#ifndef GLEPROGRAM_MANAGER_H
#define GLEPROGRAM_MANAGER_H

#include <gleshader.h>
#include <gleprogram.h>
namespace gle
{

struct i_program_manager
{
    virtual shader_ptr load_shader(std::string file_name, shader_type_t type) = 0;
    virtual program_ptr create_program(std::string name) = 0;

    virtual program_ptr program_in_use() const = 0;
    virtual void use(program_ptr prg) = 0;
    virtual void reset_program_in_use() = 0;
};

}

#endif // GLEPROGRAM_MANAGER_H
