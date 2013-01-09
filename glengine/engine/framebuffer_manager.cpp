#include "framebuffer_manager.h"

#include "framebuffer/framebuffer.h"

namespace gle
{

framebuffer_ptr framebuffer_manager_t::create_framebuffer()
{
    return framebuffer_ptr(new framebuffer_t(new_id()),
                           boost::bind(&framebuffer_manager_t::delete_framebuffer, _1));
}

void framebuffer_manager_t::set_draw_framebuffer(framebuffer_ptr fb)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fb->gl_id());
    draw_fb_ = fb;
}

void framebuffer_manager_t::set_read_framebuffer(framebuffer_ptr fb)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fb->gl_id());
    read_fb_ = fb;
}

void framebuffer_manager_t::set_draw_framebuffer_default()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    draw_fb_.reset();
}

void framebuffer_manager_t::set_read_framebuffer_default()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    read_fb_.reset();
}

GLuint framebuffer_manager_t::new_id()
{
    GLuint id;
    glGenFramebuffers(1, &id);
    return id;
}

void framebuffer_manager_t::delete_framebuffer(i_framebuffer * fb)
{
    GLuint id = fb->gl_id();
    delete fb;
    glDeleteFramebuffers(1, &id);
}


}
