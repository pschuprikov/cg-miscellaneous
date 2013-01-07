#include "shaders.h"

namespace gle
{
    void shader_t::source(std::vector<std::string> const& src)
    {
        if (src.empty())
            throw compilation_failed_exception_t(name_, "shader empty source");

        // prepare source
        std::vector<char const *> srcs(src.size());
        for (int i = 0; i < (int)src.size(); i++)
            srcs[i] = src[i].c_str();

        // compilation
        glShaderSource(id_, srcs.size(), &srcs[0], NULL);
        glCompileShader(id_);

        GLint status;
        glGetShaderiv(id_, GL_COMPILE_STATUS, &status);

        if (status == GL_TRUE)
            is_ready_ = true;
        else
        {
            GLint log_len;
            glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &log_len);
            assert(log_len > 0);
            std::vector<char> log_buffer(log_len);

            glGetShaderInfoLog(id_, log_len, &log_len, &log_buffer[0]);
            throw compilation_failed_exception_t(name_, &log_buffer[0]);
        }
    }
}
