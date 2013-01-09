#ifndef GLEFRAMEBUFFER_MANAGER_H
#define GLEFRAMEBUFFER_MANAGER_H

#include <gleframebuffer.h>

namespace gle
{

struct i_framebuffer_manager
{
    virtual framebuffer_ptr create_framebuffer() = 0;

    virtual framebuffer_ptr draw_framebuffer() const = 0;
    virtual framebuffer_ptr read_framebuffer() const = 0;
    virtual void set_draw_framebuffer(framebuffer_ptr fb) = 0;
    virtual void set_read_framebuffer(framebuffer_ptr fb) = 0;
    virtual void set_draw_framebuffer_default() = 0;
    virtual void set_read_framebuffer_default() = 0;
};

}

#endif // GLEFRAMEBUFFER_MANAGER_H
