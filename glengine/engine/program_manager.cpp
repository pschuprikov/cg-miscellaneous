#include <fstream>

#include "program_manager.h"

#include "shaders.h"
#include "program.h"
#include "utils/io_utils.h"

namespace gle
{

GLuint program_manager_t::new_shader_id(shader_type_t type)
{
   return glCreateShader(gl_shader_type(type));
}

GLuint program_manager_t::new_program_id()
{
    return glCreateProgram();
}

void program_manager_t::reset_program_in_use()
{
    glUseProgram(0);
    in_use_.reset();
}

void program_manager_t::delete_shader(i_shader *shd)
{
    GLuint id = shd->gl_id();
    delete shd;
    glDeleteShader(id);
}

void program_manager_t::delete_program(i_program *prg)
{
    GLuint id = prg->gl_id();
    delete prg;
    glDeleteProgram(id);
}

shader_ptr program_manager_t::load_shader(std::string file_name, shader_type_t type)
{
    std::vector<char> all_source;
    utils::load_file_contents(file_name, all_source, std::ios_base::in);

    std::vector<std::string> src;
    src.push_back(std::string(&all_source[0], all_source.size()));

    shader_ptr shd = shader_ptr(new shader_t(file_name, new_shader_id(type), type),
        boost::bind(&program_manager_t::delete_shader, _1));

    shd->source(src);

    return shd;
}

program_ptr program_manager_t::create_program(std::string name)
{
    return program_ptr(new program_t(name, new_program_id()),
                       boost::bind(&program_manager_t::delete_program, _1));
}

void program_manager_t::use(program_ptr prg)
{
    if (prg)
    {
        glUseProgram(prg->gl_id());
        in_use_ = prg;
    }
    else
    {
        glUseProgram(0);
        in_use_.reset();
    }
}


}
