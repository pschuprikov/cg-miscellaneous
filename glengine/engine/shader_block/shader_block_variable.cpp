#include <glm/gtc/type_ptr.hpp>

#include "mapped_block_adaptor.h"

#include "shader_block_variable.h"

namespace gle
{


inline GLfloat* shader_block_variable_t::float_ptr()
{
    return reinterpret_cast<float *>(adaptor_->get_pointer() + data_.offset());
}

inline GLint* shader_block_variable_t::int_ptr()
{
    return reinterpret_cast<int *>(adaptor_->get_pointer() + data_.offset());
}

void shader_block_variable_t::set(float x)
{
    *float_ptr() = x;
}

void shader_block_variable_t::set(glm::vec2 xy)
{
    std::copy(glm::value_ptr(xy), glm::value_ptr(xy) + 2, float_ptr());
}

void shader_block_variable_t::set(glm::vec3 xyz)
{
    std::copy(glm::value_ptr(xyz), glm::value_ptr(xyz) + 3, float_ptr());
}

void shader_block_variable_t::set(glm::vec4 xyzw)
{
    std::copy(glm::value_ptr(xyzw), glm::value_ptr(xyzw) + 4, float_ptr());
}

void shader_block_variable_t::set(int x)
{
    *int_ptr() = x;
}

void shader_block_variable_t::set(glm::ivec2 xy)
{
    std::copy(glm::value_ptr(xy), glm::value_ptr(xy) + 2, int_ptr());
}

void shader_block_variable_t::set(glm::ivec3 xyz)
{
    std::copy(glm::value_ptr(xyz), glm::value_ptr(xyz) + 3, int_ptr());
}

void shader_block_variable_t::set(glm::ivec4 xyzw)
{
    std::copy(glm::value_ptr(xyzw), glm::value_ptr(xyzw) + 4, int_ptr());
}

void shader_block_variable_t::set(glm::mat4)
{}

void shader_block_variable_t::set(glm::mat3)
{}

void shader_block_variable_t::set(glm::mat2)
{}

}
