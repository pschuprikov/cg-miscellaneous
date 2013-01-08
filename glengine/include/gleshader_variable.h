#ifndef GLEUNIFORM_H
#define GLEUNIFORM_H

#include <glecommon.h>

namespace gle
{

struct i_shader_variable
{
    virtual void set(float x) = 0;
    virtual void set(glm::vec2 xy) = 0;
    virtual void set(glm::vec3 xyz) = 0;
    virtual void set(glm::vec4 xyzw) = 0;

    virtual void set(int x) = 0;
    virtual void set(glm::ivec2 xy) = 0;
    virtual void set(glm::ivec3 xyz) = 0;
    virtual void set(glm::ivec4 xyzw) = 0;

    virtual void set(glm::mat4 m) = 0;
    virtual void set(glm::mat3 m) = 0;

    virtual GLenum type() const = 0;
};
typedef boost::shared_ptr<i_shader_variable> shader_variable_ptr;

struct i_shader_array
{
    virtual bool is_bounded() const = 0;

    virtual int size() const = 0;
    virtual int stride() const = 0;
    virtual shader_variable_ptr get(int idx) = 0;
};
typedef boost::shared_ptr<i_shader_array> shader_array_ptr;

struct i_shader_variables_provider
{
    virtual shader_variable_ptr var(std::string name) = 0;
    virtual shader_array_ptr array(std::string name) = 0;
};

}

#endif // GLEUNIFORM_H
