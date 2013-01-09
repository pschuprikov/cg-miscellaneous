#include "framebuffer_attachment.h"

namespace gle
{

void framebuffer_attachment_t::attach_texture(texture_ptr tex, int level)
{
    tex_ = tex;
    glNamedFramebufferTextureEXT(owner_->gl_id(), target_, tex->gl_id(), level);
}

void framebuffer_attachment_t::reset()
{
    tex_.reset();
    glNamedFramebufferTextureEXT(owner_->gl_id(), target_, 0, 0);
}

}
