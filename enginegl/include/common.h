#ifndef COMMON_H
#define COMMON_H

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace enginegl
{

using namespace glm;
using namespace std;

struct i_engine
{
    virtual void matrix_mode(GLenum matrix_type) = 0;
    virtual GLenum get_matrix_mode() = 0;

    virtual GLint get_current_program() = 0;

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

struct i_uniform
{
    virtual void set(float x) = 0;
    virtual void set(vec2 xy) = 0;
    virtual void set(vec3 xyz) = 0;
    virtual void set(vec4 xyzw) = 0;
    virtual void set(mat2 const& m2) = 0;
    virtual void set(mat3 const& m3) = 0;
    virtual void set(mat4 const& m4) = 0;

    virtual ~i_uniform() {}
};

typedef boost::shared_ptr<i_uniform> uniform_ptr;

struct i_material
{
    virtual GLuint id() = 0;
    virtual GLuint get_vertex_attrib_idx(string const& name, size_t idx = 0) = 0;

    virtual uniform_ptr get_uniform(string const& name, size_t idx = 0);

    virtual ~i_material() {}
};

typedef boost::shared_ptr<i_engine> engine_ptr;

}

#endif // COMMON_H
