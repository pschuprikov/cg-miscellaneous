#ifndef BUFFER_TEXTURE_H
#define BUFFER_TEXTURE_H

#include <gletexture.h>

namespace gle
{

struct buffer_texture_t
    : i_buffer_texture
{
    buffer_texture_t(GLuint id)
        : id_(id)
    {}

    // i_generic_texture
public:
    GLuint gl_id() const { return id_; }
    texture_target_t target() const { return TT_buffer; }

    int internal_format() const { return internal_format_; }

    // i_buffer_texture
public:
    void set_buffer(GLenum internal_format, buffer_ptr buf);

    void reset_buffer();

    buffer_ptr buffer() const { return buf_; }

private:
    GLuint id_;

    int internal_format_;
    buffer_ptr buf_;
};

}

#endif // BUFFER_TEXTURE_H
