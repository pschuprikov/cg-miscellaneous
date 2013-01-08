#ifndef GLEPROGRAM_H
#define GLEPROGRAM_H

#include <gleshader.h>
#include <gleshader_block.h>
#include <gleshader_variable.h>
#include <gleshader_input.h>

namespace gle
{

struct i_program
    : i_shader_variables_provider
{
    // raw access
    virtual GLuint gl_id() const = 0;

    virtual void set_separable(bool separable) = 0;
    virtual bool get_separable() const = 0;

    virtual void attach_shader(shader_ptr shd) = 0;
    virtual void reset_shader(shader_type_t type) = 0;
    virtual void link() = 0;
    virtual bool is_linked() const = 0;

    virtual shader_ptr get_shader(shader_type_t type) const = 0;

    virtual std::string const& name() const = 0;

    virtual shader_block_ptr block(std::string const& name) = 0;

    virtual shader_input_variable_ptr input_var(std::string const& name) = 0;
    virtual shader_input_array_ptr input_array(std::string const& name) = 0;

    virtual ~i_program() {}
};
typedef boost::shared_ptr<i_program> program_ptr;

}

#endif // GLEPROGRAM_H
