#ifndef PROGRAM_H
#define PROGRAM_H

#include <gleprogram.h>

#include "program_ifaces/iface_storage_fwd.h"

namespace gle
{

struct program_t
    : i_program
{
    program_t(std::string const& name, GLuint id);
    ~program_t();

    GLuint gl_id() const { return id_; }

    void set_separable(bool separable);
    bool get_separable() const { return is_separable_; }

    void attach_shader(shader_ptr shd);
    void reset_shader(shader_type_t type);

    void link();
    bool is_linked() const { return is_linked_; }

    shader_ptr get_shader(shader_type_t type) const { return shaders_.at(type); }

    std::string const& name() const { return name_; }

    // interfaces:

    shader_block_ptr block(std::string const& name);

    shader_input_variable_ptr input_var(std::string const& name);
    shader_input_array_ptr input_array(std::string const& name);

    shader_output_variable_ptr output_var(std::string const& name);
    shader_output_array_ptr output_array(std::string const& name);

    // i_shader_variables_provider
public:
    shader_variable_ptr var(std::string name);
    shader_array_ptr array(std::string name);

private:
    typedef std::map<shader_type_t, shader_ptr> shaders_map_t;

private:
    std::string name_;

    GLuint id_;

    bool is_linked_;
    shaders_map_t shaders_;

    bool is_separable_;

    boost::scoped_ptr<iface_storage_t> iface_storage_;
};

}

#endif // PROGRAM_H
