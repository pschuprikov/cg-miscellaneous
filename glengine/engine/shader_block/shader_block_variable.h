#ifndef SHADER_BLOCK_VARIABLE_H
#define SHADER_BLOCK_VARIABLE_H

#include <gleshader_variable.h>

#include "mapped_block_adaptor_fwd.h"

#include "../program_ifaces/iface_block_data.h"

namespace gle
{

struct shader_block_variable_t
    : i_shader_variable
{
    shader_block_variable_t(mapped_block_adaptor_t const * adaptor,
                            GLuint pid, iface_block_variable_data_t const& data)
        : adaptor_(adaptor)
        , pid_(pid)
        , data_(data)
    {}

    void set(float x);
    void set(glm::vec2 xy);
    void set(glm::vec3 xyz);
    void set(glm::vec4 xyzw);

    void set(int x);
    void set(glm::ivec2 xy);
    void set(glm::ivec3 xyz);
    void set(glm::ivec4 xyzw);

    void set(glm::mat4);
    void set(glm::mat3);

    GLenum type() const { return data_.type(); }

private:
    inline GLfloat* float_ptr();
    inline GLint* int_ptr();

private:
    mapped_block_adaptor_t const * adaptor_;

    GLuint const pid_;
    iface_block_variable_data_t const data_;
};

}

#endif // SHADER_BLOCK_VARIABLE_H
