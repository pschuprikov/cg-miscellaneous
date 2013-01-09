#ifndef GLEFRAMEBUFFER_H
#define GLEFRAMEBUFFER_H

#include <glecommon.h>
#include <gletexture.h>

namespace gle
{

GLenum gl_color_attachment(int idx);

struct i_framebuffer_attachment
{
    virtual void attach_texture(texture_ptr tex, int level) = 0;
    virtual void reset() = 0;
    virtual texture_ptr texture() const = 0;
};

enum framebuffer_completeness_t {
    FC_complete = GL_FRAMEBUFFER_COMPLETE,
    FC_undefined = GL_FRAMEBUFFER_UNDEFINED,
    FC_incomplete_attachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
    FC_incomplete_missing_attachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
    FC_unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
    FC_incomplete_multisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
    FC_incmoplete_layer_targets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
};

char const * framebuffer_completeness_str(framebuffer_completeness_t fc);

struct i_framebuffer
{
    virtual GLuint gl_id() const = 0;

    virtual i_framebuffer_attachment * color_attachment(int idx) = 0;
    virtual i_framebuffer_attachment * depth_attachment() = 0;
    virtual i_framebuffer_attachment * stencil_attachment() = 0;

    virtual void set_draw_buffers(std::vector<int> const& buffers) = 0;
    virtual void set_read_buffer(int buffer) = 0;
    virtual std::vector<int> const& draw_buffers() const = 0;
    virtual int read_buffer() const = 0;

    virtual framebuffer_completeness_t check_draw() const = 0;
    virtual framebuffer_completeness_t check_read() const = 0;

    virtual ~i_framebuffer() {}
};
typedef boost::shared_ptr<i_framebuffer> framebuffer_ptr;

}

#endif // GLEFRAMEBUFFER_H
