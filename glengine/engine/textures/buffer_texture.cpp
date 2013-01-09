#include "buffer_texture.h"

namespace gle
{

void buffer_texture_t::set_buffer(GLenum internal_format, buffer_ptr buf)
{
    glTextureBufferEXT(id_, TT_buffer, internal_format, buf->gl_id());
    buf_ = buf;
}

void buffer_texture_t::reset_buffer()
{
    glTextureBufferEXT(id_, TT_buffer, GL_R8UI, 0);
    buf_.reset();
}


}
