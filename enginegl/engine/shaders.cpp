#include <fstream>
#include <vector>
#include <string>

#include "shaders.h"

namespace eg
{

using namespace std;

shader_base_t::shader_base_t(string const& source, GLenum shader_type)
    : compiled_(false)
{
    shader_id_ = glCreateShader(shader_type);
    ifstream stin(source.c_str(), ios_base::binary);
    stin.seekg(0, ios_base::end);
    int size = stin.tellg();
    stin.seekg(0, ios_base::beg);

    string src;
    {
        char * source_code = new char[size];
        stin.read(source_code, size);
        src.assign(source_code, size);
        delete source_code;
    }

    char const * src_ptr = src.c_str();

    glShaderSource(shader_id_, 1, &src_ptr, NULL);
}


shader_base_t::~shader_base_t()
{
    glDeleteShader(shader_id_);
}

GLuint shader_base_t::get_id() const
{
    return shader_id_;
}

bool shader_base_t::compile()
{
    if (compiled_)
        return true;
    GLint status;
    glCompileShader(shader_id_);
    glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &status);

    GLint shader_len;
    glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &shader_len);


    char * buffer = new char[shader_len];
    glGetShaderInfoLog(shader_id_, shader_len, &shader_len, buffer);

    last_compilation_message_.assign(buffer, shader_len);

    delete [] buffer;

    compiled_ = status;

    return status;
}

bool shader_base_t::is_compiled() const
{
    return compiled_;
}

string const& shader_base_t::get_compilation_message() const
{
    return last_compilation_message_;
}


fragment_shader::fragment_shader(string const& source)
    : shader_base_t(source, GL_FRAGMENT_SHADER)
{}

vertex_shader::vertex_shader(string const& source)
    : shader_base_t(source, GL_VERTEX_SHADER)
{}

program::program()
    : linked_(false)
{
    program_id_ = glCreateProgram();
}

program::~program()
{
    glDeleteProgram(program_id_);
}

void program::attach_shader(shader_ptr shader)
{
    bool found = false;
    for (int i = 0; i < (int)attached_shaders_.size(); i++)
    {
        if (attached_shaders_[i]->get_id() == shader->get_id())
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        linked_ = false;
        attached_shaders_.push_back(shader);
        glAttachShader(program_id_, shader->get_id());
    }
}

shader_ptrs_t program::get_attached_shaders() const
{
    return attached_shaders_;
}

void program::init_mapping()
{
    assert(linked_);

    vertex_attribs_.clear();
    vertex_attribs_map_.clear();

    GLint num_attrib;
    GLint active_attribute_max_len;
    glGetProgramiv(program_id_, GL_ACTIVE_ATTRIBUTES, &num_attrib);
    glGetProgramiv(program_id_, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &active_attribute_max_len);
    for (int i = 0; i < num_attrib; i++)
    {
        vector<char> name(active_attribute_max_len);
        GLsizei dummy;
        GLint size;
        GLenum type;
        glGetActiveAttrib(program_id_, i, active_attribute_max_len, &dummy, &size, &type, &name[0]);

        vertex_attribute_t attrib;
        attrib.name.assign(&name[0]);
        attrib.idx = i;
        attrib.size = size;
        attrib.type = type;

        vertex_attribs_.push_back(attrib);
        vertex_attribs_map_.insert(make_pair(attrib.name, i));
    }
}

bool program::link()
{
    bool res = true;
    for (shader_ptrs_t::iterator i = attached_shaders_.begin(); i != attached_shaders_.end(); i++)
        res &= (*i)->compile();
    if (!res)
    {
        last_linkage_message_ = "shaders can't compile";
        return false;
    }
    else
    {
        glLinkProgram(program_id_);
        GLint status;
        glGetProgramiv(program_id_, GL_LINK_STATUS, &status);

        GLint log_length;
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &log_length);
        char * buffer = new char[log_length];
        glGetProgramInfoLog(program_id_, log_length, &log_length, buffer);

        last_linkage_message_.assign(buffer, log_length);

        if (status)
            init_mapping();
        return status;
    }
}

GLuint program::get_program_id() const
{
    return program_id_;
}

string const& program::get_linkage_message() const
{
    return last_linkage_message_;
}

}

