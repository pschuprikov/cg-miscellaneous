#include <glm/gtc/type_ptr.hpp>

#include "default_uniform.h"

namespace gle
{

void default_uniform_t::set(float x)
{
    glProgramUniform1f(pid_, data_.location(), x);
}

void default_uniform_t::set(glm::vec2 xy)
{
    glProgramUniform2fv(pid_, data_.location(), 1, glm::value_ptr(xy));
}

void default_uniform_t::set(glm::vec3 xyz)
{
    glProgramUniform3fv(pid_, data_.location(), 1, glm::value_ptr(xyz));
}

void default_uniform_t::set(glm::vec4 xyzw)
{
    glProgramUniform4fv(pid_, data_.location(), 1, glm::value_ptr(xyzw));
}

void default_uniform_t::set(int x)
{
    glProgramUniform1i(pid_, data_.location(), x);
}

void default_uniform_t::set(glm::ivec2 xy)
{
    glProgramUniform2iv(pid_, data_.location(), 1, glm::value_ptr(xy));
}

void default_uniform_t::set(glm::ivec3 xyz)
{
    glProgramUniform3iv(pid_, data_.location(), 1, glm::value_ptr(xyz));
}

void default_uniform_t::set(glm::ivec4 xyzw)
{
    glProgramUniform4iv(pid_, data_.location(), 1, glm::value_ptr(xyzw));
}

void default_uniform_t::set(glm::mat4 m)
{
    glProgramUniformMatrix4fv(pid_, data_.location(),
                              1, false, glm::value_ptr(m));
}

void default_uniform_t::set(glm::mat3 m)
{
    glProgramUniformMatrix3fv(pid_, data_.location(),
                              1, false, glm::value_ptr(m));
}

}
