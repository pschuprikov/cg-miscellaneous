#ifndef SHADERS_H
#define SHADERS_H

#include <gleshader.h>

namespace gle
{

struct shader_t
    : i_shader
{
public:
    shader_t(std::string name, GLuint id, shader_type_t type)
        : id_(id), type_(type), name_(name), is_ready_(false)
    {}

    // raw access functions
    GLuint gl_id() const { return id_; }
    GLenum gl_type() const { return gl_shader_type(type_); }

    shader_type_t type() const { return type_; }
    void source(std::vector<std::string> const& src);
    bool is_ready() const { return is_ready_; }

    std::string const& name() const { return name_; }

private:
    GLuint id_;
    shader_type_t type_;

    std::string name_;
    bool is_ready_;
};

}

#endif // SHADERS_H
