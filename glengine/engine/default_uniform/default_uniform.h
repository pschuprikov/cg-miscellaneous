#ifndef DEFAULT_UNIFORM_H
#define DEFAULT_UNIFORM_H

#include <gleshader_variable.h>
#include <gleprogram.h>

#include "../program_ifaces/iface_default_data.h"

namespace gle
{

struct default_uniform_t
    : i_shader_variable
{
    default_uniform_t(GLuint pid, iface_default_variable_data_t const& data)
        : pid_(pid)
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

    void set(unsigned int x);
    void set(glm::uvec2 xy);
    void set(glm::uvec3 xyz);
    void set(glm::uvec4 xyzw);

    void set(glm::mat4 m);
    void set(glm::mat3 m);
    void set(glm::mat2 m);

    GLenum type() const { return data_.type(); }

private:
    GLuint pid_;
    iface_default_variable_data_t const data_;
};

}

#endif // DEFAULT_UNIFORM_H
