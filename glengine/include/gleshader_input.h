#ifndef GLESHADER_INPUT_H
#define GLESHADER_INPUT_H

#include <glecommon.h>


namespace gle
{
    struct i_shader_input_variable
    {
        virtual int location() const = 0;

        virtual GLenum type() const = 0;
    };
    typedef boost::shared_ptr<i_shader_input_variable> shader_input_variable_ptr;

    struct i_shader_input_array
    {
        virtual GLenum type() const = 0;

        virtual int size() const = 0;
        virtual shader_input_variable_ptr get(int idx) const = 0;
    };
    typedef boost::shared_ptr<i_shader_input_array> shader_input_array_ptr;
}

#endif // GLESHADER_INPUT_H
