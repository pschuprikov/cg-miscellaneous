#ifndef GLESHADER_OUTPUT_H
#define GLESHADER_OUTPUT_H

#include <glecommon.h>

namespace gle
{

struct i_shader_output_variable
{
    virtual int location() const = 0;
    virtual int index() const = 0;

    virtual GLenum type() const = 0;
};
typedef boost::shared_ptr<i_shader_output_variable> shader_output_variable_ptr;

struct i_shader_output_array
{
    virtual GLenum type() const = 0;

    virtual int size() const = 0;
    virtual shader_output_variable_ptr get(int idx) const = 0;
};
typedef boost::shared_ptr<i_shader_output_array> shader_output_array_ptr;

}

#endif // GLESHADER_OUTPUT_H
