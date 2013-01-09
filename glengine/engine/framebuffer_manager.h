#ifndef FRAMEBUFFER_MANAGER_H
#define FRAMEBUFFER_MANAGER_H

#include <gleframebuffer_manager.h>

namespace gle
{

struct framebuffer_manager_t
    : i_framebuffer_manager
{
    framebuffer_ptr create_framebuffer();

    framebuffer_ptr draw_framebuffer() const { return draw_fb_; }
    framebuffer_ptr read_framebuffer() const { return read_fb_; }
    void set_draw_framebuffer(framebuffer_ptr fb);
    void set_read_framebuffer(framebuffer_ptr fb);
    void set_draw_framebuffer_default();
    void set_read_framebuffer_default();

private:
    static GLuint new_id();
    static void delete_framebuffer(i_framebuffer * fb);

private:
    framebuffer_ptr draw_fb_;
    framebuffer_ptr read_fb_;
};

}

#endif // FRAMEBUFFER_MANAGER_H
