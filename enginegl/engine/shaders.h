#ifndef SHADERS_H
#define SHADERS_H

#include <vector>
#include <map>

#include "enginegl.h"

namespace eg
{

using namespace std;

struct shader_base_t
    : boost::noncopyable
{

protected:
    shader_base_t(string const& source, GLenum shader_type);
    ~shader_base_t();

public:
    GLuint get_id() const;

    bool compile();
    bool is_compiled() const;

    std::string const& get_compilation_message() const;

private:
    bool compiled_;

    GLuint shader_id_;
    string last_compilation_message_;
};

typedef boost::shared_ptr<shader_base_t> shader_ptr;
typedef vector<shader_ptr> shader_ptrs_t;

struct fragment_shader
    : shader_base_t
{
    fragment_shader(string const& source);
};

struct vertex_shader
    : shader_base_t
{
    vertex_shader(string const& source);
};

struct program_t;

struct uniform_t
    : i_uniform
{
    uniform_t (material_ptr program_id, GLuint location);

    void set(float x);
    void set(vec2 xy);
    void set(vec3 xyz);
    void set(vec4 xyzw);
    void set(mat2 const& m2);
    void set(mat3 const& m3);
    void set(mat4 const& m4);

private:
    boost::shared_ptr<program_t> program_;
    GLuint location;
};

struct vertex_attribute_t
{
    string name;
    GLuint idx;
    GLenum type;
    size_t size;
};

typedef vector<vertex_attribute_t> vector_attributes_t;


struct program
    : boost::noncopyable
    , i_material
{
public:
    program();
    ~program();

    void attach_shader(shader_ptr shader);

    bool link();
    bool is_linked() const;

    string const& get_linkage_message() const;

    shader_ptrs_t get_attached_shaders() const;

private:
    void init_mapping();

private:
    typedef map<string, int> vertex_attribute_map_t;

private:
    vertex_attribute_map_t vertex_attribs_map_;
    vector_attributes_t vertex_attribs_;

    shader_ptrs_t attached_shaders_;

    GLuint program_id_;

    string last_linkage_message_;
    bool linked_;
};

}

#endif // SHADERS_H
