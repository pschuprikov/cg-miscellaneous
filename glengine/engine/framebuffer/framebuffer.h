#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <gleframebuffer.h>

namespace gle
{


char const * framebuffer_completeness_str(framebuffer_completeness_t fc);
GLenum gl_color_attachment(int idx);

struct framebuffer_t
    : i_framebuffer
{
    framebuffer_t(GLuint id);
    ~framebuffer_t();

    GLuint gl_id() const { return id_; }

    i_framebuffer_attachment * color_attachment(int idx);
    i_framebuffer_attachment * depth_attachment();
    i_framebuffer_attachment * stencil_attachment();

    void set_draw_buffers(std::vector<int> const& buffers);
    void set_read_buffer(int buffer);
    std::vector<int> const& draw_buffers() const;
    int read_buffer() const;

    framebuffer_completeness_t check_draw() const;
    framebuffer_completeness_t check_read() const;

private:
    static std::vector<GLenum> idx2glenums(std::vector<int> const& buffers);

private:
    struct buffers_storage_t;
    struct attachment_storage_t;

private:
    GLuint id_;

    boost::scoped_ptr<buffers_storage_t> buffers_;
    boost::scoped_ptr<attachment_storage_t> attachments_;
};

}

#endif // FRAMEBUFFER_H
