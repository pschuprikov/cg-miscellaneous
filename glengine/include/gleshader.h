#ifndef GLESHADER_H
#define GLESHADER_H

#include <stdexcept>

#include <glecommon.h>

namespace gle
{

enum shader_type_t { ST_fragment, ST_vertex, ST_geometry, ST_tess_control, ST_tess_eval, ST_compute };

inline GLenum gl_shader_type(shader_type_t st)
{
    switch(st)
    {
    case ST_fragment : return GL_FRAGMENT_SHADER; case ST_vertex : return GL_VERTEX_SHADER;
    case ST_geometry : return GL_GEOMETRY_SHADER; case ST_tess_control : return GL_TESS_CONTROL_SHADER;
    case ST_tess_eval : return GL_TESS_EVALUATION_SHADER; case ST_compute : return GL_COMPUTE_SHADER;
    default : return 0;
    }
}

struct i_shader
{
    // raw access functions
    virtual GLuint gl_id() const = 0;
    virtual GLenum gl_type() const = 0;

    virtual shader_type_t type() const = 0;
    virtual void source(std::vector<std::string> const& src) = 0;
    virtual bool is_ready() const = 0;

    virtual std::string const& name() const = 0;

    virtual ~i_shader() {}
};
typedef boost::shared_ptr<i_shader> shader_ptr;

struct compilation_failed_exception_t
    : std::exception
{
    compilation_failed_exception_t(std::string name, std::string reason)
        : name_(name)
        , reason_(reason)
        , cause_(name + " compilation failed.")
    {}

    char const * what() const throw () { return cause_.c_str(); }

    std::string const& reason() const { return reason_; }
    std::string const& name() const { return name_; }

    ~compilation_failed_exception_t() throw() {}
private:
    std::string name_;
    std::string reason_;
    std::string cause_;
};

}

#endif // GLESHADER_H
