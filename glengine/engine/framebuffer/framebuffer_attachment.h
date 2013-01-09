#ifndef FRAMEBUFFER_ATTACHMENT_H
#define FRAMEBUFFER_ATTACHMENT_H

#include <gleframebuffer.h>

namespace gle
{

struct framebuffer_attachment_t
    : i_framebuffer_attachment
{
    framebuffer_attachment_t(GLenum target, i_framebuffer const * owner)
        : owner_(owner), target_(target)
    {}

    void attach_texture(texture_ptr tex, int level);
    void reset();

    texture_ptr texture() const { return tex_; }

private:
    i_framebuffer const * owner_;

    GLenum target_;
    texture_ptr tex_;
};

}

#endif // FRAMEBUFFER_ATTACHMENT_H
