#include "program.h"

#include "program_ifaces/iface_storage.h"

#include "default_uniform/default_uniform.h"
#include "default_uniform/default_uniform_array.h"
#include "shader_block/shader_block.h"
#include "shader_input/shader_input.h"

namespace gle
{

program_t::program_t(std::string const& name, GLuint id)
    : name_(name)
    , id_(id)
    , is_linked_(false)
    , is_separable_(false)
{}

program_t::~program_t()
{}

void program_t::set_separable(bool separable)
{
    if (separable != is_separable_)
    {
        is_separable_ = separable;
        glProgramParameteri(id_, GL_PROGRAM_SEPARABLE, separable);
    }
}

void program_t::attach_shader(shader_ptr shd)
{
    if (!shd)
        return;
    else
    {
        glAttachShader(id_, shd->gl_id());
        shaders_[shd->type()] = shd;
    }
}

void program_t::reset_shader(shader_type_t type)
{
    if (shaders_[type])
        glDetachShader(id_, shaders_[type]->gl_id());
    shaders_[type] = shader_ptr();
}

void program_t::link()
{
    glLinkProgram(id_);

    GLint status;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);

    if (status)
    {
        is_linked_ = true;

        iface_storage_.reset(new iface_storage_t(id_));
    }
    else
    {
        GLint length;
        glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);
        assert(length > 0);

        std::vector<char> log_buffer(length);
        glGetProgramInfoLog(id_, length, &length, &log_buffer[0]);
        throw compilation_failed_exception_t(name_, &log_buffer[0]);
    }
}

shader_variable_ptr program_t::var(std::string name)
{
    return shader_variable_ptr(new default_uniform_t(id_, iface_storage_->var(name)),
                               boost::bind(::operator delete, _1));
}

shader_array_ptr program_t::array(std::string name)
{
    return shader_array_ptr(new default_uniform_array_t(id_, iface_storage_->array(name)),
                            boost::bind(::operator delete, _1));
}

shader_block_ptr program_t::block(std::string const& name)
{
    return shader_block_ptr(new shader_block_t(id_, iface_storage_->block(name)),
                            boost::bind(::operator delete, _1));
}

shader_input_variable_ptr program_t::input_var(std::string const& name)
{
    return shader_input_variable_ptr(new shader_input_variable_t(id_, iface_storage_->input_var(name)),
                                     boost::bind(::operator delete, _1));
}

shader_input_array_ptr program_t::input_array(std::string const& name)
{
    return shader_input_array_ptr(new shader_input_array_t(id_, iface_storage_->input_array(name)),
                                  boost::bind(::operator delete, _1));
}

}
