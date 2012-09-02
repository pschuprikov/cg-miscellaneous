#ifndef COMMON_INTERFACES_H
#define COMMON_INTERFACES_H

#include <boost/shared_ptr.hpp>

#include <glm/glm.hpp>
#include <GL/gl.h>

namespace enginegl
{

using namespace glm;

struct i_engine
{
    virtual void matrix_mode(GLenum matrix_type) = 0;
    virtual GLenum get_matrix_mode() = 0;

    virtual void load_identity() = 0;
    virtual void load_matrix(mat4 const& matrix) = 0;
    virtual void get_matrix(mat4& matrix) = 0;

    virtual void clear_color(vec4 rgba) = 0;
    virtual void clear(GLbitfield buffers_bits) = 0;

    virtual void color(vec3 rgb) = 0;
    virtual void color(vec4 rgba) = 0;

    virtual void vertex(vec2 xy) = 0;
    virtual void vertex(vec3 xyz) = 0;
    virtual void vertex(vec4 xyzw) = 0;

    virtual void begin(GLenum) = 0;
    virtual void end() = 0;

    virtual ~i_engine() {}
};

typedef boost::shared_ptr<i_engine> engine_ptr;

}

#endif // COMMON_INTERFACES_H
