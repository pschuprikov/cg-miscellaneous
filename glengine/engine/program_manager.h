#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include <gleprogram_manager.h>

namespace gle
{

struct program_manager_t
    : i_program_manager
{
    shader_ptr load_shader(std::string file_name, shader_type_t type);
    program_ptr create_program(std::string name);

    program_ptr program_in_use() const { return in_use_; }
    void use(program_ptr prg);
    void reset_program_in_use();

private:
    static void delete_shader(i_shader * shd);
    static void delete_program(i_program * prg);

    static inline GLuint new_shader_id(shader_type_t type);
    static inline GLuint new_program_id();

private:
    program_ptr in_use_;
};

}

#endif // PROGRAM_MANAGER_H
